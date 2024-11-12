#include <Arduino.h>
#include "l293d.h"

Motor::Motor(int pin1, int pin2) {
    pin_anschluss1 = pin1;
    pin_anschluss2 = pin2; 
}
int Motor::getPin1(){
    return pin_anschluss1;
}
int Motor::getPin2(){
    return pin_anschluss2;
}
void Motor::forward(){
    digitalWrite(pin_anschluss1, HIGH);     
    digitalWrite(pin_anschluss2, LOW); 
}
void Motor::backward(){
    digitalWrite(pin_anschluss1, LOW);     
    digitalWrite(pin_anschluss2, HIGH); 
}
void Motor::stop(){
    digitalWrite(pin_anschluss1, LOW);     
    digitalWrite(pin_anschluss2, LOW);
}


