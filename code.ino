#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DRV8833 Pins (ESP32-C3 SuperMini)
#define PIN_AIN1 0
#define PIN_AIN2 1
#define PIN_BIN1 7
#define PIN_BIN2 10

#define PIN_TOUCH  3
#define PIN_BUZZER 4

// PWM Settings
const int PWM_FREQ = 1000;
const int PWM_RES  = 8;

// Increased Motor Speeds (Pehle 135 tha, ab badha kar 165 kar diya)
const int CRUISE_SPEED = 165; 
const int TURN_SPEED   = 160;

void setMotorOutputs(int a1, int a2, int b1, int b2) {
  ledcWrite(PIN_AIN1, a1);
  ledcWrite(PIN_AIN2, a2);
  ledcWrite(PIN_BIN1, b1);
  ledcWrite(PIN_BIN2, b2);
}

void stopMotors() {
  setMotorOutputs(0, 0, 0, 0);
}

void moveForward() {
  setMotorOutputs(210, 0, 210, 0); // Quick kickstart pulse
  delay(30);
  setMotorOutputs(CRUISE_SPEED, 0, CRUISE_SPEED, 0);
}

void turnLeft() {
  setMotorOutputs(0, 200, 200, 0);
  delay(30);
  setMotorOutputs(0, TURN_SPEED, TURN_SPEED, 0);
}

void turnRight() {
  setMotorOutputs(200, 0, 0, 200);
  delay(30);
  setMotorOutputs(TURN_SPEED, 0, 0, TURN_SPEED);
}

// ==========================================
// BALANCED ANIMATIONS
// ==========================================
void eyeNormal() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 32, 5, SSD1306_BLACK);
  display.fillCircle(88, 32, 5, SSD1306_BLACK);
  display.fillCircle(43, 29, 2, SSD1306_WHITE);
  display.fillCircle(91, 29, 2, SSD1306_WHITE);
  display.display();
}

void eyeHappy() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 42, 16, SSD1306_BLACK);
  display.fillCircle(88, 42, 16, SSD1306_BLACK);
  display.display();
}

void eyeLookLeft() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(30, 32, 5, SSD1306_BLACK);
  display.fillCircle(78, 32, 5, SSD1306_BLACK);
  display.fillCircle(32, 29, 2, SSD1306_WHITE);
  display.fillCircle(80, 29, 2, SSD1306_WHITE);
  display.display();
}

void eyeLookRight() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(50, 32, 5, SSD1306_BLACK);
  display.fillCircle(98, 32, 5, SSD1306_BLACK);
  display.fillCircle(52, 29, 2, SSD1306_WHITE);
  display.fillCircle(100, 29, 2, SSD1306_WHITE);
  display.display();
}

void eyeLookUp() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 22, 5, SSD1306_BLACK);
  display.fillCircle(88, 22, 5, SSD1306_BLACK);
  display.display();
}

void eyeBlink() {
  display.clearDisplay();
  display.fillRoundRect(24, 31, 32, 5, 2, SSD1306_WHITE);
  display.fillRoundRect(72, 31, 32, 5, 2, SSD1306_WHITE);
  display.display();
}

void eyeWink() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 32, 5, SSD1306_BLACK);
  display.fillRoundRect(72, 31, 32, 5, 2, SSD1306_WHITE);
  display.display();
}

void drawSingleHeart(int x, int y) {
  display.fillCircle(x - 5, y, 6, SSD1306_WHITE);
  display.fillCircle(x + 5, y, 6, SSD1306_WHITE);
  display.fillTriangle(x - 11, y + 2, x + 11, y + 2, x, y + 15, SSD1306_WHITE);
}

void eyeLove() {
  display.clearDisplay();
  drawSingleHeart(40, 28);
  drawSingleHeart(88, 28);
  display.display();
}

void eyeShocked() {
  display.clearDisplay();
  display.fillCircle(40, 32, 22, SSD1306_WHITE);
  display.fillCircle(88, 32, 22, SSD1306_WHITE);
  display.fillCircle(40, 32, 8, SSD1306_BLACK);
  display.fillCircle(88, 32, 8, SSD1306_BLACK);
  display.display();
}

void eyeSleep(int frame) {
  display.clearDisplay();
  display.fillRoundRect(24, 32, 32, 6, 3, SSD1306_WHITE);
  display.fillRoundRect(72, 32, 32, 6, 3, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (frame == 0) {
    display.setCursor(108, 22); display.print("z");
  } else if (frame == 1) {
    display.setCursor(106, 16); display.print("Z");
    display.setCursor(114, 8);  display.print("z");
  } else {
    display.setCursor(102, 20); display.print("z");
    display.setCursor(110, 12); display.print("Z");
    display.setCursor(118, 4);  display.print("Z");
  }
  display.display();
}

void eyeSuspicious() {
  display.clearDisplay();
  display.fillRoundRect(24, 26, 32, 12, 4, SSD1306_WHITE);
  display.fillRoundRect(72, 26, 32, 12, 4, SSD1306_WHITE);
  display.fillCircle(40, 32, 3, SSD1306_BLACK);
  display.fillCircle(88, 32, 3, SSD1306_BLACK);
  display.display();
}

void eyeConfused() {
  display.clearDisplay();
  display.fillCircle(40, 32, 18, SSD1306_WHITE);
  display.fillCircle(40, 32, 6, SSD1306_BLACK);
  display.fillRoundRect(72, 28, 32, 10, 4, SSD1306_WHITE);
  display.display();
}

// ==========================================
// 5 DISTINCT SOUND EFFECTS
// ==========================================

// Sound 1: Wake-Up Alert
void soundWakeUp() {
  tone(PIN_BUZZER, 1800, 60); delay(70);
  tone(PIN_BUZZER, 2400, 70); delay(80);
  tone(PIN_BUZZER, 3200, 120); delay(130);
  noTone(PIN_BUZZER);
}

// Sound 2: Happy Arpeggio Chirp
void soundHappyChirp() {
  int melody[] = {2200, 2600, 3000, 3500};
  for (int i = 0; i < 4; i++) {
    tone(PIN_BUZZER, melody[i], 50);
    delay(60);
  }
  noTone(PIN_BUZZER);
}

// Sound 3: Questioning / Curious
void soundCurious() {
  tone(PIN_BUZZER, 2000, 80);
  delay(100);
  tone(PIN_BUZZER, 3000, 140);
  delay(150);
  noTone(PIN_BUZZER);
}

// Sound 4: Quick Playful Trill
void soundPlayful() {
  tone(PIN_BUZZER, 3200, 40); delay(45);
  tone(PIN_BUZZER, 2800, 40); delay(45);
  tone(PIN_BUZZER, 3600, 70); delay(80);
  noTone(PIN_BUZZER);
}

// Sound 5: Sleep Snore / Sigh
void soundSnore() {
  tone(PIN_BUZZER, 650, 160);
  delay(180);
  noTone(PIN_BUZZER);
}

// ==========================================
// SETUP & LOGIC
// ==========================================
bool isAsleep = false;
unsigned long lastActivityTime = 0;
unsigned long actionInterval = 3200;
int sleepFrame = 0;
unsigned long lastSleepAnim = 0;
int touchExpressionCounter = 0;

void setup() {
  pinMode(PIN_TOUCH, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  ledcAttach(PIN_AIN1, PWM_FREQ, PWM_RES);
  ledcAttach(PIN_AIN2, PWM_FREQ, PWM_RES);
  ledcAttach(PIN_BIN1, PWM_FREQ, PWM_RES);
  ledcAttach(PIN_BIN2, PWM_FREQ, PWM_RES);

  stopMotors();

  Wire.begin(8, 9);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  eyeNormal();

  lastActivityTime = millis();
}

void loop() {
  int touchState = digitalRead(PIN_TOUCH);

  // 1. TOUCH INTERACTION: Stop Motors + Different Sounds + Expression Cycling
  if (touchState == HIGH) {
    stopMotors();

    if (isAsleep) {
      isAsleep = false;
      eyeShocked();
      soundWakeUp();
      delay(400);
      eyeNormal();
    } else {
      // Cycle through different expressions AND different sounds
      touchExpressionCounter = (touchExpressionCounter + 1) % 6;

      if (touchExpressionCounter == 0) {
        eyeLove();
        soundHappyChirp();
      } else if (touchExpressionCounter == 1) {
        eyeWink();
        soundPlayful();
      } else if (touchExpressionCounter == 2) {
        eyeHappy();
        soundHappyChirp();
      } else if (touchExpressionCounter == 3) {
        eyeLookUp();
        soundCurious();
      } else if (touchExpressionCounter == 4) {
        eyeShocked();
        soundWakeUp();
      } else {
        eyeConfused();
        soundCurious();
      }
      
      delay(300); // Touch Debounce
    }

    lastActivityTime = millis();
    return;
  }

  // 2. SLEEP CHECK (15 second idle par sleep mode)
  if (!isAsleep && (millis() - lastActivityTime > 15000)) {
    stopMotors();
    isAsleep = true;
    eyeBlink();
    delay(250);
    eyeSleep(0);
    soundSnore();
  }

  // 3. SLEEP ANIMATION
  if (isAsleep) {
    if (millis() - lastSleepAnim > 1100) {
      lastSleepAnim = millis();
      sleepFrame = (sleepFrame + 1) % 3;
      eyeSleep(sleepFrame);
      if (sleepFrame == 2) {
        soundSnore();
      }
    }
    return;
  }

  // 4. AUTONOMOUS ROAMING (Faster Speed & Dynamic Steps)
  if (millis() - lastActivityTime > actionInterval) {
    lastActivityTime = millis();
    actionInterval = random(2800, 4500);

    int action = random(0, 5);

    if (action == 0) {
      stopMotors();
      eyeBlink();
      delay(120);
      eyeNormal();
    } else if (action == 1) {
      eyeLookLeft();
      turnLeft();
      delay(200);
      stopMotors();
    } else if (action == 2) {
      eyeLookRight();
      turnRight();
      delay(200);
      stopMotors();
    } else if (action == 3) {
      eyeNormal();
      moveForward();
      delay(320); // Steady glide
      stopMotors();
    } else {
      stopMotors();
      soundCurious();
      eyeConfused();
      delay(350);
      eyeNormal();
    }
  }
}
