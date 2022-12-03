#pragma once

class signature
{
	uintptr_t m_base;
	size_t m_size;
	std::unique_ptr<char[]> m_data;
    HANDLE m_handle;
	uintptr_t m_temp;
public:
	signature(std::string module_name)
	{
        m_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, g_process_id);
        HMODULE hMods[1024];
        DWORD cbNeeded;
        EnumProcessModules(m_handle, hMods, sizeof(hMods), &cbNeeded);
        for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            char szModName[MAX_PATH];
            GetModuleFileNameExA(m_handle, hMods[i], szModName, sizeof(szModName) / sizeof(char));
            std::string str = szModName;
            str = str.substr(str.find_last_of("\\") + 1);
            if (str == module_name)
            {
                MODULEINFO module_info;
                GetModuleInformation(m_handle, hMods[i], &module_info, sizeof(module_info));
                m_base = (uintptr_t)hMods[i];
                m_size = module_info.SizeOfImage;
                m_data = std::make_unique<char[]>(m_size);
                ReadProcessMemory(m_handle, (LPCVOID)m_base, m_data.get(), m_size, 0);
            }
        }
        m_temp = m_base;
	}

    ~signature()
    {
        m_data.reset();
        CloseHandle(m_handle);
    }

    signature& scan(std::string pattern)
    {
        m_temp = 0;

        std::stringstream ss(pattern);
        std::vector<std::string> substrings;
        std::string substring;
        while (std::getline(ss, substring, ' ')) substrings.push_back(substring);;
        
        std::vector<std::optional<char>> pattern_2;
        for (auto& str : substrings)
        {
            if (str == "?" || str == "??")
                pattern_2.push_back(std::nullopt);
            else
                pattern_2.push_back(strtol(str.c_str(), nullptr, 16));
        }

        for (size_t i = 0; i < m_size - pattern_2.size() + 1; i++)
        {
            size_t j;
            for (j = 0; j < pattern_2.size(); j++)
            {
                if (!pattern_2[j].has_value())
                    continue;
                if (pattern_2[j].value() != m_data.get()[i + j])
                    break;
            }
            if (j == pattern_2.size())
            {
                m_temp = m_base + i;
                return *this;
            }     
        }
        return *this;
    }

    signature& add(int value) { m_temp += value; return *this; }

    signature& sub(int value) { m_temp -= value; return *this; }

    signature& rip() 
    { 
        int value;
        ReadProcessMemory(m_handle, (LPCVOID)m_temp, &value, 4, 0);
        m_temp += value + 4;
        return *this;
    }

    template<typename T> T as() { return (T)m_temp; }
};