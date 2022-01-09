// Include the library
#include <ESP32Encoder.h>

// The code works but only in one direction. It also isnt very accurate in the counting. This happens for me atleast

// Create an encoder called encoder
ESP32Encoder encoder;

void setup() {
  // When opening serial monitor, make sure the number below is selected
  Serial.begin(115200);
  ESP32Encoder::useInternalWeakPullResistors=UP;
  // Connect middle pin of encoder to 32, bottom pin to 33 and top pin to ground
  encoder.attachHalfQuad(32,33);
  
  encoder.setCount(0);

  Serial.println("Encoder Start = " + String((int32_t)encoder.getCount()));
}

void loop() {
  // Not sure what the digital writes do
  digitalWrite(14,LOW);
  digitalWrite(27,LOW);
  Serial.println("Encoder count = " + String((int32_t)encoder.getCount()));
  delay(100);
}
