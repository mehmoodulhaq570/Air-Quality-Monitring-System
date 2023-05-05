// Include library for LCD and define pins
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define pins and variable for input sensor and output led and buzzer
const int mq135_aqi_sensor = A0;
const int green_led = 9;
const int red_led = 6;
const int orange_led = 7;

const int buzzer = 8;
int PIR = 13;  // Define PIR pin
int val = 0;

// Set threshold for AQI
int aqi_ppm = 0;
#include "DHT.h"

#define DHTPIN 10  // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT 11


DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // Set direction of input-output pins
  pinMode(mq135_aqi_sensor, INPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(orange_led, OUTPUT);

  pinMode(PIR, INPUT);
  pinMode(buzzer, OUTPUT);

  /*digitalWrite(green_led, LOW);
  digitalWrite(buzzer, LOW);
  // Initiate serial and lcd communication
  Serial.begin (9600);*/
  lcd.clear();
  lcd.begin(16, 2);

  Serial.println("AQI Alert System");
  //lcd.setCursor(0, 0);
  //lcd.print("Air quality");
  delay(3000);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  aqi_ppm = analogRead(mq135_aqi_sensor);


  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  val = digitalRead(PIR);  // The value read from PIR pin 3 will be assigned to 'val'
                           /*if(val == HIGH){
  digitalWrite(green_led, HIGH); // Turn LED ON
  digitalWrite(buzzer, HIGH); // Turn Buzzer ON
  Serial.println("Movement Detected"); // Print this text in Serial Monitor
}
else 
{
  digitalWrite(green_led, LOW);
  digitalWrite(buzzer, LOW);
  Serial.println("Movement not Detected");
}*/
  Serial.print("Air Quality:");
  Serial.println(aqi_ppm);
  Serial.print("Temperature : ");
  Serial.println(t);
  Serial.print("Humidity : ");
  Serial.println(h);
  Serial.print("Human Detection : ");
  Serial.println(val);

  lcd.setCursor(13, 1);
  lcd.print(aqi_ppm);
  lcd.setCursor(0, 0);
  lcd.println("T: ");
  lcd.setCursor(3, 0);
  lcd.print(int(t));
  lcd.setCursor(6, 0);
  lcd.println("H: ");
  lcd.setCursor(9, 0);
  lcd.print(int(h));
  lcd.setCursor(12, 0);
  lcd.print("D: ");
  lcd.setCursor(15, 0);
  lcd.print(val);


  if ((val == HIGH)) {
    digitalWrite(orange_led, HIGH);
    tone(buzzer, 1000, 200);
    Serial.println("Movement Detected");
    Serial.println(" ");
    lcd.print("D: ");
    lcd.setCursor(15, 0);
    lcd.print(val);


  } else if (t > 30) {
    tone(orange_led, 5000, 200);
    digitalWrite(buzzer, HIGH);
  } else if ((aqi_ppm >= 0) && (aqi_ppm <= 150)) {
    lcd.setCursor(0, 1);
    lcd.print("AQ is Good:");
    Serial.println("AQI Good");
    Serial.println(" ");
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, LOW);
    digitalWrite(orange_led, LOW);
    digitalWrite(buzzer, LOW);
  } else if ((aqi_ppm >= 150) && (aqi_ppm <= 300)) {
    lcd.setCursor(0, 1);
    lcd.print("AQ Modrate:");
    Serial.println("AQI Moderate");
    Serial.println(" ");
    tone(green_led, HIGH);
    digitalWrite(red_led, LOW);
    digitalWrite(orange_led, LOW);
    digitalWrite(buzzer, LOW);

  }

  else if ((aqi_ppm >= 300) && (aqi_ppm <= 450)) {
    lcd.setCursor(0, 1);
    lcd.print("AQ U Healt:");
    Serial.println("AQI Un Healthy");
    Serial.println(" ");
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, HIGH);
    digitalWrite(orange_led, LOW);
    digitalWrite(buzzer, LOW);
  }/* else if ((aqi_ppm >= 450) && (aqi_ppm <= 550)) {
    lcd.setCursor(0, 1);
    lcd.print("AQ V Un H:");
    Serial.println("AQI V. Un Healthy");
    Serial.println(" ");
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, HIGH);
    tone(buzzer, 1000, 200);
  }*/ else if (aqi_ppm >= 450) {
    lcd.setCursor(0, 1);
    lcd.print("AQ Hzardus:");
    Serial.println("AQI Hazardous");
    Serial.println(" ");
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, HIGH);
    digitalWrite(orange_led, LOW);
    digitalWrite(buzzer, HIGH);
  }
  delay(2000);
}