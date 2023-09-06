#include <lab1.h>
#include <rtos.h>

unsigned int led_is_on;
unsigned int counter;

//flips on/off based on timer triggered interrupt
void thread_entry(void)
{
  unsigned int led_on, counter;
  led_on = toggle_thread_setup(GPIOA, &counter);
  while (1) {
    led_on = toggle_thread_iteration(led_on, GPIOA, &counter);
  }
}

//flips on/off based on main timer
void main(void)
{
  led_is_on = main_thread_setup(GPIOB);
  start_thread(thread_entry);

  while (1) {
    led_is_on = main_thread_iteration(led_is_on, GPIOB);
  }
}
