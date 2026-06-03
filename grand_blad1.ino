#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- Pin Definitions ----------------
#define SOIL_MOISTURE_PIN A0  
#define TMP36_PIN A1          
#define RELAY_PUMP 5          
#define RELAY_VALVE_1 6       
#define RELAY_VALVE_2 7       
#define RELAY_VALVE_3 8       
#define STATUS_LED 9          

// ---------------- Thresholds & Limits ----------------
const int MOISTURE_THRESHOLD_LOW = 300;   // Dry soil
const int MOISTURE_THRESHOLD_HIGH = 700;  // Wet soil
const int TEMP_MIN = 15;                  // °C
const int TEMP_MAX = 25;                  // °C
const unsigned long MAX_IRRIGATION_TIME = 60000; // 60s cutoff

// ---------------- Relay States ----------------
#define RELAY_ON HIGH
#define RELAY_OFF LOW

// ---------------- System Variables ----------------
int soilMoisture = 0;
float temperature = 0.0;
bool isWatering = false;
unsigned long wateringStartTime = 0;
String systemStatus = "System Ready";

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);
  initializeHardware();
  lcd.init();
  lcd.backlight();
  showStartupMessage();
}

void loop() {
  readSensors();
  checkWateringConditions();
  updateDisplay();
  delay(1000);
}

// ---------------- Hardware Setup ----------------
void initializeHardware() {
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(TMP36_PIN, INPUT);
  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(RELAY_VALVE_1, OUTPUT);
  pinMode(RELAY_VALVE_2, OUTPUT);
  pinMode(RELAY_VALVE_3, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  emergencyStop();
}

void emergencyStop() {
  digitalWrite(RELAY_PUMP, RELAY_OFF);
  closeValves();
  digitalWrite(STATUS_LED, LOW);
  isWatering = false;
  systemStatus = "System Ready";
}

// ---------------- Sensor Reading ----------------
void readSensors() {
  soilMoisture = analogRead(SOIL_MOISTURE_PIN);

  int tempSensorValue = analogRead(TMP36_PIN);
  float voltage = tempSensorValue * (5.0 / 1023.0); // Convert ADC to voltage
  temperature = (voltage - 0.5) * 100.0;            // TMP36 conversion

  // JSON-like structured log for IoT expansion
  Serial.print("{\"moisture\":");
  Serial.print(soilMoisture);
  Serial.print(",\"temp\":");
  Serial.print(temperature);
  Serial.println("}");
}

// ---------------- Watering Logic ----------------
void checkWateringConditions() {
  if (isWatering) {
    // Safety timeout
    if (millis() - wateringStartTime > MAX_IRRIGATION_TIME) {
      stopWatering("Time Limit");
      return;
    }

    // Moisture target reached → stop irrigation
    if (soilMoisture >= MOISTURE_THRESHOLD_HIGH) {
      stopWatering("Target Reached");
      return;
    }

    // Continue watering otherwise
    return;
  }

  // New cycle conditions
  bool needsWater = soilMoisture < MOISTURE_THRESHOLD_LOW;
  bool goodTemp = (temperature > TEMP_MIN && temperature < TEMP_MAX);

  if (needsWater && goodTemp) {
    startWatering();
  } else if (needsWater) {
    systemStatus = (temperature <= TEMP_MIN) ? "Too Cold" : "Too Hot";
  } else {
    systemStatus = "Soil Adequate";
  }
}

void startWatering() {
  if (digitalRead(RELAY_PUMP) != RELAY_OFF) {
    emergencyStop();
    systemStatus = "Pump Error";
    return;
  }

  Serial.println("STARTING WATERING CYCLE");
  openValves();
  delay(200); // Allow valves to open
  digitalWrite(RELAY_PUMP, RELAY_ON);

  if (digitalRead(RELAY_PUMP) != RELAY_ON) {
    emergencyStop();
    systemStatus = "Pump Failed";
    return;
  }

  digitalWrite(STATUS_LED, HIGH);
  isWatering = true;
  wateringStartTime = millis();
  systemStatus = "Watering";
}

void stopWatering(String reason) {
  Serial.print("STOPPING: "); Serial.println(reason);

  // 1. Pump OFF first
  digitalWrite(RELAY_PUMP, RELAY_OFF);

  // 2. Close valves
  closeValves();

  // 3. Update system state
  digitalWrite(STATUS_LED, LOW);
  isWatering = false;
  systemStatus = reason;

  // Verification
  if (digitalRead(RELAY_PUMP) != RELAY_OFF) {
    systemStatus = "Pump Error!";
    Serial.println("WARNING: Pump failed to turn off!");
  }

  Serial.print("Final Moisture: "); Serial.println(soilMoisture);
}

// ---------------- Valve Helpers ----------------
void openValves() {
  digitalWrite(RELAY_VALVE_1, RELAY_ON);
  digitalWrite(RELAY_VALVE_2, RELAY_ON);
  digitalWrite(RELAY_VALVE_3, RELAY_ON);
}

void closeValves() {
  digitalWrite(RELAY_VALVE_1, RELAY_OFF);
  digitalWrite(RELAY_VALVE_2, RELAY_OFF);
  digitalWrite(RELAY_VALVE_3, RELAY_OFF);
}

// ---------------- LCD Display ----------------
void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C ");
  lcd.print(isWatering ? "WATERING" : systemStatus);

  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(soilMoisture);

  if (isWatering) {
    int progress = map(soilMoisture, MOISTURE_THRESHOLD_LOW, MOISTURE_THRESHOLD_HIGH, 0, 100);
    progress = constrain(progress, 0, 100);
    lcd.print(" ");
    lcd.print(progress);
    lcd.print("%");
  } else {
    lcd.print(soilMoisture < MOISTURE_THRESHOLD_LOW ? " DRY" :
              soilMoisture > MOISTURE_THRESHOLD_HIGH ? " WET" : " OK");
  }
}

void showStartupMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("Pump Control");
  delay(2000);
}
