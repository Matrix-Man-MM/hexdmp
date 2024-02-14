#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void dump_hex(const unsigned char* data, size_t len) {
	for (size_t i = 0; i < 16; i++) {
		if (i < len)
			printf("%02X ", data[i]);
		else
			printf("   ");

		if (i == 7)
			printf(" ");
	}

	printf("| ");

	for (size_t i = 0; i < len && i < 16; i++)
		printf("%c", isprint(data[i]) ? data[i] : '.');

	printf("\n");

	if (len > 16)
		dump_hex(&data[16], len - 16);
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
