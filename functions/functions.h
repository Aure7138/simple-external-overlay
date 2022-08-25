#pragma once
uintptr_t Signature(const char* pattern, const char* mask);
template<typename T> T RPM(uintptr_t address, std::vector<int64_t> offsets = {})
{
	for (auto& offset : offsets)
	{
		ReadProcessMemory(handle, (LPCVOID)address, &address, sizeof(address), 0);
		address += offset;
	}
	T value;
	ReadProcessMemory(handle, (LPCVOID)address, &value, sizeof(value), 0);
	return value;
}
bool WorldToScreen(vec3_t pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);
bool WorldToScreen(vec3_t pos, vec3_t& screen, float matrix[16], int windowWidth, int windowHeight);
void update_data();
void update_automobiles();
void update_peds();
void update_pickups();
void update_objects();
void update_players();