int echoPin = 10;  // attach pin D2 Arduino to pin Echo of HC-SR04
int trigPin = 6;   //attach pin D3 Arduino to pin Trig of HC-SR04
long duration;     // variable for the duration of sound wave travel
int distance;      // variable for the distance measurement

int previousDistance = 0;
unsigned long previousTime = 0;
int closeDetections = 0;


void setup() {
  pinMode(trigPin, OUTPUT);    // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);     // Sets the echoPin as an INPUT
  digitalWrite(trigPin, LOW);  //MAKE SURE PIN START LOW
  Serial.begin(9600);          // Serial Communication is starting with 9600 of baudrate speed
}
void loop() {

  unsigned long currentTime = millis();
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);  //length of pulse in microseconds (1uS = 0.000001s)
  distance = duration * 0.034 / 2;    // DISTANCE = Speed of sound wave (343m/s) divided by 2 (out and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 

  int currentDistance = distance;

  if (currentDistance <= 100) {
    // happiness + 10 because detect that owner is near
  }

  Serial.println("time");
  Serial.println(currentTime);
  Serial.println(previousTime);
  if (currentTime - previousTime >= 2000) {
    // Reset previous values if more than 3 seconds have passed
    previousDistance = currentDistance;
    previousTime = currentTime;
    closeDetections = 0;
    // happiness -0.01 no interaction 
  } else {
    // Check if current distance is close to previous distance
    previousTime = currentTime;
    int distanceDifference = abs(currentDistance - previousDistance);
    Serial.println(distanceDifference);
    if (distanceDifference > 200) {  // Adjust this threshold as needed
      closeDetections++;
      previousDistance = currentDistance;
      Serial.println("closeDetections: ");
      Serial.println(closeDetections);
      if (closeDetections == 4) {
        // Object has been close two times in the past 3 seconds, take action here
        Serial.println("Wave detected!");
        // happiness +10 because interact with owner
        delay(5000);
        closeDetections = 0;
      }
    }
  }

  previousDistance = currentDistance;
}