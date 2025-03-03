### 📖 **SimpleOffsetExplorer**  

---

# **EN: SimpleOffsetExplorer**  

## 📌 **Description**  
`SimpleOffsetExplorer` is a library for reading and writing memory in running Windows processes. It allows working with dynamic addresses using pointer chains (offset chain).  

⚠ **Warning!**  
Modifying another process's memory may cause crashes and violate software agreements. Use this library at your own risk.  

---

## 🔧 **Functions**  

### **Reading Memory**  
```c
BOOL ReadMem(const char* processName, const unsigned int offsets[], int offsetCount, void* outBuffer, size_t size);
```  
**Description:**  
Reads data from a process's memory using a given offset chain.  

**Parameters:**  
- `processName` — Name of the executable process (e.g., `"RDR2.exe"`).  
- `offsets` — Array of offsets to calculate the final address.  
- `offsetCount` — Number of elements in the `offsets` array.  
- `outBuffer` — Pointer to a buffer where the read data will be stored.  
- `size` — Size of the data to read.  

**Returns:**  
`TRUE` on success, `FALSE` on failure.  

---

### **Writing to Memory**  
```c
BOOL WriteMem(const char* processName, const unsigned int offsets[], int offsetCount, const void* newValue, size_t size);
```  
**Description:**  
Writes data to a process's memory using a given offset chain.  

**Parameters:**  
- `processName` — Name of the executable process (e.g., `"RDR2.exe"`).  
- `offsets` — Array of offsets to calculate the final address.  
- `offsetCount` — Number of elements in the `offsets` array.  
- `newValue` — Pointer to the data to write.  
- `size` — Size of the data to write.  

**Returns:**  
`TRUE` on success, `FALSE` on failure.  

---

## 🔹 **Usage Example**  
```c
#include <stdio.h>
#include "SimpleOffsetExplorer.h"

int main() {
    int newValue = 15251;
    unsigned int offsets[] = {0x052F2B58, 0x50, 0x108};

    if (WriteMem("RDR2.exe", offsets, 3, &newValue, sizeof(int))) {
        printf("New value written: %d\n", newValue);
    } else {
        printf("Memory write error!\n");
    }

    return 0;
}
```  

---

## ⚠ **Notes**  
- Running **as administrator** may be required.  
- Works only on **Windows**.  
- Use only for **legal** purposes.  

---

---  

# **RU: SimpleOffsetExplorer**  

## 📌 **Описание**  
`SimpleOffsetExplorer` — это библиотека для чтения и записи памяти в запущенных процессах Windows. Она позволяет работать с динамическими адресами, используя цепочку указателей (offset chain).  

⚠ **Внимание!**  
Изменение памяти чужого процесса может привести к его сбоям, а также нарушать лицензионные соглашения. Используйте библиотеку на свой страх и риск.  

---

## 🔧 **Функции**  

### **Чтение памяти**  
```c
BOOL ReadMem(const char* processName, const unsigned int offsets[], int offsetCount, void* outBuffer, size_t size);
```  
**Описание:**  
Считывает данные из памяти процесса по заданной цепочке смещений.  

**Параметры:**  
- `processName` — Имя исполняемого файла процесса (например, `"RDR2.exe"`).  
- `offsets` — Массив смещений для вычисления конечного адреса.  
- `offsetCount` — Количество элементов в массиве `offsets`.  
- `outBuffer` — Указатель на буфер, куда запишутся считанные данные.  
- `size` — Размер данных для чтения.  

**Возвращает:**  
`TRUE` — если чтение успешно, `FALSE` — если произошла ошибка.  

---

### **Запись в память**  
```c
BOOL WriteMem(const char* processName, const unsigned int offsets[], int offsetCount, const void* newValue, size_t size);
```  
**Описание:**  
Записывает данные в память процесса по заданной цепочке смещений.  

**Параметры:**  
- `processName` — Имя исполняемого файла процесса (например, `"RDR2.exe"`).  
- `offsets` — Массив смещений для вычисления конечного адреса.  
- `offsetCount` — Количество элементов в массиве `offsets`.  
- `newValue` — Указатель на данные, которые нужно записать.  
- `size` — Размер записываемых данных.  

**Возвращает:**  
`TRUE` — если запись успешна, `FALSE` — если произошла ошибка.  

---

## 🔹 **Пример использования**  
```c
#include <stdio.h>
#include "SimpleOffsetExplorer.h"

int main() {
    int newValue = 15251;
    unsigned int offsets[] = {0x052F2B58, 0x50, 0x108};

    if (WriteMem("RDR2.exe", offsets, 3, &newValue, sizeof(int))) {
        printf("Новое значение записано: %d\n", newValue);
    } else {
        printf("Ошибка записи в память!\n");
    }

    return 0;
}
```  

---

## ⚠ **Примечания**  
- Для работы библиотеки может потребоваться **запуск от имени администратора**.  
- Код работает только на **Windows**.  
- Используйте только для **легальных** целей.  

---