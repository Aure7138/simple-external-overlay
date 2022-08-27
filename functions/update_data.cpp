void update_data()
{
	//camFollowPedCamera = RPM<uintptr_t>(camGameplayDirectorPointer, { 0x2C8 });
	local_cped = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
	window_width = RPM<int>(WindowWidth);
	window_height = RPM<int>(WindowWidth + 4);
	CViewportGame = RPM<uintptr_t>(CViewportGamePointer);
	ReadProcessMemory(handle, LPCVOID(CViewportGame + 0x250), matrix, 4 * 16, 0);
}