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

// Motor Speeds (Wahi same rakhay gaye hain, no changes)
const int CRUISE_SPEED = 135; 
const int TURN_SPEED   = 130;

void setMotorOutputs(int a1, int a2, int b1, int b2) {
  ledcWrite(PIN_AIN1, a1);
  ledcWrite(PIN_AIN2, a2);
  ledcWrite(PIN_BIN1, b1);
  ledcWrite(PIN_BIN2, b2);
}

void stopMotors() {
  setMotorOutputs(0, 0, 0, 0);
}

void moveForwardSlow() {
  setMotorOutputs(180, 0, 180, 0);
  delay(25);
  setMotorOutputs(CRUISE_SPEED, 0, CRUISE_SPEED, 0);
}

void turnLeftSlow() {
  setMotorOutputs(0, 170, 170, 0);
  delay(25);
  setMotorOutputs(0, TURN_SPEED, TURN_SPEED, 0);
}

void turnRightSlow() {
  setMotorOutputs(170, 0, 0, 170);
  delay(25);
  setMotorOutputs(TURN_SPEED, 0, 0, TURN_SPEED);
}

// ==========================================
// BALANCED & CENTERED ANIMATIONS (128x64)
// Center Left Eye: X=24, Width=32
// Center Right Eye: X=72, Width=32
// ==========================================

// 1. Normal Big Cute Eyes (Center Pupil)
void eyeNormal() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  // Pupils centered
  display.fillCircle(40, 32, 5, SSD1306_BLACK);
  display.fillCircle(88, 32, 5, SSD1306_BLACK);
  // Sparkle dots
  display.fillCircle(43, 29, 2, SSD1306_WHITE);
  display.fillCircle(91, 29, 2, SSD1306_WHITE);
  display.display();
}

// 2. Happy Curved Eyes
void eyeHappy() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 42, 16, SSD1306_BLACK);
  display.fillCircle(88, 42, 16, SSD1306_BLACK);
  display.display();
}

// 3. Look Left (Dono pupil perfectly Left side)
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

// 4. Look Right (Dono pupil perfectly Right side)
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

// 5. Look Up (Upar dekhna)
void eyeLookUp() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillRoundRect(72, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 22, 5, SSD1306_BLACK);
  display.fillCircle(88, 22, 5, SSD1306_BLACK);
  display.display();
}

// 6. Natural Blink
void eyeBlink() {
  display.clearDisplay();
  display.fillRoundRect(24, 31, 32, 5, 2, SSD1306_WHITE);
  display.fillRoundRect(72, 31, 32, 5, 2, SSD1306_WHITE);
  display.display();
}

// 7. Wink (Left open, Right wink)
void eyeWink() {
  display.clearDisplay();
  display.fillRoundRect(24, 14, 32, 36, 10, SSD1306_WHITE);
  display.fillCircle(40, 32, 5, SSD1306_BLACK);
  display.fillRoundRect(72, 31, 32, 5, 2, SSD1306_WHITE);
  display.display();
}

// 8. Love / Heart Eyes
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

// 9. Shocked / Alert Big Circles
void eyeShocked() {
  display.clearDisplay();
  display.fillCircle(40, 32, 22, SSD1306_WHITE);
  display.fillCircle(88, 32, 22, SSD1306_WHITE);
  display.fillCircle(40, 32, 8, SSD1306_BLACK);
  display.fillCircle(88, 32, 8, SSD1306_BLACK);
  display.display();
}

// 10. Sleep with Zzz
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

// 11. Suspicious / Focused Squint
void eyeSuspicious() {
  display.clearDisplay();
  display.fillRoundRect(24, 26, 32, 12, 4, SSD1306_WHITE);
  display.fillRoundRect(72, 26, 32, 12, 4, SSD1306_WHITE);
  display.fillCircle(40, 32, 3, SSD1306_BLACK);
  display.fillCircle(88, 32, 3, SSD1306_BLACK);
  display.display();
}

// 12. Confused
void eyeConfused() {
  display.clearDisplay();
  display.fillCircle(40, 32, 18, SSD1306_WHITE);
  display.fillCircle(40, 32, 6, SSD1306_BLACK);
  display.fillRoundRect(72, 28, 32, 10, 4, SSD1306_WHITE);
  display.display();
}

// Expression Selector
void showExpression(int id) {
  switch (id) {
    case 0: eyeNormal(); break;
    case 1: eyeHappy(); break;
    case 2: eyeLookLeft(); break;
    case 3: eyeLookRight(); break;
    case 4: eyeLookUp(); break;
    case 5: eyeWink(); break;
    case 6: eyeLove(); break;
    case 7: eyeShocked(); break;
    case 8: eyeSuspicious(); break;
    case 9: eyeConfused(); break;
    default: eyeNormal(); break;
  }
}

// ==========================================
// BUZZER SOUNDS
// ==========================================
void soundWakeUp() {
  tone(PIN_BUZZER, 2000, 70); delay(80);
  tone(PIN_BUZZER, 2600, 90); delay(100);
  tone(PIN_BUZZER, 3300, 130); delay(140);
  noTone(PIN_BUZZER);
}

void soundTouchTone() {
  tone(PIN_BUZZER, 2800, 50); delay(60);
  tone(PIN_BUZZER, 3500, 80); delay(90);
  noTone(PIN_BUZZER);
}

void soundSnore() {
  tone(PIN_BUZZER, 700, 180); delay(200);
  noTone(PIN_BUZZER);
}

// ==========================================
// SETUP & MAIN LOOP
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

  // 1. TOUCH EVENT: Turant Motor Stop + Naya Expression + Cute Sound
  if (touchState == HIGH) {
    stopMotors(); // Turant gaadi roko

    if (isAsleep) {
      isAsleep = false;
      eyeShocked();
      soundWakeUp();
      delay(400);
      eyeNormal();
    } else {
      soundTouchTone();
      // Har bar touch karne par expression cycle hoga (Love, Wink, Happy, Confused, Up, etc.)
      touchExpressionCounter = (touchExpressionCounter + 1) % 7;
      if (touchExpressionCounter == 0) eyeLove();
      else if (touchExpressionCounter == 1) eyeWink();
      else if (touchExpressionCounter == 2) eyeHappy();
      else if (touchExpressionCounter == 3) eyeLookUp();
      else if (touchExpressionCounter == 4) eyeShocked();
      else if (touchExpressionCounter == 5) eyeConfused();
      else eyeSuspicious();
      
      delay(300); // Debounce
    }

    lastActivityTime = millis(); // Reset activity timer
    return;
  }

  // 2. SLEEP CHECK (15 second tak koi activity na ho toh so jaye)
  if (!isAsleep && (millis() - lastActivityTime > 15000)) {
    stopMotors();
    isAsleep = true;
    eyeBlink();
    delay(250);
    eyeSleep(0);
    soundSnore();
  }

  // 3. SLEEP ANIMATION (Zzz looping)
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

  // 4. DESKTOP WANDERING & CHANGING EXPRESSIONS
  if (millis() - lastActivityTime > actionInterval) {
    lastActivityTime = millis();
    actionInterval = random(3000, 5000);

    int action = random(0, 5);

    if (action == 0) {
      stopMotors();
      // Natural blink karke center dekhega
      eyeBlink();
      delay(120);
      eyeNormal();
    } else if (action == 1) {
      // Left dekhna aur left thoda sa ghoomna
      eyeLookLeft();
      turnLeftSlow();
      delay(180);
      stopMotors();
    } else if (action == 2) {
      // Right dekhna aur right thoda sa ghoomna
      eyeLookRight();
      turnRightSlow();
      delay(180);
      stopMotors();
    } else if (action == 3) {
      // Aage chalna
      eyeNormal();
      moveForwardSlow();
      delay(250);
      stopMotors();
    } else {
      stopMotors();
      int randEye = random(0, 10);
      showExpression(randEye);
    }
  }
}
