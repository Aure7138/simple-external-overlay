#include "../common.hpp"

void main_thread()
{
	while (g_running) {
		if (!FindWindowA("grcWindow", nullptr)) g_running = false;
		weapon_no_recoil();
		weapon_no_spread();
		weapon_one_shoot_kill();
		self_never_wanted();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void weapon_no_recoil()
{
	if (!g_settings->weapon.no_recoil) return;
	uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
	if (CPed)
	{
		uintptr_t CPedWeaponManager = RPM<uintptr_t>(CPed + 0x10B8);
		if (CPedWeaponManager)
		{
			uintptr_t CWeaponInfo = RPM<uintptr_t>(CPedWeaponManager + 0x20);
			if (CWeaponInfo)
			{
				WPM<int>(CWeaponInfo + 0x2E4, 0);
				WPM<int>(CWeaponInfo + 0x2E8, 0);
			}
		}
	}
}

void weapon_no_spread()
{
	if (!g_settings->weapon.no_spread) return;
	uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
	if (CPed)
	{
		uintptr_t CPedWeaponManager = RPM<uintptr_t>(CPed + 0x10B8);
		if (CPedWeaponManager)
		{
			uintptr_t CWeaponInfo = RPM<uintptr_t>(CPedWeaponManager + 0x20);
			if (CWeaponInfo)
			{
				WPM<int>(CWeaponInfo + 0x74, 0);
			}
		}
	}
}

void weapon_one_shoot_kill()
{
	static bool state = false;
	if (g_settings->weapon.one_shoot_kill)
	{
		uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
		if (CPed)
		{
			uintptr_t CPlayerInfo = RPM<uintptr_t>(CPed + 0x10A8);
			if (CPlayerInfo)
			{
				WPM<float>(CPlayerInfo + 0xD0C, 999999);
				WPM<float>(CPlayerInfo + 0xD18, 999999);
				state = true;
			}
		}
	}
	else if (state == true)
	{
		uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
		if (CPed)
		{
			uintptr_t CPlayerInfo = RPM<uintptr_t>(CPed + 0x10A8);
			if (CPlayerInfo)
			{
				WPM<float>(CPlayerInfo + 0xD0C, 1);
				WPM<float>(CPlayerInfo + 0xD18, 1);
				state = false;
			}
		}
	}
}

void self_never_wanted()
{
	if (!g_settings->self.never_wanted) return;
	uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
	if (CPed)
	{
		uintptr_t CPlayerInfo = RPM<uintptr_t>(CPed + 0x10A8);
		WPM<int>(CPlayerInfo + 0x888, 0);
	}
}