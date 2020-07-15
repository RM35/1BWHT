#ifndef fpsbypassHEADER
#define fpdbypassHEADER

#include <windows.h>

class fps_bypass
{
public:
    intptr_t frame_delay_addr = 0x0249BC88;

    fps_bypass();
    int change_state(int fps_bypass_state);
    void set_frame_delay(HANDLE hProcess, int frame_delay_ms);
};

#endif