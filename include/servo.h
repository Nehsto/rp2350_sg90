#ifndef SERVO_H
#define SERVO_H

#define PICO_PWM_PIN 13
#define PICO_LED_PIN 11

#define DIV_VAL 150.0f
#define WRAP_VAL 20000
#define WRAP_IRQ false

#define MIN_FADE 500
#define MAX_FADE 2500
#define FADE_STEP 50

#define MIN_ANGLE -90
#define MAX_ANGLE 90
#define M (MAX_FADE - MIN_FADE)/(MAX_ANGLE - MIN_ANGLE)
#define B (MAX_FADE - M * MAX_ANGLE)

#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#if WRAP_IRQ
void on_pwm_wrap();
#endif

void servo_set_angle(double angle);
void servo_init();

#endif //SERVO_H