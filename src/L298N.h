
#ifndef L298N_H
#define L298N_H

#include <Arduino.h>

/**
 * @brief L298N class to control the L298 motor driver.
 *
 * This class supports basic motor control functions:
 * - write(): Adjust motor speed and direction using sign/magnitude PWM.
 * - brake(): Activates an active braking mode.
 *
 * This library is designed to be compatible with DCMotorServo.
 */
class L298N
{
public:
    /**
     * @brief Construct a new L298N object.
     *
     * @param enablePin PWM enable pin for the motor driver.
     * @param in1Pin    Digital pin connected to IN1.
     * @param in2Pin    Digital pin connected to IN2.
     */
    L298N(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin);

    /**
     * @brief Initialize the pins.
     */
    void begin();

    /**
     * @brief Set the motor speed.
     *
     * Use a signed value (-255 to 255) to indicate direction and speed.
     * Positive values drive the motor in one direction,
     * negative values drive it in the opposite.
     * This method also releases any active braking.
     *
     * @param speed Motor speed.
     */
    void write(int16_t speed);

    /**
     * @brief Activate the brake.
     *
     * Engages active braking by shorting the motor outputs.
     */
    void brake();

private:
    uint8_t _enablePin;
    uint8_t _in1Pin;
    uint8_t _in2Pin;
};

#endif
