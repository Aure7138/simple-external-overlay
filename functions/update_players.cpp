void update_players()
{
	uintptr_t pointer = RPM<uintptr_t>(CNetworkPlayerMgrPointer);
	players.clear();
	for (size_t i = 0; i < 32; i++)
	{
		uintptr_t CNetGamePlayer = RPM<uintptr_t>(pointer + 0x180 + i * 8);
		if (CNetGamePlayer == 0) continue;
		Player player;
		uintptr_t CPlayerInfo = RPM<uintptr_t>(CNetGamePlayer + 0xA0);
		uintptr_t CPed = RPM<uintptr_t>(CPlayerInfo + 0x1E8);
		player.instance = CPed;
		player.world_coordinates = RPM<Vector3>(player.instance + 0x90);
		player.is_world_to_screen_success = WorldToScreen(player.world_coordinates, player.image_coordinates, matrix, window_width, window_height);
		if (player.is_world_to_screen_success)
		{
			player.world_head_coordinates = player.world_coordinates;
			player.world_head_coordinates.z += 1;
			WorldToScreen(player.world_head_coordinates, player.image_head_coordinates, matrix, window_width, window_height);
			uintptr_t base_model_info = RPM<uintptr_t>(player.instance + 0x20);
			player.hash = RPM<uint32_t>(base_model_info + 0x18);
			player.id = i;
		}
		players.push_back(player);
	}
}