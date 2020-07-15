#ifndef aimbotHEADER
#define aimbotHEADER

#include <windows.h>
#include <vector>

class aimbot
{
public:
    struct Vector3
    {
        float x, y, z;
        //float pitch,yaw,roll
    };

    struct centity
    {
    char pad_0000[24];     //0x0000
    Vector3 cur_coords;    //0x0018 
    char pad_0024[24];     //0x0024
    Vector3 cur_view_angs; //0x003C 
    char pad_0048[36];     //0x0048
    int32_t sound_loop;    //0x006C
    char pad_0070[8];      //0x0070
    int32_t client_no;     //0x0078 
    char pad_007C[76];     //0x007C
    int32_t cur_wep;       //0x00C8 
    int32_t leg_anim;      //0x00CC
    char pad_00D0[4];      //0x00D0
    float lean_offset;     //0x00D4 
    char pad_00D8[288];    //0x00D8
    Vector3 coords;        //0x01F8 
    Vector3 view_angs;     //0x0204 
    char pad_0210[24];     //0x0210
    };                     //Size: 0x0228 

    centity centities[64];
	intptr_t entity_list = 0x30211940;

	aimbot();
    bool toggle(bool aimbot_state);
	void update_values(HANDLE hProcess);

};

#endif