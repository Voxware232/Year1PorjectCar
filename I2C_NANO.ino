#include <Wire.h>    // include Wire library
#include <MPU9250_asukiaaa.h>
#include <WirePacker.h>
// MPU 
// Create sensor object
MPU9250_asukiaaa mySensor;
float  aY,aSqrt;

// Ultrasonic Sensor
int trigPin = 2;    
int echoPin = 3;    
long duration, cm;

// Input message from ESP
String message = "";
bool   message_flag = false;
//ESP32 Address
#define I2C_SLAVE_ADDR 0x04

// PWM Values
int zero = 0;
int High = 255;
int Low = -255;
int leftMotor_speed = 0;
int rightMotor_speed = 0;

void setup() {
  Wire.begin();       // join i2c bus (address optional for master)
  
  Serial.begin(115200); // start serial to visualise data
  
  // received via serial monitor in the IDE
  while(!Serial);
  Serial.println("started");

  // Internal function from lib
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  // Ultrasonic sensor define pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  uint8_t sensorId;
  WirePacker packer;
  
  // Fuction returns 0 when sensor detected
  if (mySensor.readId(&sensorId) == 0) 
  {
    Serial.println("sensorId: " + String(sensorId));
  } 
  else 
  {
    Serial.println("Cannot read sensorId");
  }

  // Add offset
  float accelYOffset = 0.07;

  // Acelerometer Values
  if (mySensor.accelUpdate() == 0) 
  {
    aY = mySensor.accelY()+accelYOffset;
    Serial.println("accelY: " + String(aY) +"g");   
  } 
  else 
  {
    Serial.println("Cannod read Y axis accel values");
  }

  // Gyroscope Values
   if (mySensor.gyroUpdate() == 0) {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    
    Serial.println("gyroX: " + String(gX));
    Serial.println("gyroY: " + String(gY));
    
  } 
  else {
    Serial.println("Cannot read gyro values");
  }

  // How long program has been running
  Serial.println("at " + String(millis()) + "ms");
  Serial.println(""); // Add an empty line

    // Initial trigger to activate sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the time taken for the signal to return into the Echo pin
  pinMode(echoPin, INPUT);

  // Calculate duration takenn
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     

  // Display distance
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  
  if (cm <= 10)
  {
    ParkingProcedure();
    Wire.beginTransmission(I2C_SLAVE_ADDR); 
    while (packer.available()) {            // write every packet byte
      Wire.write(packer.read());
    }
    Wire.endTransmission();
  }
  
  Wire.requestFrom(0x08, 5);    // request 6 bytes from slave device #8
  while (Wire.available()) {    // loop whilst slave sends data
    // i.e. whilst bus is busy
    char c = Wire.read();       // receive data byte by byte
    message += c;               // form complete string
    message_flag = true;         // set true to indicate message received
  }

  if (message_flag == true) {
    Serial.println (message);
    message = "";
    message_flag = false;
  }
  delay(500);
}

void ParkingProcedure()
{
  WirePacker packer;
  packer.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  packer.write((byte)(leftMotor_speed & 0x000000FF)); 
  packer.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));    
  packer.write((byte)(rightMotor_speed & 0x000000FF));          
  delay(500);
  packer.end();
}
