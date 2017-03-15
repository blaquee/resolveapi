#include "Kernel32.h"
#include <stdio.h>


int main(int argc, char** argv)
{
	PopulateKern32();
	PrintFuncs();

	VIRTUALALLOC vtAlloc = (VIRTUALALLOC) GetFunction("VirtualAlloc");

	void *p = vtAlloc(0, 32, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	printf("Allocated addr: %p\n", p);

	getchar();
	return 0;

}