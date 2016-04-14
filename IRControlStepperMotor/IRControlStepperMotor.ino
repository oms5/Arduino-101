#include <AccelStepper.h>
#include <IRremote.h>
#define HALFSTEP 8
#define FULLSTEP 4

// You need the AccelStepper library for this sketch to run.  You can get it from here: http://aka.ms/AccelStepper

// The AccelStepper constructor expects the "pins" specified to be the ends of each coil respectively.
// First the ends of the Blue/Yellow coil, then the ends of the Pink/Orange coil (Blue,Yellow,Pink,Orange)

// However, 28BYJ connector, ULN2003 board, and our current configuration is that pins are arranged in the proper FIRING order, 
// Blue, Pink, Yellow, Orange.

// No biggie, that just means that we need to pay attention to what pins on our Arduino,
// map to which ends of the coils, and pass the pin numbers in in the proper sequence.  

// To help with that, I will specify my pin variables based on their color.

#define blue 2
#define pink 3
#define yellow 4
#define orange 5

//Keeps track of the current direction
//Relative to the face of the motor. 
//Clockwise (true) or Counterclockwise(false)
//We'll default to clockwise
bool clockwise = true;
bool stepperOn = false;

// How many steps to go before reversing
// int targetPosition = 2048;  //2049 steps per rotation when wave or full stepping
int targetPosition = 4096;  //4096 steps per rotation when half stepping

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
// Notice, I'm passing them as Blue, Yellow, Pink, Orange (coil ends order) not
// Blue, Pink, Yellow, Orange (firing order). 
AccelStepper stepper1(HALFSTEP, blue, yellow, pink, orange);

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
    //Tell it how fast to accelerate
    stepper1.setAcceleration(100.0); 
    //Set a maximum speed it should exceed 
    stepper1.setMaxSpeed(4000.0);   

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("started");
  pinMode(13, OUTPUT);

}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.print(results.value, HEX);
    Serial.print("-");
    translateIR();
    irrecv.resume(); // Receive the next value
  }
  
  if (stepperOn == true) {
    //Set the  speed (read the AccelStepper docs on what "speed" means
            
    
    //Tell it to move to the target position
    if (clockwise == true) {
      stepper1.setSpeed(100.0); 
      targetPosition = 0;
    } else {
      stepper1.setSpeed(-100.0); 
      targetPosition = 4096;
    }
    stepper1.moveTo(targetPosition);  
    //If the stepper still needs to move (distanceToGo() != 0)
    //continue to advance (step) the motor
    stepper1.run();
  } else {
    
  }
  

}

void translateIR() // takes action based on IR code received

// describing Car MP3 IR codes 

{

  switch(results.value)

  {

  case 0xFFA25D:  
    Serial.println(" CH-            "); 
    break;

  case 0xFF629D:  
    Serial.println(" CH             "); 
    break;

  case 0xFFE21D:  
    Serial.println(" CH+            "); 
    
    break;

  case 0xFF22DD:  
    Serial.println(" PREV           "); 
    break;

  case 0xFF02FD:  
    Serial.println(" NEXT           "); 
    break;

  case 0xFFC23D:  
    Serial.println(" PLAY/PAUSE     "); 
    break;

  case 0xFFE01F:  
    Serial.println(" VOL-           "); 
    stepperOn = !stepperOn;
    clockwise = false;
    break;

  case 0xFFA857:  
    Serial.println(" VOL+           "); 
    stepperOn = !stepperOn;
    clockwise = true;
    break;

  case 0xFF906F:  
    Serial.println(" EQ             "); 
    break;

  case 0xFF6897:  
    Serial.println(" 0              "); 
    break;

  case 0xFF9867:  
    Serial.println(" 100+           "); 
    break;

  case 0xFFB04F:  
    Serial.println(" 200+           "); 
    break;

  case 0xFF30CF:  
    Serial.println(" 1              "); 
    break;

  case 0xFF18E7:  
    Serial.println(" 2              "); 
    break;

  case 0xFF7A85:  
    Serial.println(" 3              "); 
    break;

  case 0xFF10EF:  
    Serial.println(" 4              "); 
    break;

  case 0xFF38C7:  
    Serial.println(" 5              "); 
    break;

  case 0xFF5AA5:  
    Serial.println(" 6              "); 
    break;

  case 0xFF42BD:  
    Serial.println(" 7              "); 
    break;

  case 0xFF4AB5:  
    Serial.println(" 8              "); 
    break;

  case 0xFF52AD:  
    Serial.println(" 9              "); 
    break;

  default: 
    Serial.println(" other button   ");

  }

  delay(500);


} //END translateIR
