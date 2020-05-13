#include <Servo.h>           //include servo library
Servo servo_gripper; //initialize object
Servo servo_arm; 

boolean dropBlock = false;
boolean pickBlock = false;
boolean hasMoved = false;
boolean hasPositioned = false;
boolean hasDropped = false;
//int dropBox=0;
int blockColour;
//int attempt=0;


// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  Serial.begin(9600);
  servo_gripper.attach(9); 
  servo_arm.attach(10); //initialize servo pin
  
  servo_gripper.write(0);//initial position of the gripper
  servo_arm.write(0); //initial position of the arm

    // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void loop() {
     
      // adjustment to get appropriate reading
      //for (int attempt=0; attempt<=3; attempt++){
        getFrequency();
        blockColour = getColour();
        Serial.println("for");
        //Serial.print(attempt);
        delay(100);
      //}
      Serial.println("blockColour");
      Serial.println(blockColour);
      delay(3000);
      
      // pick up only the RGB blocks
      if (blockColour==1||blockColour==2||blockColour==3){ 
          int dropBox;
          dropBlock = false;
          pickBlock = false;
          hasMoved = false;
          hasPositioned = false;
          hasDropped = false;
          Serial.println("Val in blockColour:  ");
          Serial.println(blockColour);
          delay(2000); //Event required
          if (pickBlock == false) {
            Serial.println("in closegripper");
            closeGripper();
            pickBlock = true;
          }
           if(hasMoved == false){
            Serial.println("in 2 IF");
            dropBox = getAngle();
            Serial.println("Val in dropBox:  ");
            Serial.println(dropBox);
            delay(1000);
            moveBlock(dropBox);
            hasMoved = true;
          } 
      
          if (dropBlock == false){
            Serial.println("in open gripper");
            openGripper();
            Serial.println("Block has been dropped");
            dropBlock = true;
           }
          if (hasPositioned == false){
            Serial.println("in 1 IF");
            Serial.println("Val in dropBox in positionServo:  ");
            Serial.println(dropBox);
            positionServo(dropBox);
            hasPositioned = true;
           }
          delay(5000); 
        }
       else{
        Serial.println("Not Applicable!");
        delay(5000); 
       }
}


int getAngle(){
  Serial.println("In get angle");
  int angle = 0;
  Serial.println("Val in blockColour:  ");
  Serial.println(blockColour);
  switch(blockColour){
    case 1:
      angle=60;
      Serial.println("case 1");
      break;
    case 2:
      angle=120;
      Serial.println("case 2");
      break;
    case 3:
      angle=180;
      Serial.println("case 3");
      break;
  }
  return angle;
}


  int getColour() {
    Serial.println("In get colour");
    int colour;
  // Checks current detected color and prints  a message in the serial monitor 
  if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - RED detected!");
      colour=1;
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - GREEN detected!");
    colour=3;
  }
  if(blueColor > redColor && blueColor >= greenColor){
    Serial.println(" - BLUE detected!");
    colour=2;
  }Serial.println(colour);
  
  return colour;
  }
