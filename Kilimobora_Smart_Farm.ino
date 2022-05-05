#include "DHT.h"
#include <LiquidCrystal.h>


float temperature;
int flameDetected;
int gasValue;
float moistureLevel;

// ACTUATOR PINS
int RELAY_FAN_PIN = 9; // Arduino pin connected to relay which connected to fan
int RELAY_PUMP_PIN = 13;
int RELAY_ALARM_PIN = 5;

//
//// LCD DISPLAY CONSTANT
//#define LCD_OUT_PIN_1 A0 // LCD Analog display pin 1
//#define LCD_OUT_PIN_2 A1 // LCD Analog display pin 2

// TEMPERATURE SENSOR CONSTANTS
#define DHTPIN A5 
#define DHTTYPE DHT11 

// SOIL MOISTURE 
int SOIL_MOISTURE_IN = 10;

// FIRE DETECTOR
int FLAME_IN = 7;

//
// // GAS DETECTOR
int GAS_IN = 8;
// #define GAS_IN D8
 
DHT dht(DHTPIN, DHTTYPE);// Arduino pin connected to relay which connected to DHT sensor



const int TEMP_THRESHOLD_UPPER = 25; // upper threshold of temperature, change to your desire value
const int TEMP_THRESHOLD_LOWER = 20; // lower threshold of temperature, change to your desire value
const int MOISTURE_THRESHOLD_UPPER = 10;
const int GAS_THRESHOLD_UPPER = 1;
 
void setup() {
  Serial.begin(9600);

  // Flame Related pins both in and out.
  pinMode(FLAME_IN,INPUT);
  pinMode(RELAY_ALARM_PIN, OUTPUT);
  
  // Initialization of dht instance
  dht.begin();  

  // Soil Moisture pins both in and out
  pinMode(SOIL_MOISTURE_IN, INPUT);
  pinMode(RELAY_PUMP_PIN, OUTPUT);

  // Gas Reading
  pinMode(GAS_IN, INPUT);
          
  pinMode(RELAY_FAN_PIN, OUTPUT); // initialize digital pin as an output
  Serial.println("Reading From the Sensor ...");

  delay(2000);

}

void loop() {
  coolingSystem();
  moistureReading();
  fireAlertSystem();
  gasDetection();


  

}

void coolingSystem(){
  delay(2000);

  temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read temp");
  }
  if (temperature >= TEMP_THRESHOLD_UPPER) {
    Serial.println(temperature);
    digitalWrite(RELAY_FAN_PIN, HIGH);
    Serial.println("FAN ON");
  }
}

void moistureReading() {
  delay(2000);
  moistureLevel = digitalRead(SOIL_MOISTURE_IN);
  if (isnan(moistureLevel)) {
    Serial.println("Failed to read temp"); 
  }
  if (moistureLevel <= MOISTURE_THRESHOLD_UPPER) {
    Serial.println("Moisture Reading");
    Serial.println(moistureLevel);
    digitalWrite(RELAY_PUMP_PIN, HIGH);
    Serial.println("PUMP ON");
     
  }
  
}
void fireAlertSystem() {
  delay(2000);
  flameDetected = digitalRead(FLAME_IN);
  if(flameDetected) {
    digitalWrite(RELAY_ALARM_PIN, HIGH);
  }
  
}

void gasDetection() {
  delay(3000);
  gasValue = analogRead(GAS_IN);
  if (gasValue >= GAS_THRESHOLD_UPPER) {
    Serial.println("Gas Reading");
    Serial.println(gasValue);
    digitalWrite(RELAY_FAN_PIN, HIGH);
    Serial.println("FAN ON");
  }
  
}



//float coolingSystem() {
//   // wait a few seconds between measurements.
//  delay(2000);
//
//  temperature = dht.readTemperature();  // read temperature in Celsius
//  
//  if (isnan(temperature)) {
//    Serial.println("Failed to read from DHT sensor!");
//  } else {
//    if(temperature > TEMP_THRESHOLD_UPPER){
//      Serial.println("The fan is turned on");
//      digitalWrite(RELAY_FAN_PIN, HIGH); // turn on
//    } else if(temperature < TEMP_THRESHOLD_LOWER){
//      Serial.println("The fan is turned off");
//      digitalWrite(RELAY_FAN_PIN, LOW); // turn on
//    }
//  }
//  return temperature
//   
//}
//
//void irrigationSystem() {
//   output_value= digitalRead(sensor_pin);
//   output_value = map(output_value,550,10,0,100);
//   Serial.print("Mositure : ");
//   Serial.print(output_value);
//   Serial.println("%");
//   if(output_value<20){
//    digitalWrite(relayPin, LOW);
//   }
//   else
//   {
//    digitalWrite(relayPin, HIGH);       
//   }
//   delay(1000);
//  
//  
//}
//
//
//void irrigationSystems() {
//    digitalWrite(pump, HIGH);
//    delay(100);
//  
//    digitalWrite(pump,LOW);
//    delay(300000);
//  
//}
//
//void gasesReading(){
//  
//}
//
//void soilReading() {
//
//  
//}
//
//void LCDDisplay() {
//  
//}
