# SimpleOffsetExplorer

## memory management example:

### GAME fields
```
char GAME[] = "GAME";
char MODULE[] = "mono-2.0-bdwgc.dll";

unsigned int[] hp_PTR = { 0x00494A90, 0xC98, 0x9B0 };
hp_PTR_len = 3;

float hp = 0;
float newValue = 33.3;
```
### ReadMemEx
```
BOOL ReadMemEx(
  const char* processName,
  const char* moduleName,
  unsigned int offsets[],
  int offsetCount, void*
  outBuffer,
  size_t size
);


BOOL ReadMemEx(
  GAME,
  MODULE,
  hp_PTR,
  hp_PTR_len,
  &hp,
  sizeof(float)
);
```
### WriteMemEx
```
BOOL WriteMemEx(
  const char* processName,
  const char* moduleName,
  unsigned int offsets[],
  int offsetCount,
  void* newValue,
  size_t size
);


WriteMemEx(
  GAME,
  MODULE,
  hp_PTR,
  hp_PTR_len,
  &newValue,
  sizeof(float)
);
```
## switch lag example:
### Interface
```
const char *iface_name = "Ethernet 0";
int port = 8080;
```
### ToggleInterface
```
BOOL ToggleInterface(int enable); // 1 or 0

ToggleInterface(0); // Turn off
ToggleInterface(1); // Turn on
```
### ToggleInterface_IfaceName
```
BOOL ToggleInterface_IfaceName(
    const char *iface_name,
    int enable /*1 or 0*/
);


ToggleInterface(iface_name, 0); // Turn off
ToggleInterface(iface_name, 1); // Turn on
```
### BlockPort
```
BOOL BlockPort(
  int port,
  const char* direction
);


BlockPort(port, "out"); // Blocking Outgoing 
BlockPort(port, "in"); // Blocking Incoming
```
### UnblockPort
```
BOOL UnblockPort(
  int port
);

UnblockPort(port);
```
