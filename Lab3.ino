#include <EEPROM.h>
int bluePin = 4;
int greenPin = 5;
int redPin = 6;
int pbtnPin = 8;
int tilt = 9;
int counter = 0;
int speed = 1000;
String studentID = "00734328";
String input;
int dashPin = redPin;
int dotPin = greenPin;
int x = 0;

//float T = speed;
void Dash(){
  digitalWrite(dashPin, HIGH);
  delay(speed);
  digitalWrite(dashPin, LOW);
  delay(speed);
}

void Dot(){
  digitalWrite(dotPin,HIGH);
  delay(speed);
  digitalWrite(dotPin, LOW);
  delay(speed);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pbtnPin,INPUT_PULLUP);
  pinMode(tilt,INPUT_PULLUP);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(redPin,OUTPUT);

  //studentID = EEPROM.read(x);
  
  dashPin = EEPROM.read(9);
  dotPin = EEPROM.read(10);
  //time = EEPROM.read(11);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:  
  int status = digitalRead(pbtnPin);
  int reset = digitalRead(tilt);
  
  if(!status){
    Serial.println(dashPin);
    Serial.println(dotPin);
    Serial.println(speed);
    Serial.println(studentID);    
  }

  
  if(reset == LOW) counter = 0;
   
  if(Serial.available()) {
    input = Serial.readString();
    switch(input[0]) {
      case 'D':
        if(input[1] == 'r') dashPin = redPin;
        else if (input[1] == 'b') dashPin = bluePin;
        else if (input[1] == 'g') dashPin = greenPin;
        EEPROM.write(9, dashPin);
        break;
      case 'd':
        if(input[1] == 'r') dotPin = redPin;
        else if (input[1] == 'b') dotPin = bluePin;
        else if (input[1] == 'g') dotPin = greenPin;
        EEPROM.write(10, dotPin);                
        break;
      case 's':
        if(input[1] == '1') speed = 1000;
        else if (input[1] == '2') speed = 650;
        else if (input[1] == '3') speed = 400;
        //EEPROM.write(11, speed); I don't know how to get it to store the time delay properly
        break;
      case 'i':
        studentID = input.substring(1);
        //EEPROM.write(0, studentID); Doesn't work. I dont know how to make it store string.
        
        break;      
    }
  }
  
  if(status == LOW){
    switch(studentID[counter]){
      case '0':
        Dash();
        Dash();
        Dash();
        Dash();
        Dash();
        break;
        
      case '1':
        Dot();
        Dash();
        Dash();
        Dash();
        Dash();
        break;
        
      case '2':
        Dot();
        Dot();
        Dash();
        Dash();
        Dash();
        break;
        
      case '3':
        Dot();
        Dot();
        Dot();
        Dash();
        Dash();
        break;
        
      case '4':
        Dot();
        Dot();
        Dot();
        Dot();
        Dash();
        break;
        
      case '5':
          Dot();
          Dot();
          Dot();
          Dot();
          Dot();
          break;
        
      case '6':
        Dash();
        Dot();
        Dot();
        Dot();
        Dot();
        break;
        
      case '7':
        Dash();
        Dash();
        Dot();
        Dot();
        Dot();
        break;

      case '8':
        Dash();
        Dash();
        Dash();
        Dot();
        Dot();
        break;
      }
    counter++;
    if(counter == 8) counter = 0;
    }
}