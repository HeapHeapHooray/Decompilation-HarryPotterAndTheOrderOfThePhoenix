#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>
#include <string>
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

STICKYKEYS g_stickyKeys; // 0x8afc44
TOGGLEKEYS g_toggleKeys; // 0x8afc4c
FILTERKEYS g_filterKeys; // 0x8afc54

// Forward declaration for Window Procedure
LRESULT CALLBACK sub_60d6d0(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // 0x60d6d0

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

int sub_60db20(void* this_ptr, HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd) { return 1; } // 0x60db20
void sub_617bf0(const char* cmdLine, const char* key, int* outValue) {} // 0x617bf0
// Stubs for functions called by sub_60dc10
void sub_67d310() {} // 0x67d310
void sub_68dac0() {} // 0x68dac0
void sub_618140() {} // 0x618140
void sub_79ea80(char c) {} // 0x79ea80
void sub_612f00() {} // 0x612f00
void sub_6f53d7(void* p) {} // 0x6f53d7
void sub_616590(void* p) {} // 0x616590
void sub_6a9f20() {} // 0x6a9f20
void sub_58b8a0() {} // 0x58b8a0
void sub_66f810(void* p) {} // 0x66f810
void sub_6a8f90() {} // 0x6a8f90

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
             sub_79ea80(0x10); // 0x79ea80
             
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
                         if (g_dword_e6b2dc && *((DWORD*)((char*)g_dword_e6b2dc + 4)) == 0 && *((DWORD*)g_dword_e6b2dc) == 0) {
                              sub_6a9f20(); // 0x6a9f20
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

// Stub for Window Procedure
LRESULT CALLBACK sub_60d6d0(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

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