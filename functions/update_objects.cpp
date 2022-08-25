void update_objects()
{
	CReplayInterfaceObject = RPM<uintptr_t>(ReplayInterfacePointer, { 0x28 });
	CObjectList = RPM<uintptr_t>(CReplayInterfaceObject + 0x158);
	CObjectMaxCount = RPM<int>(CReplayInterfaceObject + 0x160);
	CObjectCurrentCount = RPM<int>(CReplayInterfaceObject + 0x168);
	objects.clear();
	for (size_t i = 0, j = 0; i < CObjectMaxCount; i++)
	{
		if (j == CObjectCurrentCount) break;
		Object object;
		object.instance = RPM<uintptr_t>(CObjectList + i * 0x10);
		if (object.instance == 0) continue;
		object.world_coordinates = RPM<Vector3>(object.instance + 0x90);
		object.is_world_to_screen_success = WorldToScreen(object.world_coordinates, object.image_coordinates, matrix, window_width, window_height);
		if (object.is_world_to_screen_success)
		{
			object.world_head_coordinates = object.world_coordinates;
			object.world_head_coordinates.z += 0.5;
			WorldToScreen(object.world_head_coordinates, object.image_head_coordinates, matrix, window_width, window_height);
			uintptr_t base_model_info = RPM<uintptr_t>(object.instance + 0x20);
			object.hash = RPM<uint32_t>(base_model_info + 0x18);
		}
		objects.push_back(object);
	}
}