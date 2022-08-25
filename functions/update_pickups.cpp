void update_pickups()
{
	CReplayInterfacePickup = RPM<uintptr_t>(ReplayInterfacePointer, { 0x20 });
	CPickupList = RPM<uintptr_t>(CReplayInterfacePickup + 0x100);
	CPickupMaxCount = RPM<int>(CReplayInterfacePickup + 0x108);
	CPickupCurrentCount = RPM<int>(CReplayInterfacePickup + 0x110);
	pickups.clear();
	for (size_t i = 0, j = 0; i < CPickupMaxCount; i++)
	{
		if (j == CPickupCurrentCount) break;
		Pickup pickup;
		pickup.instance = RPM<uintptr_t>(CPickupList + i * 0x10);
		if (pickup.instance == 0) continue;
		pickup.world_coordinates = RPM<Vector3>(pickup.instance + 0x90);
		pickup.is_world_to_screen_success = WorldToScreen(pickup.world_coordinates, pickup.image_coordinates, matrix, window_width, window_height);
		if (pickup.is_world_to_screen_success)
		{
			pickup.world_head_coordinates = pickup.world_coordinates;
			pickup.world_head_coordinates.z += 0.5;
			WorldToScreen(pickup.world_head_coordinates, pickup.image_head_coordinates, matrix, window_width, window_height);
			uintptr_t base_model_info = RPM<uintptr_t>(pickup.instance + 0x20);
			pickup.hash = RPM<uint32_t>(base_model_info + 0x18);
		}
		pickups.push_back(pickup);
	}
}