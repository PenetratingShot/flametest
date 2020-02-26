#include "ports.h"

uint8_t port_byte_in(uint16_t port) {
  uint8_t result;
  __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
  return result;
}

void port_byte_out(uint16_t port, uint8_t data) {
  __asm__ __volatile__("out %%al, %%dx" : : "a"(data), "d"(port));
}

u16 port_word_in(uint16_t port) {
  u16 result;
  __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
  return result;
}

void port_word_out(uint16_t port, uint16_t data) {
  __asm__ __volatile__("out %%ax, %%dx" : : "a"(data), "d"(port));
}

void set_bit(uint8_t* input, uint8_t bit, uint8_t state) {
  if (state == 0) {
	*input &= ~(1 << bit);
  } else if (state == 1) {
	*input = (*input | (1 << bit));
  }
}