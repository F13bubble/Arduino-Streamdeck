#include <Keyboard.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#define NUM_BUTTONS 12
const int buttonPins[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};


#define LED_PIN     18       // data-pin of led strip
#define NUM_LEDS    3       // number of LEDs

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int colorIndex = 0;
bool lastButtonState = LOW;
int rainbowHue = 0;
unsigned long lastRainbowUpdate = 0;
unsigned long rainbowDelay = 100; // time between each step

uint8_t actions[NUM_BUTTONS];

void loadActionsFromEEPROM() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    actions[i] = EEPROM.read(i);
    Serial.println(actions[i]);
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
      Keyboard.press(KEY_PRINT_SCREEN);
      delay(100);
      Keyboard.releaseAll();
      break;
    // case 12: // Play/Pause
    //   Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    //   delay(100);
    //   Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
    //   break;
    // case 13: // next track
    //   Keyboard.press(KEY_MEDIA_NEXT_TRACK);
    //   delay(100);
    //   Keyboard.release(KEY_MEDIA_NEXT_TRACK);
    //   break;
    // case 14: // previous track
    //   Keyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
    //   delay(100);
    //   Keyboard.release(KEY_MEDIA_PREVIOUS_TRACK);
    //   break;
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
    // case 21: // Mute
    //   Keyboard.press(KEY_MEDIA_MUTE);
    //   delay(100);
    //   Keyboard.release(KEY_MEDIA_MUTE);
    //   break;
    case 22: // screenshot select
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 23: //shutdown
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("shutdown /s");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    case 24: // reboot
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("shutdown /g /f /t 0");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    case 25: // hybernate
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(300);
      Keyboard.print("shutdown /h");
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
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
      if (i == 11){
        // if (actions[11]){
        //   Serial.println("something is saved.");
        //   Serial.print(actions[i]);
        //   performAction(actions[i]);
        //   pressed[i] = true;
        // }
        colorIndex++;
        if (colorIndex > 13) colorIndex = 0;
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
  if (colorIndex == 12) {
    rainbowFadeStep();
  }
}
void rainbowGradient(uint32_t colorStart, uint32_t colorEnd) {
  for (int i = 0; i < NUM_LEDS; i++) {
    float t = (float)i / (NUM_LEDS - 1); // value from 0.0 to 1.0

    // Split the start and end colors into RGB
    byte r1 = (colorStart >> 16) & 0xFF;
    byte g1 = (colorStart >> 8) & 0xFF;
    byte b1 = colorStart & 0xFF;

    byte r2 = (colorEnd >> 16) & 0xFF;
    byte g2 = (colorEnd >> 8) & 0xFF;
    byte b2 = colorEnd & 0xFF;

    // Interpolate
    byte r = r1 + (r2 - r1) * t;
    byte g = g1 + (g2 - g1) * t;
    byte b = b1 + (b2 - b1) * t;

    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
void rainbowFadeStep() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastRainbowUpdate >= rainbowDelay) {
    lastRainbowUpdate = currentMillis;

    uint32_t color = strip.ColorHSV(rainbowHue, 255, 255);

    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();

    rainbowHue += 256;
    if (rainbowHue > 65535) rainbowHue = 0;
  }
}


void setColor(int index) {
  uint32_t color;
  bool multi = false;

  switch (index) {
    case 0: color = strip.Color(255, 0, 0); break;    // red
    case 1: color = strip.Color(0, 255, 0); break;    // green
    case 2: color = strip.Color(0, 0, 255); break;    // blue
    case 3: color = strip.Color(255, 255, 0); break;  // yellow
    case 4: color = strip.Color(255, 0, 255); break;  // pink
    case 5: color = strip.Color(0, 255, 255); break;  // cyan
    case 6: color = strip.Color(0, 140, 135); break;  // cyan dark
    case 7: color = strip.Color(255, 255, 255); break;  // White
    case 8: rainbowGradient(strip.Color(255, 0, 0), strip.Color(0, 0, 255)); multi = true; break; // red → blue
    case 9: rainbowGradient(strip.Color(0, 255, 0), strip.Color(0, 0, 255)); multi = true; break; // green → blue
    case 10: rainbowGradient(strip.Color(255, 255, 0), strip.Color(255, 0, 0)); multi = true; break; // yellow → red
    case 11: rainbowGradient(strip.Color(0, 255, 0), strip.Color(255, 0, 0)); multi = true; break; // green → red
    case 12: rainbowFadeStep(); multi = true; break;
    case 13: color = strip.Color(0, 0, 0); break;  // off
  }
  
  if (multi == false){
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, color);
    }
  }
  
  strip.show();
}