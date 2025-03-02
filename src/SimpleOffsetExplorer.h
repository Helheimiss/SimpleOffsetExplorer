#ifndef SimpleOffsetExplorer_H
#define SimpleOffsetExplorer_H

#include <windows.h>

BOOL ReadMem(const char* processName, unsigned int offsets[], int offsetCount, void* outBuffer, size_t size);
BOOL WriteMem(const char* processName, unsigned int offsets[], int offsetCount, void* newValue, size_t size);

#endif