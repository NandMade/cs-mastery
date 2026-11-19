#include <stdio.h>

int *make_counter(void) {
	int n = 0;
	return &n;
}

int main() {
	int *c = make_counter();

	printf("%d", *c);
}


