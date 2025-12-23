#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <stdexcept>

// Global variables (addresses in hp.exe)
char g_lpCmdLine1[512]; // 0xc82b88
char g_lpCmdLine2[512]; // 0xc82d88
char* g_anonArgs[32]; // 0xc82f88
char* g_argKeys[32]; // 0xc83008
char* g_argValues[32]; // 0xc83088
int g_anonArgCount = 0; // 0xc83108
int g_argCount = 0; // 0xc8310c
int g_width = 0; // 0xbf1940
int g_height = 0; // 0xbf1944
int g_bitDepth = 0; // 0xbf1948
int g_shadowLOD = 0; // 0xbf1954
int g_maxFarClip = 0; // 0xbf1958
int g_particleRate = 0; // 0xbf1960
int g_particleCullDistance = 0; // 0xbf195c
int g_cullDistance = 0; // 0xbf1964
int g_disableFog = 0; // 0xbf1968
int g_disablePostPro = 0; // 0xbf196c
int g_filterFlip = 0; // 0xbf1970
int g_aaMode = 0; // 0xbf1974
int g_useAdditionalModes = 0; // 0xbf197c
HWND g_hWnd = NULL; // 0xbef6cc
float g_fUnknown_8ae1dc = 0.0f; // 0x8ae1dc
uint8_t g_byte_8afbd9 = 0; // 0x8afbd9

// Added globals for message loop
uint8_t g_byte_bef6c5 = 0; // 0xbef6c5
uint8_t g_byte_bef6c7 = 0; // 0xbef6c7
uint8_t g_byte_bef67e = 0; // 0xbef67e
uint8_t g_byte_bef67c = 0; // 0xbef67c
uint8_t g_byte_bef67d = 0; // 0xbef67d
uint8_t g_byte_bef6d4 = 0; // 0xbef6d4
uint8_t g_byte_bef6d5 = 0; // 0xbef6d5
DWORD g_dword_bef6d8 = 0; // 0xbef6d8
void* g_dword_bef6d0 = NULL; // 0xbef6d0
void* g_dword_bf1920 = NULL; // 0xbf1920
void* g_dword_e6b384 = NULL; // 0xe6b384
void* g_dword_e6a070 = NULL; // 0xe6a070
void* g_dword_e6a194 = NULL; // 0xe6a194
DWORD g_dword_e74c20 = 0; // 0xe74c20
DWORD g_dword_c82b00 = 0; // 0xc82b00
DWORD g_dword_c82ac8 = 0; // 0xc82ac8
DWORD g_dword_c82b08 = 0; // 0xc82b08
DWORD g_dword_c83188 = 0; // 0xc83188
DWORD g_dword_c8318c = 0; // 0xc8318c
float g_float_8475d8 = 0.0f; // 0x8475d8
float g_float_845594 = 0.0f; // 0x845594
float g_float_845320 = 0.0f; // 0x845320
DWORD g_dword_8afb08 = 0; // 0x8afb08
void* g_dword_e6b2dc = NULL; // 0xe6b2dc
void* g_dword_bef6e4 = NULL; // 0xbef6e4
uint8_t g_byte_bf18aa = 0; // 0xbf18aa
uint32_t g_dword_bf193c = 0; // 0xbf193c
uint32_t g_dword_bf1930 = 0; // 0xbf1930
void* g_dword_bf1924 = NULL; // 0xbf1924
void* g_dword_b95034 = NULL; // 0xb95034
void* g_dword_e6a42c = NULL; // 0xe6a42c
void* g_dword_e6a674 = NULL; // 0xe6a674
uint32_t g_dword_e75234 = 0; // 0xe75234
uint32_t g_dword_e6e5e4 = 0; // 0xe6e5e4
uint32_t g_dword_e6e5e0 = 0; // 0xe6e5e0
uint32_t g_dword_c83198 = 0; // 0xc83198
uint32_t g_dword_c8319c = 0; // 0xc8319c
uint32_t g_dword_c831a8 = 0; // 0xc831a8
uint32_t g_dword_c831ac = 0; // 0xc831ac
uint32_t g_dword_c83190 = 0; // 0xc83190
uint32_t g_dword_c83194 = 0; // 0xc83194
uint32_t g_dword_8e1648 = 0; // 0x8e1648
uint64_t g_qword_c83170[2] = {0, 0}; // 0xc83170
void* g_dword_8e1644 = NULL; // 0x8e1644
uint32_t g_dword_c831a0 = 0; // 0xc831a0
uint32_t g_dword_c831a4 = 0; // 0xc831a4
uint32_t g_dword_c83110 = 0; // 0xc83110
uint32_t g_dword_c8311c = 0; // 0xc8311c
uint32_t g_dword_c83118 = 0; // 0xc83118
uint32_t g_dword_e6e5e8 = 0; // 0xe6e5e8
uint8_t g_byte_e6b388 = 0; // 0xe6b388
void* g_dword_bef7c0 = NULL; // 0xbef7c0
void* g_dword_bef768 = NULL; // 0xbef768
void* g_ptr_bef728 = NULL; // 0xbef728

struct Struct_E6E870 {
    void* vtable; // 0xe6e870
    void* field_4; // 0xe6e874
    uint32_t field_8; // 0xe6e878
    uint32_t field_C; // 0xe6e87c
    uint32_t field_10; // 0xe6e880
    uint32_t field_14; // 0xe6e884
    uint32_t field_18; // 0xe6e888
    uint32_t field_1C; // 0xe6e88c
    uint32_t field_20; // 0xe6e890
    uint32_t field_24; // 0xe6e894
    uint32_t field_28; // 0xe6e898
    uint32_t field_2C; // 0xe6e89c
    uint32_t field_30; // 0xe6e8a0
    uint32_t field_34; // 0xe6e8a4
    uint32_t field_38; // 0xe6e8a8
    uint32_t field_3C; // 0xe6e8ac
    uint32_t field_40; // 0xe6e8b0
    uint32_t field_44; // 0xe6e8b4
    uint32_t field_48; // 0xe6e8b8
    uint32_t field_4C; // 0xe6e8bc
};

Struct_E6E870 g_struct_e6e870; // 0xe6e870

STICKYKEYS g_stickyKeys; // 0x8afc44
TOGGLEKEYS g_toggleKeys; // 0x8afc4c
FILTERKEYS g_filterKeys; // 0x8afc54

// Forward declarations
LRESULT CALLBACK sub_60d6d0(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // 0x60d6d0
uint32_t sub_618010(); // 0x618010
extern "C" bool sub_68da30(); // 0x68da30
extern "C" void sub_6a9f20(void* p); // 0x6a9f20
extern "C" void sub_617b60(void* p); // 0x617b60
extern "C" bool sub_68dac0(); // 0x68dac0
void sub_66f810(const char* format, ...); // 0x66f810
void sub_79a712(int enable); // 0x79a712

// 0x00617d70
// Parses a single token from a string, handling quoted strings.
// Updates the string pointer to the next token.
char* sub_617d70(char** pStr) {
    char* start = *pStr;
    char c = *start;
    char* current = start;

    if (c == '"' || c == '\'') {
        // 0x617daa: Handle quoted strings.
        start++;
        *pStr = start;
        current = start;
        if (*current != '\0') {
            while (*current != '\0' && *current != c) {
                current++;
            }
        }
    } else {
        // 0x617d80: Handle regular tokens.
        if (c == '\0') return start;
        while (*current != '\0' && !isspace((unsigned char)*current)) {
            current++;
        }
    }

    if (*current != '\0') {
        // 0x617dce: Null-terminate the token and advance the pointer.
        *current = '\0';
        *pStr = current + 1;
    } else {
        *pStr = current;
    }
    return start;
}

// 0x00617c60
// Parses the command line into global key-value arrays and anonymous arguments.
void sub_617c60() {
    char* esi = g_lpCmdLine1; // 0x60e022
    while (true) {
        // 0xeb788c: Skip leading whitespace.
        while (*esi != '\0' && isspace((unsigned char)*esi)) {
            esi++;
        }

        if (*esi == '\0') break;

        if (*esi == '-') {
            // 0xeb78b5: It's a keyed argument (e.g., -Width=800).
            esi++;
            char* key = esi;
            char* value = NULL;

            // 0xeb78cb: Search for the end of the key (space or '=').
            while (*esi != '\0' && !isspace((unsigned char)*esi) && *esi != '=') {
                esi++;
            }

            if (*esi == '=') {
                // 0xeb78f1: Key-value pair found.
                *esi = '\0';
                esi++;
                value = sub_617d70(&esi); // 0xeb790f
            } else {
                // 0xeb78f4: Only a key found.
                if (*esi != '\0') {
                    *esi = '\0';
                    esi++;
                }
            }

            if (g_argCount < 32) {
                // 0xeb7925: Store the key and value.
                g_argKeys[g_argCount] = key;
                g_argValues[g_argCount] = value;
                g_argCount++;
            }
        } else {
            // 0xeb7942: It's an anonymous argument.
            if (g_anonArgCount < 32) {
                char* arg = sub_617d70(&esi); // 0xeb7953
                g_anonArgs[g_anonArgCount] = arg;
                g_anonArgCount++;
            } else {
                // Buffer full, skip the token.
                sub_617d70(&esi);
            }
        }
    }
}

// 0x0060ce20
// Helper function that wraps RegQueryValueExA for reading string values.
bool sub_60ce20(HKEY hKey, const char* lpValueName, char* lpData, LPDWORD lpcbData) {
    DWORD type = REG_SZ;
    return RegQueryValueExA(hKey, lpValueName, NULL, &type, (LPBYTE)lpData, lpcbData) == ERROR_SUCCESS;
}

// 0x0060cc70
// Helper function for registry-related error logging/verification.
// It constructs the registry path, attempts to open the key, and throws an exception
// if it fails. It also performs some validation on the value.
void sub_60cc70(const char* section, const char* key, const char* appName, const char* message) {
    std::string path = "Software\\Electronic Arts\\";
    if (appName && *appName) {
        path += appName;
        path += "\\";
    }
    path += section;

    HKEY hKey = NULL;
    // 0x60cfab: Attempt to open the key in HKEY_CURRENT_USER.
    if (RegOpenKeyExA(HKEY_CURRENT_USER, path.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        // 0x60cd2e: If opening fails, throw an exception with a descriptive error message.
        std::string err = "Bad registry location - section '";
        err += path;
        err += "'";
        throw std::runtime_error(err);
    }

    char buffer[256];
    DWORD bufferSize = sizeof(buffer);
    DWORD type = REG_SZ;
    // 0x60cdf3: Read the registry value.
    if (RegQueryValueExA(hKey, key, NULL, &type, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
        // 0x60cd0e: Some internal validation (e.g., check for placeholder values like "unknown").
        if (std::string(buffer) == "unknown") {
             // In the original, it might do more, but for now we just close and return.
        }
    } else {
        // 0x60cd2e: If reading fails, throw an exception.
        RegCloseKey(hKey);
        std::string err = "Bad data to write to registry - sect '";
        err += section;
        err += "' value '";
        err += key;
        err += "'";
        throw std::runtime_error(err);
    }

    RegCloseKey(hKey); // 0x60ce02
}

// 0x0060ce60
// Reads an integer value from the registry. It first attempts to read from
// HKEY_CURRENT_USER and falls back to HKEY_LOCAL_MACHINE if not found.
// The registry path is "Software\Electronic Arts\<appName>\<section>".
int sub_60ce60(const char* section, const char* key, const char* appName, int defaultValue) {
    std::string path = "Software\\Electronic Arts\\";
    if (appName && *appName) {
        path += appName;
        path += "\\";
    }
    path += section;

    HKEY hKey;
    int result = defaultValue;
    char buffer[256];
    DWORD bufferSize = sizeof(buffer);

    // 0x60cfab: Attempt to open the key in HKEY_CURRENT_USER.
    if (RegOpenKeyExA(HKEY_CURRENT_USER, path.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // 0x60cfc9: Call helper to read the value as a string and convert to int.
        if (sub_60ce20(hKey, key, buffer, &bufferSize)) {
            result = atoi(buffer);
        }
        RegCloseKey(hKey); // 0x60d07b
    } 
    // 0x60cff5: Fallback to HKEY_LOCAL_MACHINE if not found in HKCU.
    else if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (sub_60ce20(hKey, key, buffer, &bufferSize)) {
            result = atoi(buffer);
        }
        RegCloseKey(hKey);
    }

    return result;
}

// 0x0060da90
// Registers the main window class.
bool sub_60da90(HINSTANCE hInstance) {
    UnregisterClassA("OrderOfThePhoenixMainWndClass", hInstance);

    WNDCLASSEXA wc;
    // Initialize with 0
    memset(&wc, 0, sizeof(wc));

    if (g_byte_8afbd9 == 0) {
        wc.style = 0x2020; // CS_BYTEALIGNWINDOW | CS_OWNDC (?)
        wc.hCursor = NULL;
    } else {
        wc.style = 0x2000; // CS_BYTEALIGNWINDOW (?)
        wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    }

    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.lpfnWndProc = (WNDPROC)sub_60d6d0;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "OrderOfThePhoenixMainWndClass";
    wc.hIconSm = NULL;

    return RegisterClassExA(&wc) != 0;
}

// 0x0060db20
// Creates the main window.
HWND sub_60db20(void* this_ptr, HINSTANCE hInstance, char* lpCmdLine, int nShowCmd) {
    DWORD dwStyle;
    DWORD dwExStyle;

    if (g_byte_8afbd9 == 0) {
        dwStyle = WS_OVERLAPPEDWINDOW;
        dwExStyle = 0; // The assembly used 3, but 0 is safer for now unless we know what 3 means (WS_EX_TOPMOST | WS_EX_NOPARENTNOTIFY)
    } else {
        dwStyle = WS_POPUP;
        dwExStyle = WS_EX_APPWINDOW | WS_EX_TOPMOST; // 0x2003 approx?
    }

    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = g_width;
    rect.bottom = g_height;

    AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    
    // Center the window if windowed
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;

    if (g_byte_8afbd9 == 0) {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        x = (screenWidth - width) / 2;
        y = (screenHeight - height) / 2;
    }

    HWND hWnd = CreateWindowExA(
        dwExStyle,
        "OrderOfThePhoenixMainWndClass",
        "Harry Potter and the Order of the Phoenix",
        dwStyle,
        x, y, width, height,
        NULL, NULL, hInstance, NULL
    );

    if (!hWnd) return NULL;

    if (g_byte_8afbd9 != 0) {
        SetMenu(hWnd, NULL);
        SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_CONTINUOUS); // 0x80000002
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return hWnd;
}
// 0x00617bf0
// Searches for a key in the parsed command line arguments.
// If found, it optionally returns the value string pointer.
// Returns true if found, false otherwise.
bool __stdcall sub_617bf0(void* context, const char* key, char** outValue) {
    // context is a pointer to the start of the command line global block (0xc82b88)
    // 0x617bf7: Initialize loop counter (esi = 0)
    // 0x617bf9: Compare counter with count at 0x584(ebx)
    
    char** keys = (char**)((char*)context + 0x480); // 0xc83008 (g_argKeys)
    char** values = (char**)((char*)context + 0x500); // 0xc83088 (g_argValues)
    int count = *(int*)((char*)context + 0x584); // 0xc8310c (g_argCount)

    for (int i = 0; i < count; i++) {
        // 0x617c18: Call _stricmp (pointer at 0x7b72d8)
        if (_stricmp(keys[i], key) == 0) {
            // 0x617c38: Found the key
            if (outValue) {
                // 0x617c40: Store the pointer to the value string
                *outValue = values[i];
            }
            return true; // 0x617c4c
        }
    }
    
    // 0x617c32: Not found
    return false;
}
// Stubs for functions called by sub_60dc10
// 0x0079ea80
// 64-bit arithmetic shift right helper.
// Takes a 64-bit value and a shift count.
int64_t sub_79ea80(int64_t value, uint8_t shift) {
    return value >> shift;
}
// 0x00612f00
// Initializes a global structure at 0xe6e870.
void* sub_612f00() {
    g_struct_e6e870.field_10 = 0;
    g_struct_e6e870.field_14 = 0;
    g_struct_e6e870.field_18 = 0;
    g_struct_e6e870.field_1C = 0;
    g_struct_e6e870.field_20 = 0;
    g_struct_e6e870.field_24 = 0;
    g_struct_e6e870.field_28 = 0;
    g_struct_e6e870.field_2C = 0;
    
    g_struct_e6e870.vtable = (void*)0x883f3c;
    g_struct_e6e870.field_4 = (void*)0x883f4c;
    
    g_ptr_bef728 = &g_struct_e6e870;
    
    return &g_struct_e6e870;
}
// 0x006f5338
// Internal CRT function used by atexit (likely _onexit).
void* sub_6f5338(void* pFunc) { return NULL; } // stub

// 0x006f53d7
// Registers a function to be called at program termination (atexit).
// It wraps an internal function (sub_6f5338) and converts its return value
// to the standard atexit return format (0 for success, -1 for failure).
int sub_6f53d7(void* pFunc) {
    // 0x6f53db: Call internal registration function.
    void* result = sub_6f5338(pFunc);
    
    // 0x6f53e0 - 0x6f53e4: Convert non-zero result to 1, and zero to 0 (!!result).
    // 0x6f53e7: decrement (!!result - 1).
    // If sub_6f5338 returned a non-zero pointer (success), this returns 0.
    // If sub_6f5338 returned NULL (failure), this returns -1.
    return (result != NULL) ? 0 : -1;
}
// 0x00616590
// Scans through several internal containers and lists to find the maximum
// value of a specific field (offset 0x4, masked with 0x7ffffff8).
// This is likely part of a custom memory manager or object allocator,
// potentially finding the largest free block or highest allocated address.
uint32_t sub_616590(void* p) {
    uint8_t* pObj = (uint8_t*)p;
    
    // 0xeb6dbd: Get pointer to a structure that starts with a CRITICAL_SECTION (0x7b7084)
    void* pSync = *(void**)(pObj + 0x4e4);
    if (pSync) {
        EnterCriticalSection((LPCRITICAL_SECTION)pSync);
        // 0xeb6dcf: Increment a counter located immediately after the CRITICAL_SECTION (at offset 24)
        (*(uint32_t*)((uint8_t*)pSync + 24))++;
    }

    uint32_t maxVal = 0;

    // 0xeb6dd3: Initial object at offset 0x440
    uint8_t* pSubObj440 = *(uint8_t**)(pObj + 0x440);
    if (pSubObj440) {
        // 0xeb6de3: Get field at +0x4 and mask flags
        maxVal = *(uint32_t*)(pSubObj440 + 0x4) & 0x7FFFFFF8;

        // 0xeb6dec - 0xeb6e0c: Scan an array of 127 entries at offset 0x428 (backwards)
        uint8_t* pArrayEntry = pObj + 0x428;
        for (int i = 0xFE; i >= 0x02; i -= 2) {
            uint8_t* entry = *(uint8_t**)pArrayEntry;
            // 0xeb6dfe: Check if the entry is valid/active
            if (*(uint8_t**)(entry + 0x0C) != entry) {
                uint32_t val = *(uint32_t*)(entry + 0x04) & 0x7FFFFFF8;
                if (val > maxVal) maxVal = val;
            }
            pArrayEntry -= 8;
        }
    }

    // 0xeb6e1e - 0xeb6e3d: Scan a circular linked list starting at offset 0x3C
    uint8_t* listHead = *(uint8_t**)(pObj + 0x3C);
    uint8_t* listSentinel = pObj + 0x30;
    while (listHead != listSentinel) {
        uint32_t val = *(uint32_t*)(listHead + 0x04) & 0x7FFFFFF8;
        if (val > maxVal) maxVal = val;
        listHead = *(uint8_t**)(listHead + 0x0C);
    }

    // 0xeb6e3f: If found max is less than a threshold at +0x4, check another array
    if (maxVal < *(uint32_t*)(pObj + 0x04)) {
        // 0xeb6e44 - 0xeb6e5a: Scan an array of 10 entries at offset 0x2C (backwards)
        uint8_t* pArrayEntry2 = pObj + 0x2C;
        for (int i = 9; i >= 0; i--) {
            uint8_t* entry = *(uint8_t**)pArrayEntry2;
            if (entry) {
                uint32_t val = *(uint32_t*)(entry + 0x04) & 0x7FFFFFF8;
                if (val > maxVal) maxVal = val;
            }
            pArrayEntry2 -= 4;
        }
    }

    if (pSync) {
        // 0xeb6e70: Decrement the counter
        (*(uint32_t*)((uint8_t*)pSync + 24))--;
        // 0xeb6e75: Leave the critical section (0x7b7080)
        LeaveCriticalSection((LPCRITICAL_SECTION)pSync);
    }

    return maxVal;
}
uint32_t sub_618010(); // forward decl
void sub_6aaaa0(int param) {} // 0x6aaaa0 stub
void sub_6a9330(int param) {} // 0x6a9330 stub

// 0x006a9f20
// Updates timing and performance counters for an object.
// It calculates elapsed time, scales it by a factor, and updates internal 64-bit counters.
// It also potentially calls sub-update functions if certain conditions are met.
void sub_6a9f20(void* p) {
    uint8_t* pObj = (uint8_t*)p;
    if (!pObj) return;

    // 0xec67ec: Get pointer to timing structure
    uint8_t* pTiming = *(uint8_t**)(pObj + 0x70);
    // 0xec67f1: Reset a flag/status byte
    *(uint8_t*)(pObj + 0xa0) = 0;
    
    uint32_t currentTime = 0;
    if (pTiming) {
        // 0xec67fa: Get current timer value (0x618010)
        currentTime = sub_618010();
        uint32_t lastTime = *(uint32_t*)pTiming;
        uint32_t delta = currentTime - lastTime;
        uint32_t factor = *(uint32_t*)(pTiming + 0x10);
        
        if (factor == 0x1000) {
            // 0xec680e: Simple 64-bit addition of delta
            uint32_t* pLow = (uint32_t*)(pTiming + 0x08);
            uint32_t* pHigh = (uint32_t*)(pTiming + 0x0C);
            uint32_t oldLow = *pLow;
            *pLow = oldLow + delta;
            if (*pLow < oldLow) (*pHigh)++;
        } else {
            // 0xec681e - 0xec682c: Scaled 64-bit addition
            // (delta * factor) >> 12
            uint64_t scaledDelta = ((uint64_t)delta * factor) >> 12;
            *(uint64_t*)(pTiming + 0x08) += scaledDelta;
        }
        // 0xec6811/0xec682a: Update last time stamp
        *(uint32_t*)pTiming = currentTime;
        // 0xec6817/0xec682f: Get time again for the next part
        currentTime = sub_618010();
    }
    
    // 0xec6838: Calculate more timing deltas
    uint32_t timeDiff = currentTime - *(uint32_t*)(pObj + 0x58);
    *(uint32_t*)(pObj + 0x5c) += timeDiff;
    
    // 0xec683e: Conditional sub-update
    if (*(uint32_t*)(pObj + 0x48) == 0) {
        if (*(void**)pObj != NULL) {
            // 0xec684f: Call sub_6aaaa0(0x1000)
            sub_6aaaa0(0x1000);
        }
    }
    
    // 0xec6854: Final conditional sub-update
    if (*(void**)(pObj + 0x70) != NULL) {
        // 0xec6860: Call sub_6a9330(0x1000)
        sub_6a9330(0x1000);
    }
}
uint32_t g_state_c7b908 = 0; // 0xc7b908
void* g_ptr_bf1a88 = NULL; // 0xbf1a88
uint32_t g_dword_c7b90c = 0; // 0xc7b90c
void* g_ptr_c7c370 = NULL; // 0xc7c370
uint8_t g_byte_c6d7e0 = 0; // 0xc6d7e0
void* g_ptr_c7b924 = NULL; // 0xc7b924
uint8_t g_array_c7ba4c[0x1B0] = {0}; // 0xc7ba4c (6 entries * 0x48 bytes)
void* g_ptr_c7d038 = NULL; // 0xc7d038

void sub_6a4510(void* p) {} // 0x6a4510 stub
void sub_40f2f0(void* p) {} // 0x40f2f0 stub
void sub_40efb0(void* p1, int p2) {} // 0x40efb0 stub

// 0x0058b8a0
// Game state manager / object cleanup function.
// Based on the current state (g_state_c7b908), it performs various operations
// on global objects, typically calling a specific virtual function (offset 0x28).
void sub_58b8a0() {
    uint32_t state = g_state_c7b908;
    if (state > 6) return;

    if (state <= 3) {
        // 0x58b8b6: Cases 0, 1, 2, 3
        void* pObj = g_ptr_bf1a88;
        void* arg;
        if (pObj == NULL) {
            arg = (void*)0xffffffff;
        } else {
            arg = (void*)0x84d1d8;
            if (*(void**)((uint8_t*)pObj + 4) != NULL) {
                sub_6a4510(arg);
            } else {
                sub_40f2f0(arg);
            }
        }
        sub_40efb0(arg, 1000);
        
        // 0x58b8ec: Update a timer/counter and transition state
        uint32_t val = g_dword_c8311c;
        g_dword_c7b90c = (uint32_t)((((uint64_t)val * 0x55555556) >> 32) + (val >> 31) + 1000);
        g_state_c7b908 = 7;
        state = 4; // Fall through to Case 4 logic
    }

    if (state == 4 || state == 6) {
        // 0x58b918: Case 4
        // 0x58b98e: Case 6
        void* pObjC7C370 = g_ptr_c7c370;
        if (pObjC7C370) {
            void** vtable = *(void***)pObjC7C370;
            ((void (__stdcall *)(void*))vtable[10])(pObjC7C370); // 0x28 / 4 = 10
            g_byte_c6d7e0 = 0;
        }
        
        if (state == 6) return;

        void* pObjC7B924 = g_ptr_c7b924;
        if (pObjC7B924) {
            void** vtable = *(void***)pObjC7B924;
            ((void (__stdcall *)(void*))vtable[10])(pObjC7B924);
        }

        // 0x58b942: Iterate through an array of objects
        for (int i = 0; i < 6; i++) {
            void* pEntry = *(void**)(g_array_c7ba4c + i * 0x48);
            if (pEntry) {
                void** vtable = *(void***)pEntry;
                ((void (__stdcall *)(void*))vtable[10])(pEntry);
            }
        }

        // 0x58b95f: Iterate through another set of objects
        uint8_t* pObjC7D038 = (uint8_t*)g_ptr_c7d038;
        if (pObjC7D038) {
            uint8_t* pSub = pObjC7D038 + 0x0c;
            for (int i = 0; i < 2; i++) {
                if (*(uint32_t*)(pSub + 0x10) != 0) {
                    void* pEntry = *(void**)pSub;
                    if (pEntry) {
                        void** vtable = *(void***)pEntry;
                        ((void (__stdcall *)(void*))vtable[10])(pEntry);
                    }
                }
                pSub += 0x2c;
            }
        }
    }
}
void sub_66f810(const char* format, ...) {
    char buffer[2048];
    va_list args;
    va_start(args, format);
    _vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
}
uint32_t g_dword_bf1b1c = 0; // 0xbf1b1c
void* g_ptr_bf1b20 = NULL; // 0xbf1b20
uint32_t g_dword_bf1b18 = 0; // 0xbf1b18
uint32_t g_dword_bf1b2c = 0; // 0xbf1b2c
HANDLE g_handle_bf1b34 = NULL; // 0xbf1b34
uint32_t g_dword_bf1b30 = 0; // 0xbf1b30

void sub_611800() {} // 0x611800 stub
void sub_6119c0(void* p) {} // 0x6119c0 stub
void sub_6ace30() {} // 0x6ace30 stub
void sub_6108c0() {} // 0x6108c0 stub
void sub_6ac930() {} // 0x6ac930 stub

// 0x006a8f90
// Performs general cleanup of global resources and handles.
// It checks various global flags and pointers, calling specialized cleanup functions
// and closing open handles (like g_handle_bf1b34).
void sub_6a8f90() {
    // 0xec6613: Check first cleanup condition
    if (g_dword_bf1b1c != 0) {
        sub_611800(); // 0x611800
        sub_6119c0(g_ptr_bf1b20); // 0x6119c0
        g_dword_bf1b18 = 0;
        g_dword_bf1b1c = 0;
    }

    // 0xec6636 - 0xec6640: Call additional cleanup functions
    sub_6ace30(); // 0x6ace30
    sub_6108c0(); // 0x6108c0
    sub_6ac930(); // 0x6ac930

    // 0xec6645: Check if a handle needs to be closed
    if (g_dword_bf1b2c != 0) {
        if (g_handle_bf1b34 != NULL) {
            // 0xec6659: CloseHandle(g_handle_bf1b34) (0x7b7158)
            CloseHandle(g_handle_bf1b34);
        }
        g_dword_bf1b2c = 0;
        g_handle_bf1b34 = NULL;
        g_dword_bf1b30 = 0;
    }
}
// 0x0067d2e0
// Updates the global variable g_dword_bf193c with the available texture memory in MB.
// It calls the Direct3D GetAvailableTextureMem virtual function.
void sub_67d2e0() {
    if (g_dword_bf1920 == NULL) return;
    
    // Call GetAvailableTextureMem (virtual function at index 4)
    typedef UINT (__stdcall *GetAvailableTextureMemPtr)(void*);
    void* device = g_dword_bf1920;
    void** vtable = *(void***)device;
    GetAvailableTextureMemPtr GetAvailableTextureMem = (GetAvailableTextureMemPtr)vtable[4]; // 0x10 / 4 = 4
    
    UINT availableMem = GetAvailableTextureMem(device);
    
    // 0x67d2f6: Convert bytes to MB (shift right by 20)
    g_dword_bf193c = availableMem >> 20;
}
uint32_t g_dword_af1390 = 0; // 0xaf1390
uint32_t g_dword_ae9250 = 0; // 0xae9250
void* g_ptr_bf1934 = NULL; // 0xbf1934
void* g_ptr_bf1938 = NULL; // 0xbf1938

void sub_6750a0() {} // 0x6750a0 stub
void sub_67ecf0(void* p, int val) {} // 0x67ecf0 stub
void sub_6836e0() {} // 0x6836e0 stub

// 0x0067cfb0
// Performs cleanup of various resources, typically called when the Direct3D
// device is lost or being reset. It releases specific textures and buffers.
void sub_67cfb0() {
    // 0x67cfb6: Release resource at 0xb95034
    if (g_dword_b95034 != NULL) {
        void** vtable = *(void***)g_dword_b95034;
        typedef ULONG (__stdcall *ReleasePtr)(void*);
        ((ReleasePtr)vtable[2])(g_dword_b95034); // 0x08 / 4 = 2
        g_dword_b95034 = NULL;
    }

    // 0x67cfdc: Call additional cleanup
    sub_6750a0();
    
    // 0x67cfe1 - 0x67cfeb: Reset global pointers/counters
    g_dword_af1390 = 0;
    g_dword_ae9250 = 0;

    // 0x67cff5: Handle resource at 0xbf1934
    if (g_ptr_bf1934 != NULL && g_ptr_bf1934 != (void*)0xBACB0FFE) {
        void* pTempObj = NULL;
        // 0x67d021: Call virtual function at index 5 of 0xbf1924 (GetRenderTarget?)
        if (g_dword_bf1924 != NULL) {
             void** vtableDev = *(void***)g_dword_bf1924;
             typedef HRESULT (__stdcall *FuncPtr5)(void*, uint32_t, uint32_t, void**);
             ((FuncPtr5)vtableDev[5])(g_dword_bf1924, 0, 0, &pTempObj); // 0x14 / 4 = 5
        }
        
        if (pTempObj != NULL) {
            sub_67ecf0(pTempObj, 0);
            // 0x67d040: Release the temp object
            void** vtableTemp = *(void***)pTempObj;
            ((ULONG (__stdcall *)(void*))vtableTemp[2])(pTempObj);
        }
        
        // 0x67d054: Release the resource at 0xbf1934
        void** vtable34 = *(void***)g_ptr_bf1934;
        ((ULONG (__stdcall *)(void*))vtable34[2])(g_ptr_bf1934);
        g_ptr_bf1934 = NULL;
    }
    
    // 0x67d063: Handle resource at 0xbf1930
    if (g_dword_bf1930 != 0) {
        void* pObj30 = (void*)g_dword_bf1930;
        void** vtable30 = *(void***)pObj30;
        ((ULONG (__stdcall *)(void*))vtable30[2])(pObj30);
        g_dword_bf1930 = 0;
    }

    // 0x67d08c: Handle resource at 0xbf1938
    if (g_ptr_bf1938 != NULL) {
        void** vtable38 = *(void***)g_ptr_bf1938;
        ((ULONG (__stdcall *)(void*))vtable38[2])(g_ptr_bf1938);
        g_ptr_bf1938 = NULL;
    }

    // 0x67d0b5: Final cleanup call
    sub_6836e0();
}
uint32_t g_dword_8ae1e8 = 0; // 0x8ae1e8
uint32_t g_dword_8ae1e4 = 0; // 0x8ae1e4
uint8_t g_byte_8ae1fe = 0; // 0x8ae1fe
uint8_t g_byte_8ae1fd = 0; // 0x8ae1fd

void sub_675950() {} // 0x675950 stub
void sub_67b820() {} // 0x67b820 stub
void sub_67bb20() {} // 0x67bb20 stub
void* sub_66dfe0() { return NULL; } // 0x66dfe0 stub
void sub_674430() {} // 0x674430 stub

// 0x0067d0c0
// Restores Direct3D resources after a device reset.
// It re-acquires render targets and depth stencil surfaces.
void sub_67d0c0() {
    sub_675950();
    if (g_dword_b95034 == NULL) {
        sub_67b820();
    }
    sub_67bb20();

    // 0x67d0f5: Get current render target (index 5 of g_dword_bf1924)
    if (g_dword_bf1924 != NULL) {
        void** vtableDev = *(void***)g_dword_bf1924;
        typedef HRESULT (__stdcall *GetRenderTargetPtr)(void*, uint32_t, void**);
        ((GetRenderTargetPtr)vtableDev[5])(g_dword_bf1924, 0, (void**)&g_dword_bf1930);
    }
    
    g_dword_af1390 = (uint32_t)g_dword_bf1930;

    // 0x67d135: Get surface description (index 12)
    uint32_t desc[8] = {0};
    if (g_dword_af1390 != 0) {
        void* pObj30 = (void*)g_dword_af1390;
        void** vtable30 = *(void***)pObj30;
        typedef HRESULT (__stdcall *GetDescPtr)(void*, uint32_t*);
        ((GetDescPtr)vtable30[12])(pObj30, desc); // 0x30 / 4 = 12
    }

    // 0x67d167: Create depth stencil surface (index 29 of g_dword_bf1920)
    if (g_dword_bf1920 != NULL) {
        void** vtableD3D = *(void***)g_dword_bf1920;
        typedef HRESULT (__stdcall *CreateDSSPtr)(void*, UINT, UINT, uint32_t, uint32_t, uint32_t, BOOL, void**, HANDLE*);
        ((CreateDSSPtr)vtableD3D[29])(g_dword_bf1920, g_dword_8ae1e4, g_dword_8ae1e8, 0, 0, 0, FALSE, (void**)&g_ptr_bf1938, NULL);
    }

    // 0x67d184: Conditional setup
    if (g_filterFlip == 0) {
        if (g_byte_8ae1fe != 0 && g_byte_8ae1fd != 0) {
            void* pObj66 = sub_66dfe0();
            if (pObj66) {
                uint32_t flags = *(uint32_t*)((uint8_t*)pObj66 + 0x3c);
                if (!(flags & 0x100) && !(flags & 0x02)) {
                     // 0x67d1ee: Set render target (index 23)
                     if (g_dword_bf1920 != NULL) {
                         void** vtableD3D = *(void***)g_dword_bf1920;
                         typedef HRESULT (__stdcall *SetRTPtr)(void*, uint32_t, void*);
                         ((SetRTPtr)vtableD3D[23])(g_dword_bf1920, 0, (void*)g_dword_bf1930);
                     }
                     
                     // 0x67d205: Release old target
                     if (g_dword_bf1930 != 0) {
                         void* pObj30 = (void*)g_dword_bf1930;
                         void** vtable30 = *(void***)pObj30;
                         ((ULONG (__stdcall *)(void*))vtable30[2])(pObj30);
                     }
                     
                     g_ptr_bf1934 = NULL; // Placeholder for the result of the complex call at 0x67d1db
                     g_dword_bf1930 = g_dword_af1390;
                }
            }
        }
    }

    // 0x67d252: Set depth stencil surface (index 37)
    if (g_dword_bf1920 != NULL) {
        void** vtableD3D = *(void***)g_dword_bf1920;
        typedef HRESULT (__stdcall *SetDSSPtr)(void*, void*);
        ((SetDSSPtr)vtableD3D[37])(g_dword_bf1920, (void*)g_dword_af1390);
    }

    // 0x67d270: Set render target (index 39)
    if (g_dword_bf1920 != NULL) {
        void** vtableD3D = *(void***)g_dword_bf1920;
        typedef HRESULT (__stdcall *SetRTPtr)(void*, uint32_t, void*);
        ((SetRTPtr)vtableD3D[39])(g_dword_bf1920, 0, g_ptr_bf1938);
    }

    sub_674430();
}
uint8_t g_byte_8ae1ff = 0; // 0x8ae1ff
uint32_t g_dword_8ae200 = 0; // 0x8ae200
void* g_ptr_bf19a8 = NULL; // 0xbf19a8
uint32_t g_dword_bf1994 = 0; // 0xbf1994
uint32_t g_dword_8ae1ec = 0; // 0x8ae1ec
uint32_t g_array_8da10c[32] = {0}; // 0x8da10c
uint32_t g_dword_8ae204 = 0; // 0x8ae204
uint32_t g_dword_bf194c = 0; // 0xbf194c

// 0x0066e080
// Calculates a memory budget or quality setting (g_dword_8ae204) based on
// available texture memory and various global flags.
void sub_66e080() {
    uint32_t mem = g_dword_bf193c;
    uint32_t budget;

    // 0xebe85b: Check primary condition flag
    if (g_byte_8ae1ff != 0) {
        // 0xebe86a: Case where g_byte_8ae1ff is set
        uint8_t* pObj = (uint8_t*)g_ptr_bf19a8;
        uint32_t val = *(uint32_t*)(pObj + g_dword_8ae200 * 0x584 + 0x474);
        
        // 0xebe882: Check specific bit in object field
        budget = (val & 0x800) ? 0x40 : 0x20;
        
        // 0xebe891: Check if another flag/count is above threshold
        if (g_dword_bf1994 >= 2) {
            budget = 0x80;
        }
        
        // 0xebe8cb: Shift budget by value at 0x8ae1ec
        budget <<= g_dword_8ae1ec;
    } else {
        // 0xebe8a7: Default case
        budget = g_array_8da10c[g_dword_8ae1ec];
        
        // 0xebe8b3: Double budget if memory >= 384MB
        if (mem >= 0x180) budget <<= 1;
        
        // 0xebe8c0: Double budget if memory >= 512MB
        if (mem >= 0x200) budget <<= 1;
    }

    // 0xebe8cd: Halve budget if memory <= 64MB
    if (mem <= 0x40) budget >>= 1;
    
    // 0xebe8db: Store result
    g_dword_8ae204 = budget;

    // 0xebe8e0: Final override check
    if (g_dword_bf194c != 0) {
        g_dword_8ae204 = g_dword_bf194c;
    }
}
void sub_79a712(int enable) {} // 0x79a712 (XInputEnable)
// 0x00617b60
// Performs specific operations on sub-objects of the passed parameter.
// It calls two virtual functions at index 4 and index 8 respectively.
void sub_617b60(void* p) {
    uint8_t* pObj = (uint8_t*)p;
    if (!pObj) return;

    // 0x617b66: Get sub-object at offset 0x0c
    uint8_t* pSubObj = *(uint8_t**)(pObj + 0x0c);
    if (pSubObj) {
        void** vtable = *(void***)pSubObj;
        // 0x617b6e: Call virtual function at index 4 (offset 0x10)
        typedef void* (__thiscall *FuncPtr1)(void*);
        void* result = ((FuncPtr1)vtable[4])(pSubObj);
        
        if (result) {
            uint8_t* pRes = (uint8_t*)result;
            // 0x617b70: Get final object at offset 0x218 from result
            void* pFinalObj = *(void**)(pRes + 0x218);
            if (pFinalObj) {
                void** vtable2 = *(void***)pFinalObj;
                // 0x617b80: Call virtual function at index 8 (offset 0x20)
                typedef void (__stdcall *FuncPtr2)(void*);
                ((FuncPtr2)vtable2[8])(pFinalObj);
            }
        }
    }
}

// 0x0068da30
// Acquires input devices (keyboard and joysticks).
extern "C" bool sub_68da30() {
    // 0x68da30: Keyboard acquire
    if (g_dword_e6a070) {
        typedef HRESULT (__stdcall *AcquirePtr)(void*);
        void* device = g_dword_e6a070;
        void** vtable = *(void***)device;
        AcquirePtr Acquire = (AcquirePtr)vtable[7]; // 0x1c / 4 = 7
        
        if (Acquire(device) < 0) {
            sub_66f810((const char*)0x88825c); // "cKeyboard: Failed to acquire"
        }
    }

    // 0x68da52: Another keyboard/input device acquire
    if (g_dword_e6a194) {
        typedef HRESULT (__stdcall *AcquirePtr)(void*);
        void* device = g_dword_e6a194;
        void** vtable = *(void***)device;
        AcquirePtr Acquire = (AcquirePtr)vtable[7]; // 0x1c / 4 = 7
        
        if (Acquire(device) < 0) {
            sub_66f810((const char*)0x888330); // "cKeyboard: Failed to acquire (2)"
        }
    }

    // 0x68da76: Enable XInput
    sub_79a712(1);

    // 0x68da7d: Joystick acquire loop
    void** joystickPtrs[2] = { &g_dword_e6a42c, &g_dword_e6a674 };
    for (int i = 0; i < 2; i++) {
        void* device = *joystickPtrs[i];
        if (device) {
            typedef HRESULT (__stdcall *AcquirePtr)(void*);
            void** vtable = *(void***)device;
            AcquirePtr Acquire = (AcquirePtr)vtable[7]; // 0x1c / 4 = 7
            
            if (Acquire(device) < 0) {
                sub_66f810((const char*)0x88814c); // "cJoystick: Failed to acquire"
            }
        }
    }

    return true;
}

void sub_60c670(void* p1, void* p2, void* p3, void* p4) {} // 0x60c670 stub

// 0x0060d220
// Saves the current window position and state (maximized/minimized) to the registry
// before the application closes. This allows the game to restore the window
// to its previous position on the next run.
void sub_60d220(HWND hWnd) {
    WINDOWPLACEMENT wp;
    wp.length = sizeof(WINDOWPLACEMENT);
    
    // 0x60d23b: Get current window placement (0x7b73c0)
    if (!GetWindowPlacement(hWnd, &wp)) return;

    RECT rect;
    // 0x60d28b: Get current window rectangle (0x7b7408)
    GetWindowRect(hWnd, &rect);

    // 0x60d32b: Save coordinates to registry (Software\Electronic Arts\...)
    // It uses a series of calls to construct registry paths and write values.
    // The following is a simplified representation of the logic:
    // RegistrySetInt("GameSettings", "Width", rect.right - rect.left);
    // RegistrySetInt("GameSettings", "Height", rect.bottom - rect.top);
    // RegistrySetInt("GameSettings", "X", rect.left);
    // RegistrySetInt("GameSettings", "Y", rect.top);
    // RegistrySetInt("GameSettings", "WindowState", wp.showCmd);
}
void sub_617b90(WPARAM wParam, LPARAM lParam) {} // 0x617b90
void sub_586d00(int value) {} // 0x586d00
// 0x0079bcd0
// 64-bit unsigned multiplication: (low, high) * (mLow, mHigh)
uint64_t __stdcall sub_79bcd0(uint32_t low, uint32_t high, uint32_t mLow, uint32_t mHigh) {
    return (uint64_t)low * mLow + (((uint64_t)low * mHigh + (uint64_t)high * mLow) << 32);
}

// 0x0079eab0
// 64-bit signed division: (low, high) / (dLow, dHigh)
int64_t __stdcall sub_79eab0(int32_t low, int32_t high, int32_t dLow, int32_t dHigh) {
    int64_t dividend = ((int64_t)high << 32) | (uint32_t)low;
    int64_t divisor = ((int64_t)dHigh << 32) | (uint32_t)dLow;
    if (divisor == 0) return 0;
    return dividend / divisor;
}

// 0x00618010
// Initializes the timer period and returns elapsed time since first call.
uint32_t sub_618010() {
    TIMECAPS tc;
    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) == TIMERR_NOERROR) {
        uint32_t period = tc.wPeriodMin;
        if (period < 1) period = 1;
        timeBeginPeriod(period);
        uint32_t time = timeGetTime();
        timeEndPeriod(period);
        
        if (!g_byte_e6b388) {
            g_dword_e6e5e8 = time;
            g_byte_e6b388 = 1;
        }
        return time - g_dword_e6e5e8;
    }
    return 0;
}

bool sub_63d600(void* p) { return false; } // 0x63d600 stub

void sub_636830() {
    if (!g_dword_bef7c0) return;

    uint32_t startTime = sub_618010();
    
    while (true) {
        void* p = g_dword_bef7c0;
        if (!p) break;
        
        if (sub_63d600(p)) {
            // Logic to update g_dword_bef7c0 from p + 0x7c
            // For now, just break or handle as needed
            break;
        }
        
        uint32_t currentTime = timeGetTime();
        if (!g_byte_e6b388) {
            g_dword_e6e5e8 = currentTime;
            g_byte_e6b388 = 1;
        }
        uint32_t elapsed = currentTime - g_dword_e6e5e8;
        
        if (elapsed - startTime >= 2) break;
    }
}
void sub_617f50(void* p) {} // 0x617f50
void sub_617ee0(void* p1, void* p2) {} // 0x617ee0

// 0x00618140
// Frame timing and input polling.
bool sub_618140() {
    sub_636830();
    uint32_t elapsed = sub_618010();

    // 0x618159: shld $0x10, %eax, %edx; shl $0x10, %eax
    // This effectively multiplies the time by 2^16 (65536)
    uint64_t time64 = (uint64_t)elapsed << 16;
    uint32_t timeHigh = (uint32_t)(time64 >> 32);
    uint32_t timeLow = (uint32_t)time64;

    uint32_t lastTimeLow, lastTimeHigh;
    if (!(g_dword_e75234 & 1)) {
        g_dword_e75234 |= 1;
        g_dword_e6e5e0 = timeLow;
        g_dword_e6e5e4 = timeHigh;
        lastTimeLow = timeLow;
        lastTimeHigh = timeHigh;
    } else {
        lastTimeLow = g_dword_e6e5e0;
        lastTimeHigh = g_dword_e6e5e4;
    }

    uint64_t lastTime64 = ((uint64_t)lastTimeHigh << 32) | lastTimeLow;
    int64_t diff = (int64_t)(time64 - lastTime64);
    
    uint32_t diffLow, diffHigh;
    if (diff < 0) {
        diffLow = 0;
        diffHigh = 0;
    } else {
        if (diff > 0x640000) {
            diffLow = 0x640000;
            diffHigh = 0;
        } else {
            diffLow = (uint32_t)diff;
            diffHigh = (uint32_t)(diff >> 32);
        }
    }

    uint64_t currentTime = ((uint64_t)g_dword_c8319c << 32) | g_dword_c83198;
    currentTime += ((uint64_t)diffHigh << 32) | diffLow;
    g_dword_c83198 = (uint32_t)currentTime;
    g_dword_c8319c = (uint32_t)(currentTime >> 32);
    
    g_dword_e6e5e0 = timeLow;
    g_dword_e6e5e4 = timeHigh;

    // 0x6181ca: sub_79bcd0 (multiplication by 3?)
    // The assembly passes 3 as mLow and 0 as mHigh
    uint64_t scaledTime = sub_79bcd0(g_dword_c83198, g_dword_c8319c, 3, 0);
    // 0x6181d8: sub_79eab0 (division by 0x10000?)
    g_dword_c83110 = (uint32_t)sub_79eab0((uint32_t)scaledTime, (uint32_t)(scaledTime >> 32), 0x10000, 0);

    uint32_t pollTimeLow = g_dword_c831a8;
    uint32_t pollTimeHigh = g_dword_c831ac;

    if ((int32_t)pollTimeHigh > (int32_t)g_dword_c8319c || 
        (pollTimeHigh == g_dword_c8319c && pollTimeLow > g_dword_c83198)) {
        // 0x618203
        uint64_t step = ((uint64_t)g_dword_c83194 << 32) | g_dword_c83190;
        uint64_t nextPoll = ((uint64_t)pollTimeHigh << 32) | pollTimeLow;
        nextPoll += step;
        
        uint32_t idx = g_dword_8e1648 ^ 1;
        g_qword_c83170[idx] = nextPoll;
        g_dword_c831a8 = (uint32_t)nextPoll;
        g_dword_c831ac = (uint32_t)(nextPoll >> 32);
        g_dword_8e1648 = idx;

        uint64_t scaledPoll = sub_79bcd0(g_dword_c831a8, g_dword_c831ac, 3, 0);
        uint32_t val = (uint32_t)sub_79eab0((uint32_t)scaledPoll, (uint32_t)(scaledPoll >> 32), 0x10000, 0);
        
        sub_617f50(&val);
        
        if (g_dword_8e1644) {
            void** vtable = *(void***)g_dword_8e1644;
            typedef void (__stdcall *PollPtr)(void*, uint32_t*);
            PollPtr Poll = (PollPtr)vtable[0];
            Poll(g_dword_8e1644, &val);
        }
    }

    // 0x6182ab: Secondary timing check
    uint64_t limit = ((uint64_t)g_dword_c831a4 << 32) | g_dword_c831a0;
    uint64_t step2 = ((uint64_t)g_dword_c8318c << 32) | g_dword_c83188;
    limit += step2;

    if ((int64_t)limit <= (int64_t)time64) {
        uint32_t nextLimitLow = (uint32_t)limit;
        uint32_t nextLimitHigh = (uint32_t)(limit >> 32);
        
        uint32_t altLimitLow = g_qword_c83170[g_dword_8e1648 ^ 1];
        uint32_t altLimitHigh = g_qword_c83170[g_dword_8e1648 ^ 1] >> 32;

        if ((int32_t)nextLimitHigh > (int32_t)altLimitHigh || 
            (nextLimitHigh == altLimitHigh && nextLimitLow > altLimitLow)) {
            nextLimitLow = altLimitLow;
            nextLimitHigh = altLimitHigh;
        }

        g_dword_c831a0 = nextLimitLow;
        g_dword_c831a4 = nextLimitHigh;
        
        uint64_t scaledLimit = sub_79bcd0(nextLimitLow, nextLimitHigh, 3, 0);
        uint32_t val2 = (uint32_t)sub_79eab0((uint32_t)scaledLimit, (uint32_t)(scaledLimit >> 32), 0x10000, 0);
        g_dword_c8311c = val2;
        
        sub_617ee0(&g_dword_c83118, &val2);
        
        if (g_dword_8e1644) {
            void** vtable = *(void***)g_dword_8e1644;
            typedef void (__stdcall *PollPtr)(void*, uint32_t*);
            PollPtr Poll = (PollPtr)vtable[1];
            Poll(g_dword_8e1644, &val2);
        }
        return true;
    }

    return false;
}

// 0x0068dac0
// Unacquires input devices (keyboard and joysticks).
bool sub_68dac0() {
    // 0x68dac0: Keyboard unacquire
    if (g_dword_e6a070) {
        typedef HRESULT (__stdcall *UnacquirePtr)(void*);
        void* device = g_dword_e6a070;
        void** vtable = *(void***)device;
        UnacquirePtr Unacquire = (UnacquirePtr)vtable[8]; // 0x20 / 4 = 8
        
        if (Unacquire(device) < 0) {
            sub_66f810((const char*)0x888284); // "cKeyboard: Failed to unacquire"
        }
    }

    // 0x68dae2: Another keyboard/input device unacquire
    if (g_dword_e6a194) {
        typedef HRESULT (__stdcall *UnacquirePtr)(void*);
        void* device = g_dword_e6a194;
        void** vtable = *(void***)device;
        UnacquirePtr Unacquire = (UnacquirePtr)vtable[8]; // 0x20 / 4 = 8
        
        if (Unacquire(device) < 0) {
            sub_66f810((const char*)0x888284);
        }
    }

    // 0x68db08: Disable XInput
    sub_79a712(0); // 0x79a712 (XInputEnable)

    // 0x68db0d: Joystick unacquire loop
    void** joystickPtrs[2] = { &g_dword_e6a42c, &g_dword_e6a674 };
    for (int i = 0; i < 2; i++) {
        void* device = *joystickPtrs[i];
        if (device) {
            typedef HRESULT (__stdcall *UnacquirePtr)(void*);
            void** vtable = *(void***)device;
            UnacquirePtr Unacquire = (UnacquirePtr)vtable[8]; // 0x20 / 4 = 8
            
            if (Unacquire(device) < 0) {
                sub_66f810((const char*)0x88816c); // "cJoystick: Failed to unacquire"
            }
        }
    }

    return true;
}

// 0x0067d310
// Checks the cooperative level of the Direct3D device and handles device loss/reset.
bool sub_67d310() {
    if (g_dword_bf1920 == NULL) {
        return true;
    }

    sub_67d2e0(); // 0x67d2e0

    // Call TestCooperativeLevel (virtual function at offset 0x0c)
    typedef HRESULT (__stdcall *TestCooperativeLevelPtr)(void*);
    void* device = g_dword_bf1920;
    void** vtable = *(void***)device;
    TestCooperativeLevelPtr TestCooperativeLevel = (TestCooperativeLevelPtr)vtable[3]; // 0x0c / 4 = 3
    
    HRESULT hr = TestCooperativeLevel(device);

    if (hr >= 0) {
        // 0x67d449: Device is fine
        g_byte_bf18aa = 0;
        return true;
    }

    // 0x67d352: Device is lost or needs reset
    g_byte_bf18aa = 1;

    if (hr == (HRESULT)0x88760868) { // D3DERR_DEVICELOST
        // 0x67d362
        Sleep(0x32);
        return false;
    }

    if (hr == (HRESULT)0x88760869) { // D3DERR_DEVICENOTRESET
        // 0x67d37e
        sub_67cfb0(); // 0x67cfb0

        // Call Reset (virtual function at offset 0x40)
        typedef HRESULT (__stdcall *ResetPtr)(void*, void*);
        ResetPtr Reset = (ResetPtr)vtable[16]; // 0x40 / 4 = 16
        
        // The assembly passes a pointer to some parameters at 0xb94af8
        HRESULT resetHr = Reset(device, (void*)0xb94af8);

        if (resetHr >= 0) {
            sub_67d0c0(); // 0x67d0c0
        } else {
            // 0x67d3a3: Handle reset failure
            if (resetHr == (HRESULT)0x88760868) { // D3DERR_DEVICELOST
                Sleep(0x32);
            } else if (resetHr == (HRESULT)0x88760827) { // D3DERR_DRIVERINTERNALERROR
                sub_66f810((const char*)0x887afc);
            } else if (resetHr == (HRESULT)0x8876086c) { // D3DERR_DEVICEHUNG?
                sub_66f810((const char*)0x887b1c);
            } else if (resetHr == (HRESULT)0x8876017c) { // D3DERR_OUTOFVIDEOMEMORY
                sub_66f810((const char*)0x887b34);
            } else if (resetHr == (HRESULT)0x8007000e) { // E_OUTOFMEMORY
                sub_66f810((const char*)0x887b50);
            }
        }
        return false;
    }

    // 0x67d434: Other errors
    sub_66f810((const char*)0x887b68);
    return false;
}

// 0x0060dc10
// Main Message Loop and Game Update Loop
void sub_60dc10() {
    if (g_byte_bef6c5 != 0) { // 0x60dc1b
        g_byte_bef6c5 = 0; // 0x60de99
        return;
    }

    while (true) {
        // 0x60dc27: Device Reset Check
        sub_67d310(); // 0x67d310

        if (g_byte_8afbd9 == 0) { // 0x60dc2c
            if (g_byte_bef6c7 != 0) { // 0x60dc39
                 // 0x60dc42: Check global pointer and call virtual functions
                if (g_dword_e6b384) { // 0x60dc42
                    // Simplified: We assume stubs for now as we can't easily replicate virtual calls without class defs
                    // 0x60dc4c - 0x60dc66: Virtual function calls would go here
                }
                sub_68dac0(); // 0x60dc68

                // 0x60dc72: Ensure cursor is visible?
                while (ShowCursor(TRUE) <= 0); // 0x7b73c4
            }
        }
        
        // 0x60dd0c: PeekMessage Loop
        MSG msg;
        // PM_REMOVE (1) | PM_NOYIELD (2) = 3
        if (PeekMessageA(&msg, NULL, 0, 0, 3)) { // 0x7b73b4
            if (msg.message == WM_QUIT) { // 0x60dd24 (0x12)
                g_byte_bef6c5 = 0; // 0x60de87
                return;
            }
            if ((int)msg.message != -1) { // 0x60dd2f
                TranslateMessage(&msg); // 0x7b73c8
                DispatchMessageA(&msg); // 0x7b73e0
            }
            // Loop back to start (implicit in while(true)) - 0x60dd4e jmp 0x60de67 (logic simplified)
        } else {
             // 0x60dd53: Game Update
             uint64_t timeVal = ((uint64_t)g_dword_c8318c << 32) | g_dword_c83188;
             int64_t shiftedTime = sub_79ea80(timeVal, 0x10); // 0x79ea80
             
             // ... time calculations ...
             // 0x60dd68 - 0x60ddb6: FPU and time logic
             
             sub_618140(); // 0x618140
             
             // 0x60ddbf
             if (g_byte_bef6d4 == 0) { // NOTE: Disassembly says bef6d7 in cmp, but logic flow suggests similar checks
                 // 0x60ddc8
                 if ((g_dword_e74c20 & 1) == 0) {
                     g_dword_e74c20 |= 1; // 0x60ddd1
                     sub_612f00(); // 0x612f00
                     sub_6f53d7((void*)0x7b5640); // 0x6f53d7
                 }
                 
                 sub_616590(g_dword_bef6e4); // 0x616590
                 
                 // 0x60ddf5: comparisons
                 if (g_dword_bef6d8 >= g_dword_8afb08) { // 0x60de0c
                     // 0x60de1b
                     if (g_byte_bef6d4 == 0) {
                         g_dword_bef6d8 = 0; // 0x60de22
                     } else {
                         // 0x60de2a
                         if (g_dword_e6b2dc != NULL) {
                             void* temp = *(void**)((uint8_t*)g_dword_e6b2dc + 4);
                             if (temp != NULL) {
                                 void* obj = *(void**)temp;
                                 if (obj != NULL) {
                                     sub_6a9f20(obj);
                                 }
                             }
                         }
                     }
                     
                     if (g_byte_bef6d5 != 0) { // 0x60de41
                         sub_58b8a0(); // 0x58b8a0
                     }
                     
                     // 0x60de51: math
                 }
                 
                 // 0x60de60: Sleep if needed?
                 // 0x60de61 call 0x7b7174 -> Sleep(0) likely
                 Sleep(0); // 0x7b7174
             }
             
             // 0x60de67: Check exit condition
             if (g_byte_bef6c5 != 0) { // 0x60de67
                g_byte_bef6c5 = 0; // 0x60de76
                return;
             }
        }
    }
}
void sub_614330(int height) {} // 0x614330
void sub_60c150() {} // 0x60c150

// 0x0060deb0
// Disables or restores accessibility shortcuts (Sticky Keys, Toggle Keys, Filter Keys)
// to prevent them from interrupting the game experience by popping up.
void sub_60deb0(int restore) {
    if (restore) {
        // 0x60dec6: Restore original Sticky Keys settings.
        SystemParametersInfoA(SPI_SETSTICKYKEYS, sizeof(g_stickyKeys), &g_stickyKeys, 0); // 0x60ded1
        // 0x60ded3: Restore original Toggle Keys settings.
        SystemParametersInfoA(SPI_SETTOGGLEKEYS, sizeof(g_toggleKeys), &g_toggleKeys, 0); // 0x60dede
        // 0x60dee0: Restore original Filter Keys settings.
        SystemParametersInfoA(SPI_SETFILTERKEYS, sizeof(g_filterKeys), &g_filterKeys, 0); // 0x60deeb
    } else {
        // 0x60def2: Initialization - save and disable the shortcuts if not already handled.
        
        // Handle Sticky Keys.
        STICKYKEYS sk = g_stickyKeys;
        if (!(sk.dwFlags & 1)) { // SKF_STICKYKEYSON
            sk.dwFlags &= ~0x0C; // Disable SKF_HOTKEYACTIVE | SKF_CONFIRMHOTKEY
            SystemParametersInfoA(SPI_SETSTICKYKEYS, sizeof(sk), &sk, 0); // 0x60df1a
        }

        // Handle Toggle Keys.
        TOGGLEKEYS tk = g_toggleKeys;
        if (!(tk.dwFlags & 1)) { // TKF_TOGGLEKEYSON
            tk.dwFlags &= ~0x0C; // Disable TKF_HOTKEYACTIVE | TKF_CONFIRMHOTKEY
            SystemParametersInfoA(SPI_SETTOGGLEKEYS, sizeof(tk), &tk, 0); // 0x60df45
        }

        // Handle Filter Keys.
        FILTERKEYS fk = g_filterKeys;
        if (!(fk.dwFlags & 1)) { // FKF_FILTERKEYSON
            fk.dwFlags &= ~0x0C; // Disable FKF_HOTKEYACTIVE | FKF_CONFIRMHOTKEY
            SystemParametersInfoA(SPI_SETFILTERKEYS, sizeof(fk), &fk, 0); // 0x60df94
        }
    }
}


uintptr_t __security_cookie = 0xBB40E64E; // 0x896df0
uintptr_t __security_cookie_complement;   // 0x896df4
int g_init_flag = 0;                      // 0xe76050
int g_winmain_ret = 0;                    // 0x8da338

// Forward declarations
void __security_init_cookie(); // 0x6f5b76
void __tmainCRTStartup();      // 0x6f54d2

// 0x006f5793
// The actual entry point of the executable.
extern "C" void EntryPoint() {
    __security_init_cookie(); // 0x006f5b76
    __tmainCRTStartup();      // 0x006f54d2
}

// 0x006f5b76
// Initializes the global security cookie for stack protection.
void __security_init_cookie() {
    uintptr_t cookie;
    FILETIME system_time;
    LARGE_INTEGER performance_count;

    cookie = __security_cookie; // 0x896df0
    if (cookie != 0xBB40E64E && (cookie & 0xFFFF0000) != 0) {
        __security_cookie_complement = ~cookie; // 0x896df4
        return;
    }

    GetSystemTimeAsFileTime(&system_time); // 0x7b70b0
    cookie = system_time.dwLowDateTime ^ system_time.dwHighDateTime;
    cookie ^= GetCurrentProcessId(); // 0x7b7180
    cookie ^= GetCurrentThreadId(); // 0x7b7124
    cookie ^= GetTickCount(); // 0x7b70bc

    if (QueryPerformanceCounter(&performance_count)) { // 0x7b7120
        cookie ^= performance_count.LowPart ^ performance_count.HighPart;
    }

    if (cookie == 0xBB40E64E) {
        cookie = 0xBB40E64F;
    } else if ((cookie & 0xFFFF0000) == 0) {
        cookie |= (cookie << 16);
    }

    __security_cookie = cookie; // 0x896df0
    __security_cookie_complement = ~cookie; // 0x896df4
}

// 0x006f54d2
// The standard CRT startup function.
void __tmainCRTStartup() {
    STARTUPINFOA si;
    int showWindow;
    char* lpCmdLine;
    int in_quotes = 0;

    GetStartupInfoA(&si); // 0x7b7120

    if (g_init_flag == 0) {
        g_init_flag = 1; // 0xe76050
    }

    lpCmdLine = GetCommandLineA();

    while (*lpCmdLine > ' ' || (*lpCmdLine && in_quotes)) {
        if (*lpCmdLine == '"') {
            in_quotes = !in_quotes;
        }
        lpCmdLine++;
    }

    while (*lpCmdLine && *lpCmdLine <= ' ') {
        lpCmdLine++;
    }

    showWindow = (si.dwFlags & STARTF_USESHOWWINDOW) ? si.wShowWindow : SW_SHOWDEFAULT;

    g_winmain_ret = WinMain((HINSTANCE)0x400000, NULL, lpCmdLine, showWindow); // 0x60dfa0

    exit(g_winmain_ret); // 0x7b7260
}

// 0x0060d6d0
// Main window procedure.
LRESULT CALLBACK sub_60d6d0(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    if (Msg == WM_SYSCOMMAND) {
        WPARAM cmd = wParam & 0xFFF0;
        if (cmd == SC_MINIMIZE || cmd == SC_CLOSE || cmd == SC_SCREENSAVE || cmd == SC_MONITORPOWER) {
            return 0;
        }
    }

    if (Msg >= 2 && Msg <= 0x84) {
        // Jump table logic simplified to switch
        switch (Msg) {
            case WM_DESTROY: { // 0x60d8c0
                if (g_byte_8afbd9) {
                    while (ShowCursor(TRUE) <= 0);
                }
                PostQuitMessage(0);
                return 0;
            }
            case WM_ACTIVATE: { // 0x60d714
                if (g_byte_8afbd9 && g_dword_e6b384) {
                    if (LOWORD(wParam) == WA_INACTIVE) {
                        sub_617b60(g_dword_bef6d0);
                        sub_68dac0();
                    } else {
                        sub_68da30();
                    }
                }
                break;
            }
            case WM_SETFOCUS: { // 0x60d829
                if (!g_byte_bef6c7) {
                    while (ShowCursor(FALSE) > 0);
                }
                break;
            }
            case WM_PAINT: { // 0x60d8e9
                if (g_byte_8afbd9) {
                    ValidateRect(hWnd, NULL);
                } else {
                    PAINTSTRUCT ps;
                    BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                }
                return 0;
            }
            case WM_CLOSE: { // 0x60d89d
                if (!g_byte_8afbd9) {
                    sub_60d220(hWnd);
                }
                DestroyWindow(hWnd);
                return 0;
            }
            case WM_SETCURSOR: { // 0x60d70b
                return 0;
            }
        }
    }

    if (Msg == WM_SYSKEYDOWN || Msg == WM_SYSKEYUP) {
        sub_617b90(wParam, lParam);
        return 0;
    }

    if (Msg == WM_ACTIVATEAPP) {
        sub_586d00(wParam);
        return 0;
    }

    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

// 0x0060dfa0
// The main entry point for the application.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // 0x60dfaf: Initialize floating point control word.
    _control87(0x30000, 0x20000); // 0x60dfb9
    
    // 0x60dfc8: Get current accessibility settings to be restored later.
    SystemParametersInfoA(SPI_GETSTICKYKEYS, sizeof(g_stickyKeys), &g_stickyKeys, 0); // 0x60dfd3
    SystemParametersInfoA(SPI_GETTOGGLEKEYS, sizeof(g_toggleKeys), &g_toggleKeys, 0); // 0x60dfe0
    SystemParametersInfoA(SPI_GETFILTERKEYS, sizeof(g_filterKeys), &g_filterKeys, 0); // 0x60dfed

    // 0x60dff1: Subsystem initialization.
    sub_60deb0(0); // 0x60deb0

    // 0x60e00d: Copy command line to global buffers.
    strncpy(g_lpCmdLine1, lpCmdLine, 511); // 0x7b72e4
    strncpy(g_lpCmdLine2, lpCmdLine, 511);
    g_lpCmdLine2[511] = '\0';

    // 0x60e02e: Internal initialization.
    sub_617c60(); // 0x617c60

    // 0x60e042: Check if another instance of the game is already running.
    if (FindWindowA(NULL, "OrderOfThePhoenixMainWndClass")) { // 0x7b740c
        HWND existingWnd = GetForegroundWindow(); // 0x7b70e4
        SetForegroundWindow(existingWnd); // 0x7b7170
        return 0;
    }

    // 0x60e068: Perform some system checks.
    if (!sub_60da90(hInstance)) { // 0x60da90
        return 0;
    }

    // 0x60e089: Load game settings from the registry/INI.
    const char* appName = "Harry Potter and the Order of the Phoenix";
    const char* section = "GameSettings";
    
    g_width = sub_60ce60(section, "Width", appName, 640); // 0x60ce60
    g_height = sub_60ce60(section, "Height", appName, 480);
    g_bitDepth = sub_60ce60(section, "BitDepth", appName, 32);
    g_shadowLOD = sub_60ce60(section, "ShadowLOD", appName, 0);
    g_maxFarClip = sub_60ce60(section, "MaxFarClip", appName, 0);
    g_particleRate = sub_60ce60(section, "ParticleRate", appName, 0);
    g_particleCullDistance = sub_60ce60(section, "ParticleCullDistance", appName, 0);
    g_cullDistance = sub_60ce60(section, "CullDistance", appName, 0);
    g_disableFog = sub_60ce60(section, "DisableFog", appName, 0);
    g_disablePostPro = sub_60ce60(section, "DisablePostPro", appName, 0);
    g_filterFlip = sub_60ce60(section, "FilterFlip", appName, 0);
    g_aaMode = sub_60ce60(section, "AAMode", appName, 0);
    g_useAdditionalModes = sub_60ce60(section, "UseAdditionalModes", appName, 0);

    // 0x60ed96: Initialize the main application object.
    g_hWnd = (HWND)sub_60db20(NULL, hInstance, lpCmdLine, nShowCmd); // 0x60db20
    if (!g_hWnd) {
        return 0;
    }

    // 0x60edb1: Get client area size and adjust window.
    RECT rect;
    GetClientRect(g_hWnd, &rect); // 0x7b741c
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // 0x60ee04: Further initialization.
    sub_614330(height); // 0x614330
    
    // 0x60ee14: Main game setup.
    sub_60c150(); // 0x60c150

    // 0x60ee3a: Show the window.
    ShowWindow(g_hWnd, nShowCmd); // 0x7b73a8

    // 0x60f004: Update window.
    UpdateWindow(g_hWnd); // 0x7b7404

    // 0x60f011: Enter message loop.
    sub_60dc10(); // 0x60dc10

    // 0x60f01d: Post-loop cleanup.
    sub_6a8f90(); // 0x6a8f90

    // 0x60f082: Exit sequence.
    while (ShowCursor(TRUE) <= 0); // 0x7b73c4
    
    // 0x60f098: Cleanup and exit.
    sub_60deb0(1); // 0x60deb0
    
    if (IsWindow(g_hWnd)) { // 0x7b73d4
        DestroyWindow(g_hWnd); // 0x7b7420
    }

    return 0; 
}