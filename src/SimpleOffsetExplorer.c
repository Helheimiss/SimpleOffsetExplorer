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

    if (Process32First(snapshot, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, processName) == 0) {
                CloseHandle(snapshot);
                return pe.th32ProcessID;
            }
        } while (Process32Next(snapshot, &pe));
    }
    CloseHandle(snapshot);
    return 0;
}


uintptr_t GetModuleBaseAddress(DWORD pid, const char* modName) {
    MODULEENTRY32 modEntry;
    modEntry.dwSize = sizeof(MODULEENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (Module32First(snapshot, &modEntry)) {
        do {
            if (_stricmp(modEntry.szModule, modName) == 0) {
                CloseHandle(snapshot);
                return (uintptr_t)modEntry.modBaseAddr;
            }
        } while (Module32Next(snapshot, &modEntry));
    }
    CloseHandle(snapshot);
    return 0;
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


BOOL ReadMem(const char* processName, unsigned int offsets[], int offsetCount, void* outBuffer, size_t size) {
    DWORD pid = GetProcessIdByName(processName);
    if (pid == 0) {
        return FALSE;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(pid, processName);
    if (moduleBase == 0) {
        return FALSE;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        return FALSE;
    }

    uintptr_t finalAddress = FindDynamicAddress(hProcess, moduleBase, offsets, offsetCount);
    if (finalAddress == 0) {
        CloseHandle(hProcess);
        return FALSE;
    }

    if (!ReadProcessMemoryGeneric(hProcess, finalAddress, outBuffer, size)) {
        CloseHandle(hProcess);
        return FALSE;
    }

    CloseHandle(hProcess);
    return TRUE;
}


BOOL WriteMem(const char* processName, unsigned int offsets[], int offsetCount, void* newValue, size_t size) {
    DWORD pid = GetProcessIdByName(processName);
    if (pid == 0) {
        return FALSE;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(pid, processName);
    if (moduleBase == 0) {
        return FALSE;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        return FALSE;
    }

    uintptr_t finalAddress = FindDynamicAddress(hProcess, moduleBase, offsets, offsetCount);
    if (finalAddress == 0) {
        CloseHandle(hProcess);
        return FALSE;
    }

    if (WriteProcessMemoryGeneric(hProcess, finalAddress, newValue, size)) {
    } else {
        CloseHandle(hProcess);
        return FALSE;
    }

    CloseHandle(hProcess);
    return TRUE;
}