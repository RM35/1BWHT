#ifndef aimbotHEADER
#define aimbotHEADER

#include <windows.h>
#include <vector>
#include "utils.hpp"

class aimbot
{
public:
    const float  PI_F = 3.14159265358979f;

    struct client_info_t
    {
    public:
        int32_t valid_info;   //0x0000
        char pad_0004[4];     //0x0004
        int32_t client_no;    //0x0008
        char name[32][1];     //0x000C
        int32_t team;         //0x002C
        int32_t team2;        //0x0030
        int32_t score;        //0x0034
        char pad_0038[1084];  //0x0038
        int32_t stance;       //0x0474
        char pad_0478[28];    //0x0478
        int32_t scoping;      //0x0494
        char pad_0498[20];    //0x0498
        int32_t wep;          //0x04AC
    };                        //Size: 0x04B0

    struct cg_t
    {
        int32_t client_frame;       //0x0000
        int32_t client_no;          //0x0004
        char pad_0008[160832];      //0x0008
        Vector3 ref_coords;         //0x27448
        Vector3 ref_angles;         //0x27454
        char pad_27460[13108];      //0x27460
        int32_t crosshair_client_no;//0x2A794
        int32_t crosshair_time;     //0x2A798
    } cg_t;                         //Size: 0x2A79C


    struct centity
    {
        char pad_0000[24];     //0x0000
        Vector3 cur_coords;    //0x0018 
        char pad_0024[24];     //0x0024
        Vector3 cur_view_angs; //0x003C 
        char pad_0048[36];     //0x0048
        int32_t sound_loop;    //0x006C
        char pad_0070[32];     //0x0070
        int32_t client_no;     //0x0078 
        char pad_007C[52];     //0x007C
        int32_t cur_wep;       //0x00C8 
        int32_t leg_anim;      //0x00CC
        char pad_00D0[4];      //0x00D0
        float lean_offset;     //0x00D4 
        char pad_00D8[288];    //0x00D8
        Vector3 coords;        //0x01F8 
        Vector3 view_angs;     //0x0204 
        char pad_0210[24];     //0x0210
    };                         //Size: 0x0228 

    struct 
    client_info_t c_info_t[64];
    centity centities[64];
	uintptr_t entity_list = 0x30211940;
    uintptr_t cgt_addr = 0x301E5f00;
    uintptr_t x_angle = 0x01493BE4;
    uintptr_t y_angle = 0x01493BE0;

    Vector3 origin = { 0, 0, 108};

	aimbot();
    bool toggle(bool aimbot_state);
	void update_values(HANDLE hProcess);
    void print_player_client_no();
    Vector3 calc_angles(Vector3 player, Vector3 enemy);
    void do_aim(Vector3 enemy, HANDLE hProcess);
    Vector3 get_local_coords();
    Vector3 get_local_angles();
    int closest_enemy();
    void aim_lerp(Vector3 enemy, HANDLE hProcess, int divisions);
};

#endif