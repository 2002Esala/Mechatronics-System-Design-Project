const int trigPin1 = 51;  // define the pin number for the first ultrasound sensor's trigger
const int echoPin1 = 49;  // define the pin number for the first ultrasound sensor's echo
const int trigPin2 = 45;  // define the pin number for the second ultrasound sensor's trigger
const int echoPin2 = 47;  // define the pin number for the second ultrasound sensor's echo
// defines variables
long duration;
int distance;

int motorIn1 = 4;
int motorIn2 = 3;
int motorEnA = 2;

int motorIn3 = 7;
int motorIn4 = 6;
int motorEnB = 5;
int i=1;
int limit = 5000;
int count = 1;

int fan = 0;

#include <Servo.h>
Servo ESC1; // create servo object to control the ESC
Servo ESC2;

int start_time = millis();

const int SWITCH_PIN = 14;

void setup() {

  ESC1.attach(9,1000,2000);
  ESC2.attach(8,1000,2000);
  ESC1.write(0); // Send the signal to the ESC
  ESC2.write(0);
  
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);  // set the trigger pin of the first ultrasound sensor to output
  pinMode(echoPin1, INPUT);   // set the echo pin of the first ultrasound sensor to input
  pinMode(trigPin2, OUTPUT);  // set the trigger pin of the second ultrasound sensor to output
  pinMode(echoPin2, INPUT);   // set the echo pin of the second ultrasound sensor to input
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorEnA, OUTPUT);

  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  pinMode(motorEnB, OUTPUT);
  
  pinMode(SWITCH_PIN, INPUT_PULLUP);  // set the switch pin as input with internal pull-up resistor
  Serial.begin(9600);  // initialize the serial communication for debugging purposes
  int switchState = digitalRead(SWITCH_PIN);
  while (switchState == 1){
    switchState = digitalRead(SWITCH_PIN);
    Serial.println(switchState);
    Serial.println("nothing");
    }
  Serial.println("Start");
  start_time = millis();
  
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorEnA, 90);
  analogWrite(motorEnB, 90);
  delay(2000);


}

void loop(){


  
  int time = millis();
  int time_taken = time-start_time;
  
  if (time_taken<=limit){
    digitalWrite(trigPin1, LOW);  // set trigger pin to low
    delayMicroseconds(2);         // wait for 2 microseconds
    digitalWrite(trigPin1, HIGH); // set trigger pin to high
    delayMicroseconds(10);        // wait for 10 microseconds
    digitalWrite(trigPin1, LOW);  // set trigger pin to low
    long duration1 = pulseIn(echoPin1, HIGH);  // read the duration of the echo signal
    float distance1 = duration1 * 0.034 / 2;

    digitalWrite(trigPin2, LOW);  // set trigger pin to low
    delayMicroseconds(2);         // wait for 2 microseconds
    digitalWrite(trigPin2, HIGH); // set trigger pin to high
    delayMicroseconds(10);        // wait for 10 microseconds
    digitalWrite(trigPin2, LOW);  // set trigger pin to low
    long duration2 = pulseIn(echoPin2, HIGH);  // read the duration of the echo signal
    float distance2 = duration2 * 0.034 / 2;   // calculate distance based on duration
    Serial.print("Distance1: ");
    Serial.print(distance1);
    Serial.print("   Distance2: ");
    Serial.println(distance2);
    if (distance1 < 40 || distance2 < 40){
        fan=1;
        digitalWrite(13,HIGH);
      }
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    digitalWrite(motorIn3, HIGH);
    digitalWrite(motorIn4, LOW);
    analogWrite(motorEnA, 90);
    analogWrite(motorEnB, 90);
    ESC1.write(0);
    ESC2.write(0);
    count=1;
    }
  else{
    if (i==1){
      if(count==1){
        for(int i=0;i<=180;i++){
          ESC1.write(i); // Send the signal to the ESC
          ESC2.write(i);
          Serial.println(i);
          delay(2);
          }
        }
       count=0;
       ESC1.write(180);
       ESC2.write(180);
      delay(5000);
      ESC1.write(0);
      ESC2.write(0);
      delay(2000);
      fan=0;
      digitalWrite(13,LOW);
      limit = limit+10000;
      i=2;
      }
    else if(fan ==1){
      if(count==1){
        for(int i=0;i<=180;i++){
          ESC1.write(i); // Send the signal to the ESC
          ESC2.write(i);
          Serial.println(i);
          delay(2);
          }
        }
       count=0;
       ESC1.write(180);
       ESC2.write(180);
      delay(5000);
      ESC1.write(0);
      ESC2.write(0);
      delay(2000);
      fan=0;
      digitalWrite(13,LOW);
      limit = limit+10000;
      }
    
    
   else if(fan == 0){
      ESC1.write(0);
      ESC2.write(0);
      delay(2000);
      analogWrite(motorEnA, 0);
      analogWrite(motorEnB, 0);
      exit(0);
    }
  
  
}
}
