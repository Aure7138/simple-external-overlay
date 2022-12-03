#pragma once
#include "../common.hpp"
#include "../types.hpp"

// row major
inline bool WorldToScreen(vec3_t pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
    //Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
    vec4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
    clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
    clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
    clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

    if (clipCoords.w < 0.1f)
        return false;

    //perspective division, dividing by clip.W = Normalized Device Coordinates
    vec3_t NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
    return true;
}
// column major
inline bool WorldToScreen(vec3_t pos, vec3_t& screen, float matrix[16], int windowWidth, int windowHeight)
{
    //Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
    vec4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clipCoords.w < 0.1f)
        return false;

    //perspective division, dividing by clip.W = Normalized Device Coordinates
    vec3_t NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    //Transform to window coordinates
    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
    return true;
}

inline void model_to_world(vec3_t model_coords, vec3_t& world_coords, float model_matrix[16])
{
    world_coords.x = model_coords.x * model_matrix[0] + model_coords.y * model_matrix[4] + model_coords.z * model_matrix[8] + model_matrix[12];
    world_coords.y = model_coords.x * model_matrix[1] + model_coords.y * model_matrix[5] + model_coords.z * model_matrix[9] + model_matrix[13];
    world_coords.z = model_coords.x * model_matrix[2] + model_coords.y * model_matrix[6] + model_coords.z * model_matrix[10] + model_matrix[14];
}

template<typename T> T RPM(uintptr_t address, std::vector<int64_t> offsets = {})
{
    for (auto& offset : offsets)
    {
        ReadProcessMemory(g_handle, (LPCVOID)address, &address, sizeof(address), 0);
        address += offset;
    }
    T value;
    ReadProcessMemory(g_handle, (LPCVOID)address, &value, sizeof(value), 0);
    return value;
}

template<typename T> void WPM(uintptr_t address, T value, std::vector<int64_t> offsets = {})
{
    for (auto& offset : offsets)
    {
        ReadProcessMemory(g_handle, (LPCVOID)address, &address, sizeof(address), 0);
        address += offset;
    }
    WriteProcessMemory(g_handle, (LPVOID)address, &value, sizeof(value), 0);
}

inline uintptr_t get_self_ped() { return RPM<uintptr_t>(CPedFactoryPointer, { 0x8 }); }

inline void get_instance_world_coords(uintptr_t instance, Vector3& world_coords) { world_coords = RPM<Vector3>(instance + 0x30, { 0x50 }); }

inline Vector3 get_instance_world_coords(uintptr_t instance) { return RPM<Vector3>(instance + 0x30, { 0x50 }); }

inline uint32_t get_instance_hash(uintptr_t instance) { return RPM<uint32_t>(instance + 0x20, { 0x18 }); }

inline void get_vehicle_name_1(uintptr_t instance, char(&name_1)[20]) { ReadProcessMemory(g_handle, (LPCVOID)(RPM<uintptr_t>(instance + 0x20) + 0x298), name_1, 20, 0); }

inline void get_vehicle_name_2(uintptr_t instance, char(&name_2)[20]) { ReadProcessMemory(g_handle, (LPCVOID)(RPM<uintptr_t>(instance + 0x20) + 0x2A4), name_2, 20, 0); }

inline float get_ped_health(uintptr_t instance) { return RPM<float>(instance + 0x280); }

inline uint32_t get_ped_ped_type(uintptr_t instance) { return RPM<uint32_t>(instance + 0x1098) << 11 >> 25; }

inline void get_instace_model_matrix(uintptr_t instance, float(&matrix)[16]) { ReadProcessMemory(g_handle, (LPCVOID)(RPM<uintptr_t>(instance + 0x30) + 0x20), matrix, 16 * 4, 0); }