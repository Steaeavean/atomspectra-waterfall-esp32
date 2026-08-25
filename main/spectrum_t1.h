#pragma once
#include <stddef.h>
#define SPECTRUM_T1_REFRESH_MS 5000u
float spectrum_temp_from_token(const char *p);
int   spectrum_temp_json(char *buf, size_t cap, float t);
