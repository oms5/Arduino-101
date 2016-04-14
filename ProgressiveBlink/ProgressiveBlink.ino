/*
  Progressive Blink
 */
int initialDelay = 500; // in miliseconds
int currentDelay = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  // initialize the serial monitor
   Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // reset the delay when it decreases to zero or less
  if (currentDelay <= 0) {
    currentDelay = initialDelay;
  }
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(currentDelay);      // wait for current value of currentDelay
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(currentDelay);      // wait for current value of currentDelay
  
  currentDelay = currentDelay - 10;
  Serial.print("currentDelay is: ");
  Serial.print(currentDelay);
  Serial.println("ms");
}
