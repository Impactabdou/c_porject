#include "../include/shared.h"
#include <stdlib.h>
#include <string.h>

void sanitise_input(const char *input, char *output) {
  size_t j = 0;
  for (size_t i = 0; i < strlen(input); i++) {
    if (input[i] == 32)
      continue;
    output[j++] = input[i];
  }
}
