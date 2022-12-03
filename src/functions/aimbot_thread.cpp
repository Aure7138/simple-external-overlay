#include "../common.hpp"

void aimbot_thread()
{
	while(g_running)
	{
		if (g_settings->weapon.aimbot && GetKeyState(VK_RBUTTON) < 0)
		{
			uintptr_t self_ped = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
			Vector3 self_pos = RPM<Vector3>(self_ped + 0x90);
			float matrix[16];
			ReadProcessMemory(g_handle, LPCVOID(RPM<uintptr_t>(CViewportGamePointer) + 0x250), matrix, 16 * 4, 0);
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
				if (g_settings->weapon.aimbot_player_only && RPM<uintptr_t>(v + 0x10A8) == 0)
					continue;
				Vector3 pos = RPM<Vector3>(v + 0x90);
				Vector3 screen;
				if (WorldToScreen(pos, screen, matrix, game_window_width, game_window_height))
				{
					//if (screen.x > game_window_width * 3 / 8 && screen.x < game_window_width * 6 / 8)
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
				get_instace_model_matrix(target_ped, model_matrix);
				Vector3 pos = RPM<Vector3>(target_ped + 0x410);
				Vector3 bone_head_pos;
				model_to_world(pos, bone_head_pos, model_matrix);

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