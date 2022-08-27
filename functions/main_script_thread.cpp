void main_script_thread()
{
	while (true) {
		if (main_script_thread_globals.no_recoil)
		{
			uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
			if (CPed)
			{
				uintptr_t CPedWeaponManager = RPM<uintptr_t>(CPed + 0x10D8);
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
		if (main_script_thread_globals.no_spread)
		{
			uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
			if (CPed)
			{
				uintptr_t CPedWeaponManager = RPM<uintptr_t>(CPed + 0x10D8);
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
		{
			static bool state = false;
			if (main_script_thread_globals.one_shoot_kill)
			{
				uintptr_t CPed = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
				if (CPed)
				{
					uintptr_t CPlayerInfo = RPM<uintptr_t>(CPed + 0x10C8);
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
					uintptr_t CPlayerInfo = RPM<uintptr_t>(CPed + 0x10C8);
					if (CPlayerInfo)
					{
						WPM<float>(CPlayerInfo + 0xD0C, 1);
						WPM<float>(CPlayerInfo + 0xD18, 1);
						state = false;
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}