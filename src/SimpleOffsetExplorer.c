#include "../include/SimpleOffsetExplorer.h"

#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <stdint.h>


DWORD GetProcessIdByName(const char* processName) {
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    DWORD pid = 0;
    if (Process32First(snapshot, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, processName) == 0) {
                pid = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &pe));
    }
    CloseHandle(snapshot);
    return pid;
}


uintptr_t GetModuleBaseAddressEx(DWORD pid, const char* moduleName) {
    MODULEENTRY32 modEntry;
    modEntry.dwSize = sizeof(MODULEENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    uintptr_t baseAddress = 0;
    if (Module32First(snapshot, &modEntry)) {
        do {
            if (_stricmp(modEntry.szModule, moduleName) == 0) {
                baseAddress = (uintptr_t)modEntry.modBaseAddr;
                break;
            }
        } while (Module32Next(snapshot, &modEntry));
    }
    CloseHandle(snapshot);
    return baseAddress;
}


uintptr_t FindDynamicAddress(HANDLE hProcess, uintptr_t baseAddress, unsigned int offsets[], int count) {
    uintptr_t addr = baseAddress;
    for (int i = 0; i < count; i++) {
        addr += offsets[i];
        if (i < count - 1) { 
            if (!ReadProcessMemory(hProcess, (LPCVOID)addr, &addr, sizeof(addr), NULL)) {
                return 0;
            }
        }
    }
    return addr;
}

BOOL ReadProcessMemoryGeneric(HANDLE hProcess, uintptr_t address, void* buffer, size_t size) {
    return ReadProcessMemory(hProcess, (LPCVOID)address, buffer, size, NULL);
}

BOOL WriteProcessMemoryGeneric(HANDLE hProcess, uintptr_t address, void* buffer, size_t size) {
    return WriteProcessMemory(hProcess, (LPVOID)address, buffer, size, NULL);
}


static BOOL OpenProcessAndResolveAddress(const char* processName, const char* moduleName, const unsigned int offsets[], int offsetCount, uintptr_t* finalAddress, HANDLE* hProcessOut) {
    DWORD pid = GetProcessIdByName(processName);
    if (pid == 0)
        return FALSE;

    const char* modName = (moduleName != NULL) ? moduleName : processName;
    uintptr_t moduleBase = GetModuleBaseAddressEx(pid, modName);
    if (moduleBase == 0)
        return FALSE;

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if (hProcess == NULL)
        return FALSE;

    uintptr_t addr = FindDynamicAddress(hProcess, moduleBase, (unsigned int*)offsets, offsetCount);
    if (addr == 0) {
        CloseHandle(hProcess);
        return FALSE;
    }
    *finalAddress = addr;
    *hProcessOut = hProcess;
    return TRUE;
}


BOOL ReadMem(const char* processName, unsigned int offsets[], int offsetCount, void* outBuffer, size_t size) {
    return ReadMemEx(processName, NULL, offsets, offsetCount, outBuffer, size);
}

BOOL WriteMem(const char* processName, unsigned int offsets[], int offsetCount, void* newValue, size_t size) {
    return WriteMemEx(processName, NULL, offsets, offsetCount, newValue, size);
}


BOOL ReadMemEx(const char* processName, const char* moduleName, unsigned int offsets[], int offsetCount, void* outBuffer, size_t size) {
    uintptr_t finalAddress;
    HANDLE hProcess;
    if (!OpenProcessAndResolveAddress(processName, moduleName, offsets, offsetCount, &finalAddress, &hProcess))
        return FALSE;

    BOOL result = ReadProcessMemoryGeneric(hProcess, finalAddress, outBuffer, size);
    CloseHandle(hProcess);
    return result;
}

BOOL WriteMemEx(const char* processName, const char* moduleName, unsigned int offsets[], int offsetCount, void* newValue, size_t size) {
    uintptr_t finalAddress;
    HANDLE hProcess;
    if (!OpenProcessAndResolveAddress(processName, moduleName, offsets, offsetCount, &finalAddress, &hProcess))
        return FALSE;

    BOOL result = WriteProcessMemoryGeneric(hProcess, finalAddress, newValue, size);
    CloseHandle(hProcess);
    return result;
}
