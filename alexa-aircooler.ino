#include "arduino_secrets.h"
#include "thingProperties.h"

const int power = 33;                // Power On button
const int water = 32;                // Water vaper button
const int fan = 25;                  // Fan Speed button

const int fanSpeedLed1 = 17;         // This inputs represent the fan speed leds in the Air Cooler
const int fanSpeedLed2 = 19;         //
const int fanSpeedLed3 = 18;         //

const int waterSpeedLed1 = 22;       // This inputs represent the water vaper leds in the Air Cooler
const int waterSpeedLed2 = 23;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  pinMode(power,OUTPUT); 
  pinMode(water,OUTPUT); 
  pinMode(fan,OUTPUT);
  
  digitalWrite(power,HIGH);
  digitalWrite(water,HIGH);
  digitalWrite(fan,HIGH);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();  

}



/*
  Since PowerHumidifier is READ_WRITE variable, onPowerHumidifierChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPowerHumidifierChange()  {
  // Add your code here to act upon PowerHumidifier change

  //Power on the air cooler
  digitalWrite(power,LOW);
  delay(200);
  digitalWrite(power,HIGH);
  
  delay(500);

  // Turn on the water in speed 1
  digitalWrite(water,LOW);
  delay(200);
  digitalWrite(water,HIGH);
    

  if (!powerHumidifier) {
    digitalWrite(power,LOW);
    delay(200);
    digitalWrite(power,HIGH);
  }
}
/*
  Since WaterLevel is READ_WRITE variable, onWaterLevelChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onWaterLevelChange()  {
  // Add your code here to act upon WaterLevel change
  int waterSpeed = findWaterSpeed();
  int requiredSpeed = map(waterLevel.getBrightness(), 1, 100, 1, 2);
  int loopWater = 0;

  if (!waterLevel.getSwitch()){
    requiredSpeed = 0;
  } 


  if ((requiredSpeed == 1 && waterSpeed == 0) || (requiredSpeed == 2 && waterSpeed == 1) || ((requiredSpeed == 0 && waterSpeed == 2))) {
    loopWater = 1;
  } else if ((requiredSpeed == 2 && waterSpeed == 0) || (requiredSpeed == 0 && waterSpeed == 1) || ((requiredSpeed == 1 && waterSpeed == 2))) {
    loopWater = 2;
  }

  Serial.println("loopWater: " + String(loopWater) + " || requiredSpeed: " + String(requiredSpeed) + " || waterSpeed: " + String(waterSpeed)); 

  for (int i = 0; i < loopWater; i++){
    digitalWrite(water,LOW);
    delay(200);
    digitalWrite(water,HIGH);
    delay(500);
    Serial.println("loop"); 
  }
  
}

/*
  Since FanLevel is READ_WRITE variable, onFanLevelChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFanLevelChange()  {
  // Add your code here to act upon FanLevel change
  int fanSpeed = findFanSpeed();
  int requiredSpeed = map(fanLevel.getBrightness(), 1, 100, 1, 3);
  int loopFan = 0;

  if (!fanLevel.getSwitch()){
    requiredSpeed = 0;
  } 


  if ((requiredSpeed == 1 && fanSpeed == 0) || (requiredSpeed == 2 && fanSpeed == 1) || (requiredSpeed == 3 && fanSpeed == 2) || (requiredSpeed == 0 && fanSpeed == 3)) {
    loopFan = 1;
  } else if ((requiredSpeed == 2 && fanSpeed == 0) || (requiredSpeed == 3 && fanSpeed == 1) || (requiredSpeed == 0 && fanSpeed == 2) || (requiredSpeed == 1 && fanSpeed == 3)) {
    loopFan = 2;
  } else if ((requiredSpeed == 3 && fanSpeed == 0) || (requiredSpeed == 0 && fanSpeed == 1) || (requiredSpeed == 1 && fanSpeed == 2) || (requiredSpeed == 2 && fanSpeed == 3)) {
    loopFan = 3;
  }

  Serial.println("loopFan: " + String(loopFan) + " || requiredSpeed: " + String(requiredSpeed) + " || fanSpeed: " + String(fanSpeed)); 

  for (int i = 0; i < loopFan; i++){
    digitalWrite(fan,LOW);
    delay(200);
    digitalWrite(fan,HIGH);
    delay(500);
    Serial.println("loop"); 
  }
}

int findWaterSpeed() {
  int waterSpeed = 0;

  for (int i = 0; i < 50000; i++) {

    if (digitalRead(waterSpeedLed1) == 0) {
      waterSpeed = 1;
      break;
    } else if (digitalRead(waterSpeedLed2) == 0) {
      waterSpeed = 2;
      break;
    }
    
  }

  Serial.println("waterSpeed " + String(waterSpeed)); 

  return waterSpeed;  
}


int findFanSpeed() {
    int fanSpeed = 0;

  for (int i = 0; i < 50000; i++) {

    if (digitalRead(fanSpeedLed1) == 0){
      fanSpeed = 1;
      break;
    } else if (digitalRead(fanSpeedLed2) == 0) {
      fanSpeed = 2;
      break;
    } else if (digitalRead(fanSpeedLed3) == 0) {
      fanSpeed = 3;
      break;
    }
    
  }

  Serial.println("fanSpeed " + String(fanSpeed)); 

  return fanSpeed;  
}
