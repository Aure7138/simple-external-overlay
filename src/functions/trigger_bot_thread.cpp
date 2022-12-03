#include "../common.hpp"

void trigger_bot_thread()
{
	while (g_running)
	{
		static bool state = false;
		if (g_settings->weapon.trigger_bot && FindWindowA("grcWindow", 0) == GetForegroundWindow())
		{
			uintptr_t CPed = RPM<uintptr_t>(AimCPedPointer);
			if (CPed != 0 && RPM<float>(CPed + 0x280) >= 100.0f)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // Press
				state = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		if (state)
		{
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); // Release
			state = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}