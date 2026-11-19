#include <limits.h>
#include <stdio.h>

int main() {
	int x = INT_MAX;
	printf("%d\n", x + 1 > x);

}
