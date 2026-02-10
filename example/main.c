#include "servo.h"

// Sweep an SG90 servo across [-90,90] degree range

int main(){
  uint32_t sys_clk_hz = clock_get_hz(clk_sys);

  stdio_init_all();
  sleep_ms(1000);
  printf("Speed of system clock: %d\n", sys_clk_hz);
  printf("Frequency of pwm signal: %.0f\n", (float)sys_clk_hz/(WRAP_VAL*DIV_VAL));//sys_clk/());

  servo_init();

  // This process can be done the same way as an IRQ or task, see servo.c
  double angle = 0.0;
  double step = 0.1;
  while(1){
    if(angle > 90.0){
      angle = 90.0;
      step = -0.1;
    }else if(angle < -90.0){
      angle = -90.0;
      step = 0.1;
    }
    angle = angle + step;
    servo_set_angle(angle);
    sleep_ms(5);
  }

  return 0;
}