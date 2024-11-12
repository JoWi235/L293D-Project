#include <Arduino.h>

class Motor {
    private:
        int pin_anschluss1;
        int pin_anschluss2;
    public:
        Motor(int pin1, int pin2);
        int getPin1();
        int getPin2();
        void forward();
        void backward();
        void stop();
};
