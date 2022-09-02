#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <fstream>

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/xchar.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <Dwmapi.h>
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#include "D3D9/D3D9.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif

#include "types.h"
#include "enum.h"
#include "globals.h"
#include "functions/functions.h"
#include "GDI/GDI.h"
#include "fonts/NotoSans-Regular.hpp"
#include "fonts/IconsFontAwesome5.h"
#include "fonts/fa-regular-400.hpp"
#include "fonts/fa-solid-900.hpp"
#include "fonts/seguisym.hpp"