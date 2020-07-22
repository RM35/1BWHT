#ifndef fast_runHEADER
#define fast_runHEADER

#include <windows.h>

class fast_run
{
public:
	INPUT kb_input;
	fast_run();
	bool toggle(bool fast_run_state);
	void do_fast_run_macro(int delay, float speed_cap);
	void do_test(int delay);
};

#endif