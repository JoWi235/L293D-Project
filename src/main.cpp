#include <Arduino.h>
#include <ESP32Servo.h>
#include "l293d.h"

int servoPin = 13;
Servo servomotor;

//1 Motor FR, 2 Motor HR, 3 Motor FL, 4 Motor HL
Motor motor_FR(14,27);
Motor motor_HR(26,25);
Motor motor_FL(17,5);
Motor motor_HL(18,19);

int trigger = 33;
int echo = 32;
long distance;
long distance_front;
long distance_left;
long distance_right;
long duration;
int infraright_quelle=15;
long infraright_wert;
int infraleft_quelle=0;
long infraleft_wert;
int inframiddle_quelle=4;
long inframiddle_wert;


void setup() {
  // Motoren Output
  pinMode(motor_FR.getPin1(), OUTPUT);
  pinMode(motor_FR.getPin2(), OUTPUT);
  pinMode(motor_HR.getPin1(), OUTPUT);
  pinMode(motor_HR.getPin2(), OUTPUT);
  pinMode(motor_FL.getPin1(), OUTPUT);
  pinMode(motor_FL.getPin2(), OUTPUT);
  pinMode(motor_HL.getPin1(), OUTPUT);
  pinMode(motor_HL.getPin2(), OUTPUT);
  
  // Rest
  Serial.begin(115200);
  servomotor.attach(servoPin);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

}

void move_forward(){
  motor_FR.forward();
  motor_FL.forward();
  motor_HR.forward();
  motor_HL.forward();
}

void move_backward(){
  motor_FR.backward();
  motor_FL.backward();
  motor_HR.backward();
  motor_HL.backward();
}

void move_stop(){
  motor_FR.stop();
  motor_FL.stop();
  motor_HR.stop();
  motor_HL.stop();
}

void move_right(){
  motor_FR.backward();
  motor_FL.forward();
  motor_HR.forward();
  motor_HL.backward();
}

void move_left(){
  motor_FR.forward();
  motor_FL.backward();
  motor_HR.backward();
  motor_HL.forward();
}

void move_right_turn(){
  motor_FR.backward();
  motor_FL.forward();
  motor_HR.backward();
  motor_HL.forward();
}

void move_left_turn(){
  motor_FR.forward();
  motor_FL.backward();
  motor_HR.forward();
  motor_HL.backward();
}

void servomotorright(){
  servomotor.write(0);
}

void servomotorleft(){
  servomotor.write(180);
}

void servomotormiddle(){
  servomotor.write(90);
}

long distance_measure(){
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) * 0.03432;
  return distance;
}

void chose_way(long dis_right, long dis_left){
  if (dis_right >= dis_left) {
    move_right_turn();
    delay(10000);
  } else {
    move_left_turn();
    delay(10000);
  }
}

void infra_scann(){
  infraleft_wert = analogRead(infraleft_quelle);
  infraright_wert = analogRead(infraright_quelle);
  inframiddle_wert = analogRead(inframiddle_quelle);
  if (infraleft_wert <= 200) {
    move_backward();
    delay(2000);
    move_right();
    delay(1000);
  }
  if (infraright_wert <= 200) {
    move_backward();
    delay(2000);
    move_left();
    delay(1000);
  }
  if (inframiddle_wert <= 200) {
    move_forward();
    delay(1000);
  } 
}

void distance_check(){
  servomotormiddle();
  distance_front = distance_measure();
  Serial.println(distance_front);
  if(distance_front <= 20) {
    move_stop();
    servomotorright();
    delay(1000);
    distance_right = distance_measure();
    servomotorleft();
    delay(1000);
    distance_left = distance_measure();
    delay(1000);
    servomotormiddle();
    chose_way(distance_right, distance_left);
  }else {
    move_forward();
  }
  //infra_scann();
}

void loop() {
  distance_check();
}
