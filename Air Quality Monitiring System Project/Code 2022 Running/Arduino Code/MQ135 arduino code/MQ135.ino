// Include library for LCD and define pins
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define pins and variable for input sensor and output led and buzzer
const int mq135_aqi_sensor = A0;
const int green_led = 9;
const int red_led = 6;
const int buzzer = 8;

// Set threshold for AQI
int aqi_ppm = 0;

void setup() {
  // Set direction of input-output pins
  pinMode (mq135_aqi_sensor, INPUT);
  pinMode (green_led, OUTPUT);
  pinMode (red_led, OUTPUT);

  pinMode (buzzer, OUTPUT);

  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);  
  digitalWrite(buzzer, LOW);

  // Initiate serial and lcd communication
  Serial.begin (9600);
  lcd.clear();
  lcd.begin (16, 2);

  Serial.println("AQI Alert System");
  lcd.setCursor(0, 0);
  lcd.print("AQI Alert System");
  delay(1000);
}

void loop() {
  aqi_ppm = analogRead(mq135_aqi_sensor);

  Serial.print("Air Quality: ");
  Serial.println(aqi_ppm);

  lcd.setCursor(0, 0);
  lcd.print("Air Quality: ");
  lcd.print(aqi_ppm);

  if ((aqi_ppm >= 0) && (aqi_ppm <= 150))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Good");
    Serial.println("AQI Good");
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, LOW);    
    digitalWrite(buzzer, LOW);
  }
  else if ((aqi_ppm >= 150) && (aqi_ppm <= 350))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Moderate");
    Serial.println("AQI Moderate");
    tone(green_led, 5000, 200);
    digitalWrite(buzzer, LOW);
  }

  else if ((aqi_ppm >= 350) && (aqi_ppm <= 450))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Unhealthy");
    Serial.println("AQI Unhealthy");
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, LOW);    
    digitalWrite(buzzer, LOW);
  }
  else if ((aqi_ppm >= 450) && (aqi_ppm <= 550))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI V. Unhealthy");
    Serial.println("AQI V. Unhealthy");
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, HIGH);
    tone(buzzer, 1000, 200);    
  }
  else if (aqi_ppm >= 550)
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Hazardous");
    Serial.println("AQI Hazardous");
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  delay (200);
}