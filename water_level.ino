#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

long duration;
int distance;

const int trigPIN = 11;
const int echoPIN = 10;
const int Distance_empty = 19;
const int Distance_full = 2;

void setup() {
  pinMode(trigPIN, OUTPUT);
  pinMode(echoPIN, INPUT);
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  //---------------------- HC-SR04-----------------------------//

  digitalWrite(trigPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPIN, LOW);
  duration = pulseIn(echoPIN, HIGH);


  //---------------------- Data processing -----------------------------//


  if (duration > 0) {
    distance = duration * 0.034 / 2;
    float truepercent = (float)(distance - Distance_empty) * 100.0 // (Distance_full - Distance_empty);
                        int percent = (int)truepercent;
    percent = constrain(percent, 0, 100);

    //---------------------- Display  -----------------------------//

    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.print(" cm ");

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);


    if (percent < 10) display.setCursor(50, 25);
    else if (percent < 100) display.setCursor(40, 25);
    else display.setCursor(30, 25);

    display.print(percent);
    display.print(" %");
    display.display();

    if (distance <= Distance_full) {
      Serial.println("Status: Full");
    } else if (distance >= Distance_empty) {
      Serial.println("Status: Empty");
    } else {
      Serial.println("Status: There is water");
    }
  }

  delay(500);
}
