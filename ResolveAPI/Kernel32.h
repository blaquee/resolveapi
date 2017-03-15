#pragma once
#ifndef _KERN32_H
#define _KERN32_H
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//Type defs
extern "C"
{
	typedef LPVOID(WINAPI * VIRTUALALLOC)(_In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);
	typedef BOOL(WINAPI * VIRTUALFREE)(_In_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD dwFreeType);
	typedef BOOL(WINAPI * VIRTUALPROTECT)(_In_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flNewProtect, _Out_ PDWORD lpflOldProtect);
	typedef HANDLE(WINAPI * HEAPCREATE)(_In_ DWORD flOptions, _In_ SIZE_T dwInitialSize, _In_ SIZE_T dwMaximumSize);
}
const unsigned int num_pointers = 4;

static VIRTUALALLOC _VirtualAlloc;
static VIRTUALFREE _VirtualFree;
static VIRTUALPROTECT _VirtualProtect;
static HEAPCREATE _HeapCreate;

#pragma pack(push,1)
typedef struct funcpointers {
	void* func_pointer;
	char canonical_name[MAX_PATH];
}_func_pointers;
#pragma pack(pop)

static _func_pointers k32_pointers[num_pointers] =
{
	{_VirtualAlloc, "VirtualAlloc"},
	{_VirtualFree, "VirtualFree"},
	{_VirtualProtect, "VirtualProtect"},
	{_HeapCreate, "HeapCreate"}
};

int PopulateFuncAddr(TCHAR* szDllName, _func_pointers* fp);
int PopulateKern32();
void PrintFuncs();
void* GetFunction(const char* funcName);

#endif