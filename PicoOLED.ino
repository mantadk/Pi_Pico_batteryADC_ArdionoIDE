#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int potPin = 26; // Analog pin

double convertToVoltage(int potValue) {
  return (potValue / 4096.0) * 3.3;
}

double backConvert (double Vout){
  return((Vout*(680+446)/446)+0.01);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  delay(1000); // Allow time for startup

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  double potValue = analogRead(potPin); // Correctly declare and read analog value
  double voltage = convertToVoltage(potValue);
  double originalVoltage = backConvert(voltage);
  display.clearDisplay();  // Clear the previous frame
  display.setCursor(0, 10);
  display.print("Raw ADC: ");
  display.println(potValue); // Fix variable name (was plotValue)
  display.print("Divided: ");
  display.print(voltage);
  display.println(" V");
  display.print("Original: ");
  display.print(originalVoltage);
  display.println(" V");
  display.display();  // Only call display() once per update

  delay(5000);
}
