#include "servo.h"

#if WRAP_IRQ
void on_pwm_wrap() {
  static int fade = MIN_FADE;
  static bool going_up = true;
  // Clear the interrupt flag that brought us here
  pwm_clear_irq(pwm_gpio_to_slice_num(PICO_PWM_PIN));

  if (going_up) {
    fade += FADE_STEP;
    if (fade > MAX_FADE) {
      fade = MAX_FADE;
      going_up = false;
    }
  } else {
    fade -= FADE_STEP;
    if (fade < MIN_FADE) {
      fade = MIN_FADE;
      going_up = true;
    }
  }

  // Note this range matches with the wrap value
  pwm_set_gpio_level(PICO_PWM_PIN, fade);
}
#endif

void servo_set_angle(double angle){
  if(angle < MIN_ANGLE || angle > MAX_ANGLE)
    return;

  uint16_t val = M * angle + B;
  pwm_set_gpio_level(PICO_PWM_PIN, val);
}

void servo_init() {
  // set_sys_clock_khz(SYS_CLK_KHZ, true);
  uint32_t sys_clk_hz = clock_get_hz(clk_sys);

  // Tell the LED pin that the PWM is in charge of its value.
  gpio_set_function(PICO_PWM_PIN, GPIO_FUNC_PWM);
  // Figure out which slice we just connected to the LED pin
  uint slice_num = pwm_gpio_to_slice_num(PICO_PWM_PIN);

  #if WRAP_IRQ
  // Mask our slice's IRQ output into the PWM block's single interrupt line,
  // and register our interrupt handler
  pwm_clear_irq(slice_num);
  pwm_set_irq_enabled(slice_num, true);
  irq_set_exclusive_handler(PWM_DEFAULT_IRQ_NUM(), on_pwm_wrap);
  irq_set_enabled(PWM_DEFAULT_IRQ_NUM(), true);
  #endif
  
  // Get some sensible defaults for the slice configuration. 
  pwm_config config = pwm_get_default_config();
  // Set divider, reduces counter clock to sysclock/this value
  pwm_config_set_clkdiv(&config, DIV_VAL);

  pwm_config_set_wrap(&config, WRAP_VAL-1);
  // Load the configuration into our PWM slice, and set it running.
  pwm_init(slice_num, &config, true);
}
