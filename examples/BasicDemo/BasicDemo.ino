
#include "L298N.h" // Include the L298N library header

// Create instances of the L298N class for two motors
// L298N(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin);
int ENA = 3, IN1 = 4, IN2 = 5; // ENA must be PWM capable pin
int ENB = 6, IN3 = 7, IN4 = 8; // ENB must be PWM capable pin

L298N motor1(ENA, IN1, IN2);
L298N motor2(ENB, IN3, IN4);

void setup()
{
    // Initialize Serial Monitor for debugging output
    Serial.begin(115200);

    // Initialize motor drivers
    motor1.begin();
    Serial.println("motor1 initialized");
    motor2.begin();
    Serial.println("motor2 initialized");
}

void loop()
{
    // --- Forward Phase: Ramp Up ---
    // Gradually increase speed from 0 to half speed (PWM 128)
    for (int speed = 0; speed <= 128; speed += 4)
    {
        motor1.write(speed);
        motor2.write(speed);
        Serial.print("Ramping forward up: ");
        Serial.println(speed);
        delay(50); // adjust delay for smoother/slower ramping
    }

    // Hold at half speed for a short duration
    delay(3000);

    // --- Forward Phase: Ramp Down ---
    // Gradually decrease speed from half speed (PWM 128) to 0
    for (int speed = 128; speed >= 0; speed -= 4)
    {
        motor1.write(speed);
        motor2.write(speed);
        Serial.print("Ramping forward down: ");
        Serial.println(speed);
        delay(50);
    }

    // Brake the motors after the forward phase
    motor1.brake();
    motor2.brake();
    Serial.println("Motors braking (forward phase)");
    delay(3000);

    // --- Reverse Phase: Ramp Up ---
    // Gradually increase reverse speed from 0 to full reverse (-255)
    for (int speed = 0; speed >= -255; speed -= 5)
    {
        motor1.write(speed);
        motor2.write(speed);
        Serial.print("Ramping reverse up: ");
        Serial.println(speed);
        delay(30);
    }

    // Hold at full reverse for a short duration
    delay(3000);

    // --- Reverse Phase: Ramp Down ---
    // Gradually decrease reverse speed from full reverse (-255) to 0
    for (int speed = -255; speed <= 0; speed += 5)
    {
        motor1.write(speed);
        motor2.write(speed);
        Serial.print("Ramping reverse down: ");
        Serial.println(speed);
        delay(30);
    }

    // Brake the motors after the reverse phase
    motor1.brake();
    motor2.brake();
    Serial.println("Motors braking (reverse phase)");
    delay(3000);

    // --- Forward Phase: Ramp Up ---
    // Gradually increase speed from 0 to full speed (255)
    for (int speed = 0; speed <= 255; speed += 5)
    {
        motor1.write(speed);
        motor2.write(speed);
        Serial.print("Ramping forward up to soft stop: ");
        Serial.println(speed);
        delay(30); // adjust delay for smoother/slower ramping
    }
    // Hold at full speed for a short duration
    delay(3000);

    // --- Soft Stop Phase ---
    // Allow the motors to decelerate gradually to a stop on their own
    motor1.write(0);
    motor2.write(0);
    Serial.println("Soft stop initiated (gradual deceleration; write(0))");
    delay(3000); // adjust delay for desired deceleration time

    // --- Forward Phase: Ramp Up ---
    // Gradually increase speed from 0 to full speed (255)
    for (int speed = 0; speed <= 255; speed += 5)
    {
        motor1.write(speed);
        motor2.write(speed);
        Serial.print("Ramping forward up to hard stop: ");
        Serial.println(speed);
        delay(30); // adjust delay for smoother/slower ramping
    }
    // Hold at full speed for a short duration
    delay(3000);

    // --- Hard Stop Phase ---
    // Immediately stop the motors
    motor1.brake();
    motor2.brake();
    Serial.println("Hard stop initiated (immediate stop; brake())");
    delay(3000); // adjust delay for desired stop time
}
