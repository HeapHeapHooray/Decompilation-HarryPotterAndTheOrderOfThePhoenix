#include <windows.h>
#include <stdlib.h>

// Forward declarations
void __security_init_cookie(); // 0x6f5b76
void __tmainCRTStartup();      // 0x6f54d2
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd); // 0x60dfa0
void __cdecl exit(int status); // 0x6f5901 (implied)

// Global variables (inferred from assembly)
extern uintptr_t __security_cookie; // 0x896df0 (approximate name)
extern uintptr_t __security_cookie_complement; // Related to 0xbb40e64e?

// 0x006f5793
// The actual entry point of the executable.
extern "C" void EntryPoint();

// 0x006f5b76
// Initializes the global security cookie for stack protection.
void __security_init_cookie();

// 0x006f54d2
// The standard CRT startup function (likely __tmainCRTStartup).
void __tmainCRTStartup();
}
