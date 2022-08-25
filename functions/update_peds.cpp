void update_peds()
{
	CReplayInterfacePed = RPM<uintptr_t>(ReplayInterfacePointer, { 0x18 });
	CPedList = RPM<uintptr_t>(CReplayInterfacePed + 0x100);
	CPedMaxCount = RPM<int>(CReplayInterfacePed + 0x108);
	CPedCurrentCount = RPM<int>(CReplayInterfacePed + 0x110);
	peds.clear();
	for (size_t i = 0, j = 0; i < CPedMaxCount; i++)
	{
		if (j == CPedCurrentCount) break;
		Ped ped;
		ped.instance = RPM<uintptr_t>(CPedList + i * 0x10);
		if (ped.instance == 0) continue;
		ped.world_coordinates = RPM<Vector3>(ped.instance + 0x90);
		ped.is_world_to_screen_success = WorldToScreen(ped.world_coordinates, ped.image_coordinates, matrix, window_width, window_height);
		if (ped.is_world_to_screen_success)
		{
			ReadProcessMemory(handle, LPCVOID(ped.instance + 0x60), ped.model_matrix, 4 * 16, 0);
			for (size_t k = 0; k < 9; k++)
			{
				ped.bones_model_coordinates[k] = RPM<Vector3>(ped.instance + 0x430 + k * 0x10);
				ped.bones_world_coordinates[k].x = ped.bones_model_coordinates[k].x * ped.model_matrix[0] + ped.bones_model_coordinates[k].y * ped.model_matrix[4] + ped.bones_model_coordinates[k].z * ped.model_matrix[8] + ped.model_matrix[12];
				ped.bones_world_coordinates[k].y = ped.bones_model_coordinates[k].x * ped.model_matrix[1] + ped.bones_model_coordinates[k].y * ped.model_matrix[5] + ped.bones_model_coordinates[k].z * ped.model_matrix[9] + ped.model_matrix[13];
				ped.bones_world_coordinates[k].z = ped.bones_model_coordinates[k].x * ped.model_matrix[2] + ped.bones_model_coordinates[k].y * ped.model_matrix[6] + ped.bones_model_coordinates[k].z * ped.model_matrix[10] + ped.model_matrix[14];
				WorldToScreen(ped.bones_world_coordinates[k], ped.bones_image_coordinates[k], matrix, window_width, window_height);
			}
			ped.world_head_coordinates = ped.world_coordinates;
			ped.world_head_coordinates.z += 1;
			WorldToScreen(ped.world_head_coordinates, ped.image_head_coordinates, matrix, window_width, window_height);

			ped.health = RPM<float>(ped.instance + 0x280);
			ped.ped_type = RPM<uint32_t>(ped.instance + 0x10B8);
			ped.ped_type = ped.ped_type << 11 >> 25;
			uintptr_t base_model_info = RPM<uintptr_t>(ped.instance + 0x20);
			ped.hash = RPM<uint32_t>(base_model_info + 0x18);
		}
		peds.push_back(ped);
	}
}