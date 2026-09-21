#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DRV8833 Motor Driver Pins
#define PIN_IN1 0
#define PIN_IN2 1
#define PIN_IN3 7  // BIN1 ke liye GPIO 7 use karein
#define PIN_IN4 10

// Sensor & Buzzer Pins
#define PIN_TOUCH  3
#define PIN_BUZZER 4

// Motor Control Functions
void stopMotors() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
}

void moveForward() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
}

void turnRight() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
}

// OLED Eyes Animation Functions
void drawNormalEyes() {
  display.clearDisplay();
  display.fillRoundRect(25, 18, 28, 32, 10, SSD1306_WHITE);
  display.fillRoundRect(75, 18, 28, 32, 10, SSD1306_WHITE);
  display.display();
}

void drawLookingUpEyes() {
  display.clearDisplay();
  display.fillRoundRect(25, 6, 28, 28, 10, SSD1306_WHITE);
  display.fillRoundRect(75, 6, 28, 28, 10, SSD1306_WHITE);
  display.display();
}

void drawBlinkEyes() {
  display.clearDisplay();
  display.fillRoundRect(25, 30, 28, 6, 3, SSD1306_WHITE);
  display.fillRoundRect(75, 30, 28, 6, 3, SSD1306_WHITE);
  display.display();
}

// Cute Sound on Touch
void playHappySound() {
  int notes[] = {800, 1200, 1600, 2000};
  for (int i = 0; i < 4; i++) {
    tone(PIN_BUZZER, notes[i], 60);
    delay(70);
  }
  noTone(PIN_BUZZER);
}

void setup() {
  // Motor driver pins setup
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  stopMotors();

  // Touch and Buzzer pins setup
  pinMode(PIN_TOUCH, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  // I2C Setup for ESP32-C3 SuperMini (SDA: 8, SCL: 9)
  Wire.begin(8, 9);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Agar screen na chale toh 0x3D try karein
  }

  display.clearDisplay();
  drawNormalEyes();
}

unsigned long roamTimer = 0;
int botState = 0;

void loop() {
  // 1. Touch Action Check
  if (digitalRead(PIN_TOUCH) == HIGH) {
    stopMotors();          // Pehle gaadi roko
    playHappySound();      // Sound effect
    drawLookingUpEyes();   // Upar dekhna
    delay(300);
    drawBlinkEyes();       // Blink
    delay(200);
    drawNormalEyes();
    delay(400);

    roamTimer = millis();  // Timer reset
  }

  // 2. Autonomous Roaming (Har 2.5 second me random action)
  if (millis() - roamTimer > 2500) {
    roamTimer = millis();
    botState = random(0, 3); // 0 = Aage, 1 = Turn, 2 = Rukna

    if (botState == 0) {
      moveForward();
      drawNormalEyes();
    } else if (botState == 1) {
      turnRight();
      drawBlinkEyes();
      delay(150);
      drawNormalEyes();
    } else {
      stopMotors();
      drawNormalEyes();
    }
  }
}
