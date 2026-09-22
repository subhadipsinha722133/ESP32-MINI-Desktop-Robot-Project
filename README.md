# 🤖 Cute Desktop Assistant Robot

Yeh ek chhota, smart aur expressive desktop companion robot hai jo ESP32-C3 SuperMini par chalta hai. Yeh robot ek 80x40 cm desk par aaram se bina gire ghoom sakta hai, 0.96" OLED screen par cute animated expressions dikhata hai, capacitive touch sensor se interact karta hai, aur buzzer ke zariye cute sounds nikaalta hai.

---

## ✨ Features

- **Autonomous Roaming:** 80x40 cm desk ke hisaab se tuned short safe-steps (glide, turn, stop).
- **15+ OLED Expressions:** Normal, Happy, Blink, Wink, Look Left/Right, Look Up, Love Hearts, Shocked, Sleepy with Zzz, Suspicious, Confused, etc.
- **Sleep & Wake-up System:** 15 seconds idle rehne par robot screen par Zzz animation ke sath so jata hai aur soft snore sound nikaalta hai.
- **Touch Interaction:** TTP223 sensor ko touch karte hi robot turant rukta hai, wake-up hota hai, aur alag-alag cute tones ke sath expressions cycle karta hai.
- **Smart Motor Kickstart:** Low speed par micro gear motors ko jam hone se bachane ke liye PWM kickstart pulse feature.

---

## 🛠️ Hardware Components

| S.No | Component | Description |
| :--- | :--- | :--- |
| 1 | **ESP32-C3 SuperMini** | Main Microcontroller (Wi-Fi + BLE) |
| 2 | **0.96" I2C OLED Display** | SSD1306 (128x64 resolution) |
| 3 | **DRV8833 Motor Driver** | Dual H-Bridge Motor Driver Module (V318 pinout) |
| 4 | **2x DC Gear Motors + Wheels** | N20 Micro Gear Motors (6V) |
| 5 | **TTP223 Touch Sensor** | Capacitive Touch Module |
| 6 | **Passive Buzzer** | 5V B10 Buzzer |
| 7 | **Power Supply** | 3.7V Li-Po (with 5V Booster) ya 7.4V Battery (with Buck Converter set to 5V) |

---

## 🔌 Pinout & Wiring Diagram

### 1. Power Distribution
- **Booster / Buck Converter (5V Out):** ESP32-C3 `5V` pin aur DRV8833 ke `VM` pin par.
- **Common Ground (GND):** Saare components ka GND aapas mein common karke ESP32 ke `GND` se jodna hai.

### 2. Signal Connections (ESP32-C3 SuperMini)

| Component | Pin | ESP32-C3 Pin | Remarks |
| :--- | :--- | :--- | :--- |
| **OLED Display** | SDA | GPIO 8 | I2C Data |
| | SCL | GPIO 9 | I2C Clock |
| | VCC | 3V3 | Power |
| | GND | GND | Ground |
| **DRV8833 Driver** | AIN1 | GPIO 0 | Left Motor PWM |
| | AIN2 | GPIO 1 | Left Motor PWM |
| | BIN1 | GPIO 7 | Right Motor PWM (GPIO 2 avoid kiya gaya hai) |
| | BIN2 | GPIO 10 | Right Motor PWM |
| | STBY | 3V3 | Active High (Always ON) |
| | AO1, AO2 | - | Left DC Motor Wires |
| | BO1, BO2 | - | Right DC Motor Wires |
| **Touch Sensor** | SIG / OUT | GPIO 3 | Digital Input |
| | VCC | 3V3 | Power |
| | GND | GND | Ground |
| **Passive Buzzer**| Positive (+) | GPIO 4 | Tone output |
| | Negative (-) | GND | Ground |

---

## 💻 Software & Libraries

Arduino IDE mein code upload karne ke liye yeh libraries install karein:
1. **Adafruit SSD1306** (`Sketch -> Include Library -> Manage Libraries`)
2. **Adafruit GFX Library**

### Board Settings (Arduino IDE):
- **Board:** `ESP32C3 Dev Module`
- **USB CDC On Boot:** `Enabled`
- **Flash Size:** `4MB`

---

## 🚀 How to Run

1. Saari wiring tables ke mutabiq verify karein (Khas kar `STBY` pin ko 3.3V se connect rakhein).
2. Arduino IDE mein code paste karein aur upload karein.
3. Power on karein; robot normal eyes dikhayega aur gentle desk roaming start karega.
4. Robot ke head par touch karke playful reactions aur sounds check karein.
