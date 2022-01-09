// Using digital pins
int trigPin = 2;    
int echoPin = 3;    
long duration, cm, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  
  //Define pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
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
  
  delay(200);
}
