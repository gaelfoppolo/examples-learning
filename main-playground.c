
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types/out-enum.c"

int main(int argc, char const *argv[])
{
	OutEnum* test = (OutEnum*)malloc(sizeof(OutEnum));
	initOutEnum(test);

	int* x;

	vectPush(int, test->oenu, 1);
	vectPush(int, test->oenu, 4);
	vectPush(int, test->oenu, 12);
	vectPush(int, test->oenu, 5);

	vectIndexOf(test->oenu, 4, *x);

	printf("%d\n", *x);

	freeOutEnum(test);
	free(test);
	return 0;
}