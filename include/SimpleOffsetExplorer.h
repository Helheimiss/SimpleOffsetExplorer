#ifndef SIMPLE_OFFSET_EXPLORER_H
#define SIMPLE_OFFSET_EXPLORER_H

#include <windows.h>

BOOL ReadMem(const char* processName, unsigned int offsets[], int offsetCount, void* outBuffer, size_t size);
BOOL WriteMem(const char* processName, unsigned int offsets[], int offsetCount, void* newValue, size_t size);

BOOL ReadMemEx(const char* processName, const char* moduleName, unsigned int offsets[], int offsetCount, void* outBuffer, size_t size);
BOOL WriteMemEx(const char* processName, const char* moduleName, unsigned int offsets[], int offsetCount, void* newValue, size_t size);

BOOL ToggleInterface(const char *iface_name, int enable);
BOOL BlockPort(int port, const char* direction);
BOOL UnblockPort(int port);

#endif