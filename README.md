# Automated Irrigation System

An IoT-based personal project for automating agricultural irrigation using Arduino microcontrollers. This system intelligently monitors soil moisture and environmental conditions to automatically control water distribution, reducing water waste and improving crop health.

## 🌾 Overview

The Automated Irrigation System is a smart farming solution designed to optimize water usage in agriculture. Using Arduino-compatible microcontrollers, soil moisture sensors, and automated valve controls, this system provides a cost-effective way to ensure crops receive optimal hydration levels automatically.

## ✨ Features

- **Soil Moisture Monitoring**: Real-time soil moisture detection via capacitive/resistive sensors
- **Automatic Watering**: Triggers irrigation when soil moisture falls below a configurable threshold
- **IoT Connectivity**: Remote monitoring and control capabilities
- **Water Efficiency**: Reduces water waste by delivering precise amounts of water
- **Low Power Consumption**: Optimized for continuous operation
- **Customizable Thresholds**: Adjust moisture levels based on crop type and season
- **Data Logging**: Track watering cycles and environmental data

## 🛠️ Hardware Requirements

- **Microcontroller**: Arduino Uno, Arduino Mega, or compatible board
- **Soil Moisture Sensor**: Capacitive or resistive soil moisture sensor
- **Water Pump/Valve**: 12V DC pump or solenoid valve
- **Relay Module**: 1-channel or multi-channel relay for pump control
- **Power Supply**: 12V DC power supply for pump and relay
- **Optional Components**:
  - Temperature/Humidity sensor (DHT22)
  - Real-time clock module (DS3231)
  - GSM/WiFi module for remote monitoring
  - LCD/OLED display for status

## 📋 Prerequisites

- Arduino IDE or PlatformIO
- Basic knowledge of Arduino programming
- Understanding of circuit design and electrical safety

## 🚀 Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/kamunyuraphael/Automated-Irrigation-System-.git
cd Automated-Irrigation-System-
```

### 2. Hardware Setup
- Connect soil moisture sensor to Arduino analog input (A0)
- Connect relay module to Arduino digital output (D8)
- Connect water pump/valve through relay module
- Power the system with appropriate voltage regulators

### 3. Upload Code
1. Open Arduino IDE
2. Load the main sketch from the project
3. Select your Arduino board and COM port
4. Click Upload

### 4. Configure Settings
Adjust these parameters in the code:
- `MOISTURE_THRESHOLD`: Soil moisture level to trigger watering
- `SENSOR_DRY_VALUE`: ADC value when sensor is completely dry
- `SENSOR_WET_VALUE`: ADC value when sensor is completely wet
- `PUMP_RUN_TIME`: Duration to run pump in seconds

## 📁 Project Structure

```
Automated-Irrigation-System-/
├── README.md
├── src/
│   ├── main.ino              # Main Arduino sketch
│   ├── sensors.cpp           # Sensor reading functions
│   └── pump_control.cpp      # Pump/valve control functions
├── circuit/
│   └── schematic.pdf         # Circuit diagram
├── docs/
│   ├── SETUP.md              # Detailed setup guide
│   └── TROUBLESHOOTING.md    # Common issues and solutions
└── LICENSE
```

## 🔧 Configuration

Edit the following constants in `main.ino`:

```cpp
#define SOIL_MOISTURE_PIN A0
#define PUMP_RELAY_PIN 8
#define MOISTURE_THRESHOLD 400
#define PUMP_ON_TIME 5000  // milliseconds
```

## 📊 How It Works

1. **Reading**: Continuously reads analog input from soil moisture sensor
2. **Comparison**: Compares current moisture level with threshold value
3. **Activation**: If moisture falls below threshold, activates pump
4. **Timing**: Pump runs for a set duration, then stops
5. **Monitoring**: Waits for soil moisture to restore before next cycle

## 🐛 Troubleshooting

- **Pump doesn't activate**: Check relay connections and power supply
- **Inaccurate readings**: Calibrate sensor with dry and wet soil samples
- **Continuous watering**: Increase moisture threshold or check for sensor issues

See [TROUBLESHOOTING.md](docs/TROUBLESHOOTING.md) for more details.

## 📚 Learning Resources

- [Arduino Official Documentation](https://www.arduino.cc/reference/)
- [IoT Basics](https://en.wikipedia.org/wiki/Internet_of_things)
- [Smart Agriculture](https://en.wikipedia.org/wiki/Precision_agriculture)

## 🤝 Contributing

Contributions are welcome! Please feel free to:
- Report bugs and issues
- Suggest new features
- Submit pull requests with improvements
- Improve documentation

## 📝 License

This project is open source. See LICENSE file for details (if applicable).

## 👤 Author

**Raphael Kamunyua**  
- GitHub: [@kamunyuraphael](https://github.com/kamunyuraphael)

## 🌟 Future Enhancements

- [ ] WiFi/IoT connectivity for remote monitoring
- [ ] Mobile app for control and notifications
- [ ] Multiple zone support for larger irrigation areas
- [ ] Weather integration to skip watering during rain
- [ ] Data visualization dashboard
- [ ] ML-based optimal watering schedules

## ⚠️ Safety Notes

- Always use proper power supplies with adequate voltage regulators
- Ensure all electrical connections are properly insulated
- Test the system with a controlled water source before full deployment
- Follow local electrical and agricultural regulations

---

**Happy automated farming! 🌱**
