// Include library
#include <MPU9250_asukiaaa.h>

// Create sensor object
MPU9250_asukiaaa mySensor;

float  aY,aSqrt;
void setup() {
  
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");

  // Internal function from lib
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

}

void loop() {
  uint8_t sensorId;

  // Fuction returns 0 when sensor detected
  if (mySensor.readId(&sensorId) == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId");
  }

  // Add offset
  float accelYOffset = 0.07;
  
  if (mySensor.accelUpdate() == 0) 
  {
    aY = mySensor.accelY()+accelYOffset;
    Serial.println("accelY: " + String(aY) +"g");   
  } 
  else 
  {
    Serial.println("Cannod read Y axis accel values");
  }

  // How long program has been running
  Serial.println("at " + String(millis()) + "ms");
  Serial.println(""); // Add an empty line

  // Repeat every 500ms
  delay(500);
}
