#include "L298N.h"

L298N::L298N(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin)
    : _enablePin(enablePin), _in1Pin(in1Pin), _in2Pin(in2Pin)
{
}

void L298N::begin()
{
    pinMode(_enablePin, OUTPUT);
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
    // Ensure the motor is stopped initially by engaging brake.
    brake();
}

void L298N::write(int16_t speed)
{
    // Release any active braking state by setting proper direction signals.
    if (speed >= 0)
    {
        digitalWrite(_in1Pin, HIGH);
        digitalWrite(_in2Pin, LOW);
    }
    else
    {
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, HIGH);
        speed = -speed; // use absolute value for PWM duty cycle
    }
    // Constrain speed to valid PWM range.
    speed = constrain(speed, 0, 255);
    analogWrite(_enablePin, speed);
}

void L298N::brake()
{
    // Engage active braking by shorting the motor outputs.
    // Here, both IN1 and IN2 are set LOW and full PWM is applied.
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, LOW);
    analogWrite(_enablePin, 255);
}
