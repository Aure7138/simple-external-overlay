void update_automobiles()
{
	CReplayInterfaceVeh = RPM<uintptr_t>(ReplayInterfacePointer, { 0x10 });
	CAutombileList = RPM<uintptr_t>(CReplayInterfaceVeh + 0x180);
	CAutombileMaxCount = RPM<int>(CReplayInterfaceVeh + 0x188);
	CAutombileCurrentCount = RPM<int>(CReplayInterfaceVeh + 0x190);
	automobiles.clear();
	for (size_t i = 0, j = 0; i < CAutombileMaxCount; i++)
	{
		if (j == CAutombileCurrentCount) break;
		Automobile automobile;
		automobile.instance = RPM<uintptr_t>(CAutombileList + i * 0x10);
		if (automobile.instance == 0) continue;
		automobile.world_coordinates = RPM<Vector3>(automobile.instance + 0x90);
		automobile.is_world_to_screen_success = WorldToScreen(automobile.world_coordinates, automobile.image_coordinates, matrix, window_width, window_height);
		if (automobile.is_world_to_screen_success)
		{
			automobile.world_head_coordinates = automobile.world_coordinates;
			automobile.world_head_coordinates.z += 1;
			WorldToScreen(automobile.world_head_coordinates, automobile.image_head_coordinates, matrix, window_width, window_height);
			uintptr_t base_model_info = RPM<uintptr_t>(automobile.instance + 0x20);
			automobile.hash = RPM<uint32_t>(base_model_info + 0x18);
			ReadProcessMemory(handle, LPCVOID(base_model_info + 0x298), automobile.name1, 20, 0);
			ReadProcessMemory(handle, LPCVOID(base_model_info + 0x2A4), automobile.name2, 20, 0);
		}
		automobiles.push_back(automobile);
	}
}