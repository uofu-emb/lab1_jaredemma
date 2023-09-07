#include <lab1.h>
#define MAIN_DELAY 1000
#define THREAD_DELAY 500

//sets up the struct for it to flick a specific light + the counter
//return is initial state of led
int toggle_thread_setup(struct gpio *dev, unsigned int* counter)
{
  *counter = 1;
  dev->CR |= 1 << 2;
  return 0;
}

//puts light on if off and vice versa + increments counter
int toggle_thread_iteration(const unsigned int led_is_on, struct gpio *dev, unsigned int* counter)
{
  *counter = *counter + 1;
  if (led_is_on) {
    dev->DR &= ~(1<<2);
  } else {
    dev->DR |= 1<<2;
  }
  
  delay_ms(THREAD_DELAY);
  return !led_is_on;
}

//sets up the struct for it to flick a specific light
//return is initial state of led
int main_thread_setup(struct gpio *dev)
{
  dev->CR |= 1 << 3;
  return 1;
}

//puts light on if off and vice versa
int main_thread_iteration(const unsigned int led_is_on, struct gpio *dev)
{
  if (led_is_on) {
    dev->DR &= ~(1<<3);
  } else {
    dev->DR |= 1<<3;
  }
  delay_ms(MAIN_DELAY);
  return !led_is_on;
}

