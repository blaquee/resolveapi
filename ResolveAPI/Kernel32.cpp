#include "Kernel32.h"



int PopulateFuncAddr(TCHAR* szDllName, _func_pointers* fp)
{
	HMODULE hModule = NULL;
	DWORD dwRetVal = 0;

	hModule = GetModuleHandle(szDllName);
	if (!hModule)
	{
		//Try LoadLib
		hModule = LoadLibrary(szDllName);
		if (!hModule)
			return dwRetVal;
	}
	for (int i = 0; i < num_pointers; ++i)
	{
		fp[i].func_pointer = GetProcAddress(hModule, fp[i].canonical_name);
		if (!fp[i].func_pointer)
		{
			printf("Function not found for %s\n", fp[i].canonical_name);
			return dwRetVal;
		}
	}
	return(!dwRetVal);
}

void* GetFunction(const char* funcName)
{
	for (int i = 0; i < num_pointers; ++i)
	{
		if (stricmp(funcName, k32_pointers[i].canonical_name) == 0)
			return k32_pointers[i].func_pointer;
	}
	return 0;
}


int PopulateKern32()
{
	return PopulateFuncAddr(TEXT("Kernel32"), k32_pointers);
}

void PrintFuncs()
{
	for (int i = 0; i < num_pointers; ++i)
	{
		printf("Function pointer: %X\tFunction Name: %s\n", (unsigned int*)k32_pointers[i].func_pointer,
			k32_pointers[i].canonical_name);
	}
}