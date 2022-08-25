uintptr_t Signature(const char* pattern, const char* mask)
{
    uintptr_t result = 0;
    HMODULE hMods[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(handle, hMods, sizeof(hMods), &cbNeeded))
    {
        MODULEINFO module_info;
        if (GetModuleInformation(handle, hMods[0], &module_info, sizeof(module_info)))
        {
            uintptr_t module_addr = (uintptr_t)module_info.lpBaseOfDll;
            uint32_t module_size = module_info.SizeOfImage;
            char* buffer = new char[module_size];
            if (ReadProcessMemory(handle, (LPCVOID)module_addr, buffer, module_size, 0))
            {
                for (size_t i = 0; i < module_size - strlen(mask) + 1; i++)
                {
                    size_t j;
                    for (j = 0; j < strlen(mask); j++)
                    {
                        if (mask[j] == '?') continue;
                        if (buffer[i + j] != pattern[j]) break;
                    }
                    if (j == strlen(mask))
                    {
                        result = module_addr + i;
                        break;
                    }
                }
            }
            delete[] buffer;
        }
    }
    return result;
}