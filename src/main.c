#define T Floats, float
#include <stc/vec.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	Floats nums = {0};
	Floats_push(&nums, 30.f);
	Floats_push(&nums, 10.f);
	Floats_push(&nums, 20.f);

	for (c_each(i, Floats, nums)) 
		printf(" %g\n", *i.ref);

	Floats_drop(&nums);

	return EXIT_SUCCESS;
}
