#pragma once
int read_int_2(void (*askFn)(), int (*validate)(void*), void (*ErrorFunction)());
void clear_buffer();