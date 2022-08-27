void aimbot_thread()
{
	while(true)
	{
		if (aimbot_thread_globals.enable_aimbot && GetKeyState(VK_RBUTTON) < 0)
		{
			uintptr_t self_ped = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
			Vector3 self_pos = RPM<Vector3>(self_ped + 0x90);
			float matrix_[16];
			ReadProcessMemory(handle, LPCVOID(RPM<uintptr_t>(CViewportGamePointer) + 0x250), matrix_, 16 * 4, 0);
			int game_window_width = RPM<int>(WindowWidth);
			int game_window_height = RPM<int>(WindowWidth + 0x4);
			
			uintptr_t p = RPM<uintptr_t>(ReplayInterfacePointer, { 0x18 });
			uintptr_t list = RPM<uintptr_t>(p + 0x100);
			int max_count = RPM<int>(p + 0x108);
			int current_count = RPM<int>(p + 0x110);
			float min_dist = -1.0;
			uintptr_t target_ped = 0;
			for (size_t i = 0, j = 0; i < max_count; i++)
			{
				if (j == current_count) break;
				uintptr_t v = RPM<uintptr_t>(list + i * 0x10);
				if (v == 0)
					continue;
				j++;
				if (v == self_ped)
					continue;
				if (RPM<float>(v + 0x280) < 100.0f)
					continue;
				if (aimbot_thread_globals.exclude_player && RPM<uintptr_t>(v + 0x10C8) != 0)
					continue;
				Vector3 pos = RPM<Vector3>(v + 0x90);
				Vector3 screen;
				if (WorldToScreen(pos, screen, matrix_, game_window_width, game_window_height))
				{
					if (screen.x > game_window_width * 3 / 8 && screen.x < game_window_width * 6 / 8)
					{
						float dist = self_pos.Distance(pos);
						if (min_dist == -1.0) min_dist = dist, target_ped = v;
						if (min_dist > dist) min_dist = dist, target_ped = v;
					}
				}
			}
			if (target_ped != 0)
			{
				float model_matrix[16];
				ReadProcessMemory(handle, LPCVOID(target_ped + 0x60), model_matrix, 16 * 4, 0);
				Vector3 pos = RPM<Vector3>(target_ped + 0x430);
				Vector3 bone_head_pos;
				bone_head_pos.x = pos.x * model_matrix[0] + pos.y * model_matrix[4] + pos.z * model_matrix[8] + model_matrix[12];
				bone_head_pos.y = pos.x * model_matrix[1] + pos.y * model_matrix[5] + pos.z * model_matrix[9] + model_matrix[13];
				bone_head_pos.z = pos.x * model_matrix[2] + pos.y * model_matrix[6] + pos.z * model_matrix[10] + model_matrix[14];

				uintptr_t camGameplayDirector = RPM<uintptr_t>(camGameplayDirectorPointer);
				uintptr_t camFollowPedCamera = RPM<uintptr_t>(camGameplayDirector + 0x2C8);
				Vector3 camera_pos = RPM<Vector3>(camFollowPedCamera + 0x60);
				uintptr_t camFollowPedCameraMetadata = RPM<uintptr_t>(camFollowPedCamera + 0x10);
				bool is_first_person = RPM<float>(camFollowPedCameraMetadata + 0x30) == 0.0f;

				float dist = camera_pos.Distance(bone_head_pos);
				Vector3 angle;
				angle.x = (bone_head_pos.x - camera_pos.x) / dist;
				angle.y = (bone_head_pos.y - camera_pos.y) / dist;
				angle.z = (bone_head_pos.z - camera_pos.z) / dist;
				if (is_first_person)
					WPM<Vector3>(camFollowPedCamera + 0x40, angle);
				else
					WPM<Vector3>(camFollowPedCamera + 0x3D0, angle);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}