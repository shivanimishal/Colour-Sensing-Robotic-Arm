void positionServo(int colourBox){
  Serial.println("in pick up");
   for (int i=colourBox;i>=0;i--)   //moves downwards(2 gears are present)
  {
    servo_arm.write(i);
    delay(15);              //duty cycle of servo motor is 20ms
  }
  delay(3000);
}

void moveBlock(int colourBox){
  Serial.println("in position");
  for (int j=0;j<=colourBox;j++)   //moves upwards
  {
    servo_arm.write(j);
    delay(15);
  }
   delay(3000);
}

void closeGripper() {
 for (int i=75;i<=140;i++)   //moves downwards(2 gears are present)
  {
    servo_gripper.write(i);
    delay(15);              //duty cycle of servo motor is 20ms
  }
// delay(3000);
}

void openGripper() {
 for (int i=140;i>=75;i--)   //moves downwards(2 gears are present)
  {
    servo_gripper.write(i);
    delay(15);              //duty cycle of servo motor is 20ms
  }
// delay(3000);
}



void getFrequency() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  redColor = map(redFrequency,137,380, 255,0);
  
  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  greenColor = map(greenFrequency, 150, 358, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);[
  delay(100);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  blueColor = map(blueFrequency, 43,129, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);
  }
