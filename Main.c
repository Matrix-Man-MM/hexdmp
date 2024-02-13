#include <stdio.h>
#include <stdlib.h>

void dump_hex(const unsigned char* data, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%02X ", data[i]);

		if ((i + 1) % 8 == 0)
			printf(" ");

		if ((i + 1) % 16 == 0) {
			printf(" | ");

			for (size_t j = i - 15; j <= i; j++)
				printf("%c", (data[j] >= 32 && data[j] <= 126) ? data[j] : '.');

			printf("\n");
		}
	}

	size_t rem = len % 16;
	if (rem != 0) {
		for (size_t i = 0; i < 16 - rem; i++) {
			printf("   ");

			if ((i + rem + 1) % 8 == 0)
				printf(" ");
		}

		printf(" | ");

		for (size_t i = len - rem; i < len; i++)
			printf("%c", (data[i] >= 32 && data[i] <= 126) ? data[i] : '.');

		printf("\n");
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	FILE* f_ptr = fopen(argv[1], "rb");
	if (!f_ptr) {
		perror("Unable to open file!");
		exit(1);
	}

	unsigned char buffer[16];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), f_ptr)) > 0)
		dump_hex(buffer, bytes_read);

	fclose(f_ptr);

	return 0;
}