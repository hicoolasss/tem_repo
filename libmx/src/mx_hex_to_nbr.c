#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long first_counter = 0;
	unsigned long second_counter = 1;
	int length = 0;

	if (hex != NULL) {
		while (hex[length]) {
			length++;
        }
    }
	else {
		return first_counter;
    }
	for (int i = 0; i <= length; i++) {
		if (hex[length - i] >= '0' && hex[length - i] <= '9') {
			first_counter = first_counter + (hex[length - i] - 48) * second_counter;
			second_counter = second_counter * 16;
		}
		if (hex[length - i] >= 'A' && hex[length - i] <= 'F') {
			first_counter = first_counter + (hex[length - i] - 55) * second_counter;
			second_counter = second_counter * 16;
		}
		if (hex[length - i] >= 'a' && hex[length - i] <= 'f') {
			first_counter = first_counter + (hex[length - i] - 87) * second_counter;
			second_counter = second_counter * 16;
		}
	}
	return first_counter;
}
