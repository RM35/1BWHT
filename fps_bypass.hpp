#ifndef fpsbypassHEADER
#define fpdbypassHEADER

#include <windows.h>

class fps_bypass
{
public:
    
    BYTE fps_bypass_opcodes[5] = { 0xB8, 0x4C, 0x1D, 0xAE, 0x00 };
    BYTE original_opcodes[5] = { 0xE8, 0x68, 0x9F, 0xFD, 0xFF };

    intptr_t bypass_addr = 0x0043A4CF;

    fps_bypass();
    int change_state(int fps_bypass_state);
    void set_fps_bypassed(HANDLE hProcess, int fps);
};

#endif