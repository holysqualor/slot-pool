#include <stdio.h>
#include "slpool.h"

void print(void *element, const void *ctx) {
	printf("%d\n", *(int*)element);
}

int main() {
	sl_pool pool = sl_create(sizeof(int));
	for(int element = 1; element <= 10; element++)
		sl_push_back(pool, &element);
	sl_for_each(pool, print, NULL);
	pool = sl_destroy(pool, NULL);
	return 0;
}
