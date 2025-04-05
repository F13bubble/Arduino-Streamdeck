#include <Keyboard.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#define NUM_BUTTONS 12
const int buttonPins[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 15, 14};


#define LED_PIN     18       // data-pin of led strip
#define NUM_LEDS    3       // number of LEDs

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int colorIndex = 0;
bool lastButtonState = LOW;

uint8_t actions[NUM_BUTTONS];

void loadActionsFromEEPROM() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    actions[i] = EEPROM.read(i);
  }
}

void performAction(uint8_t actionID) {
  switch (actionID) {
    case 1: // Copy
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 2: // Paste
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 3: // Cut
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('x');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 4: // Lock Screen
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('l');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 5: // Task Manager
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_ESC);
      delay(100);
      Keyboard.releaseAll();
      break;
    case 6: // Open Chrome
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("chrome");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    case 7: // Open Notepad
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("notepad");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    case 8: // Open Code
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("code");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    case 9: // Open cmd
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("cmd");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    case 10: // Desktop
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('d');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 11: // Screenshot
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 12: // Play/Pause
      Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
      delay(100);
      Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
      break;
    case 13: // next track
      Keyboard.press(KEY_MEDIA_NEXT_TRACK);
      delay(100);
      Keyboard.release(KEY_MEDIA_NEXT_TRACK);
      break;
    case 14: // previous track
      Keyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
      delay(100);
      Keyboard.release(KEY_MEDIA_PREVIOUS_TRACK);
      break;
    case 15: // PowerToys color picker
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('c');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 16: // PowerToys Text extractor
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('t');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 17: // PowerToys Screen ruler
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('m');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 18: // PowerToys Always on top
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('t');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 19: // Git Push
      Keyboard.print("git push");
      Keyboard.write(KEY_RETURN);
      break;
    case 20: // Git Pull
      Keyboard.print("git pull");
      Keyboard.write(KEY_RETURN);
      break;
    case 21: // Mute
      Keyboard.press(KEY_MEDIA_MUTE);
      delay(100);
      Keyboard.release(KEY_MEDIA_MUTE);
      break;
    default:
      if (actionID >= 100) {
        Keyboard.write((char)(actionID - 100));
      }
  }
}

void setup() {
  Keyboard.begin();
  strip.begin();
  strip.show(); // all leds off
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  loadActionsFromEEPROM();
  Serial.begin(9600);
}

void loop() {
  static bool pressed[NUM_BUTTONS] = {false};

  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool isPressed = digitalRead(buttonPins[i]) == LOW;
    if (isPressed && !pressed[i]) {
      if (i == 10){
        colorIndex++;
        if (colorIndex > 6) colorIndex = 0;
        setColor(colorIndex);
      }
      else {
        Serial.print(i);
        performAction(actions[i]);
        pressed[i] = true;
      }
      delay(200);
    } else if (!isPressed && pressed[i]) {
      pressed[i] = false;
    }
  }

  // Mapping via Serial: "5:2\n" means key 5 -> action 2 (paste)
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int sep = input.indexOf(':');
    if (sep > 0 && sep < input.length() - 1) {
      int btn = input.substring(0, sep).toInt();
      int act = input.substring(sep + 1).toInt();
      if (btn >= 0 && btn < NUM_BUTTONS) {
        actions[btn] = (uint8_t)act;
        EEPROM.write(btn, act);
        Serial.println("OK");
      }
    }
  }
}

void setColor(int index) {
  uint32_t color;

  switch (index) {
    case 0: color = strip.Color(255, 0, 0); break;    // red
    case 1: color = strip.Color(0, 255, 0); break;    // green
    case 2: color = strip.Color(0, 0, 255); break;    // blue
    case 3: color = strip.Color(255, 255, 0); break;  // yellow
    case 4: color = strip.Color(255, 0, 255); break;  // pink
    case 5: color = strip.Color(255, 255, 255); break;  // White
    case 6: color = strip.Color(0, 0, 0); break;  // off
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}