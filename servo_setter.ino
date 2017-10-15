#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int buttonPinP10 = 2;
const int buttonPinP1 = 3;
const int buttonPinRes = 4;
const int buttonPinM1 = 5;
const int buttonPinM10 = 6;

const int ServoPin = 8;

int degree = 0;
Servo testServo;

void setup()   {       
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  pinMode(buttonPinP10, INPUT);
  pinMode(buttonPinP1, INPUT);
  pinMode(buttonPinRes, INPUT);
  pinMode(buttonPinM1, INPUT);
  pinMode(buttonPinM10, INPUT);
}

void loop() {
  bool buttonPressed = false;
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  if(digitalRead(buttonPinP10)) {
    display.println("\n +10 button pressed");
    degree += 10;
    if(degree > 180)
      degree=180;
    buttonPressed = true;
  } else if(digitalRead(buttonPinP1)) {
    display.println("\n +1  button pressed");
    degree += 1;
    if(degree > 180)
      degree=180;
    buttonPressed = true;
  } else if(digitalRead(buttonPinRes)) {
    display.println("\n res button pressed");
    degree = 90;
    buttonPressed = true;
  } else if(digitalRead(buttonPinM1)) {
    display.println("\n -1  button pressed");
    degree -= 1;
    if(degree < 0)
      degree=0;
    buttonPressed = true;
  } else if(digitalRead(buttonPinM10)) {
    display.println("\n -10 button pressed");
    degree -= 10;
    if(degree < 0)
      degree=0;
    buttonPressed = true;
  } else {
    display.println("\n no  button pressed");
    display.print("   - set servo ");display.print(degree);display.println(" -");
  }
  if(buttonPressed){
    testServo.attach(ServoPin);
    testServo.write(degree);
    display.print("   - set servo ");display.print(degree);display.println(" -");
    buttonPressed = false;
  }
  display.display();
  delay(1000);
  testServo.detach();
  display.clearDisplay();
}
