# rp2350_sg90

This library is used to set up and control SG90 servos

For running the example (in example directory):
cmake ..
make
picotool load example.uf2

They are controlled with: 
- PWM signal of 50Hz
- Duty cycle of [5-10%] mapping to [-90,90]

Any GPIO pin in the rp2350 can drive PWM signals

SG90 servos are driven with 5V, so use an external
power supply to drive the VIN pins, tie to GND 
with 47uF electrolytic cap