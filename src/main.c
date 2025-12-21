#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("----------------------------------\n");
	printf(" Project: shdrt\n");
	printf(" Status:  Running successfully\n");
	printf("----------------------------------\n");

	// Print arguments if any were provided
	if (argc > 1) {
		printf("Arguments provided:\n");
		for (int i = 1; i < argc; i++) {
			printf("  [%d]: %s\n", i, argv[i]);
		}
	} else {
		printf("No command-line arguments provided.\n");
	}

	return EXIT_SUCCESS;
}
