static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void main_window();
void esp_window();

int main()//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    if (!FindWindowA("grcWindow", nullptr))
    {
        MessageBoxA(NULL, "Please run game first", "Error", MB_ICONERROR);
        return 0;
    }
	GetWindowThreadProcessId(FindWindowA("grcWindow", nullptr), &g_process_id);
    spdlog::info("process_id                    : {}", g_process_id);
	g_handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, g_process_id);
    spdlog::info("handle                        : {}", g_handle);
	
    signature GTA5_exe("GTA5.exe");
    ReplayInterfacePointer = GTA5_exe.scan("E8 ? ? ? ? 40 02 FB 40 0A F0 40 3A FB 72 E1 40 84 F6 75 72 81 7D ? ? ? ? ? 75 69 81 7D ? ? ? ? ? 75 60 8B 05 ? ? ? ? 39 45 BC").add(1).rip().add(0x84).add(3).rip().as<uintptr_t>();
    spdlog::info("ReplayInterfacePointer        : {:0X}", ReplayInterfacePointer);
	
    CPedFactoryPointer = GTA5_exe.scan("75 17 48 8B 0D ? ? ? ? 8B C3").add(2).add(3).rip().as<uintptr_t>();
    spdlog::info("CPedFactoryPointer            : {:0X}", CPedFactoryPointer);
	
    CViewportGamePointer = GTA5_exe.scan("48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD").add(3).rip().as<uintptr_t>();
    spdlog::info("CViewportGamePointer          : {:0X}", CViewportGamePointer);
	
    WindowWidth = GTA5_exe.scan("F3 0F 10 1D ? ? ? ? 8B 0D").add(8).add(2).rip().as<uintptr_t>();
    spdlog::info("WindowWidth                   : {:0X}", WindowWidth);
	
    camGameplayDirectorPointer = GTA5_exe.scan("48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3").add(3).rip().as<uintptr_t>();
    spdlog::info("camGameplayDirectorPointer    : {:0X}", camGameplayDirectorPointer);
    
    CNetworkPlayerMgrPointer = GTA5_exe.scan("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 37").add(3).rip().as<uintptr_t>();
    spdlog::info("CNetworkPlayerMgrPointer      : {:0X}", CNetworkPlayerMgrPointer);
    
    AimCPedPointer = GTA5_exe.scan("E8 ? ? ? ? B1 01 48 81 C4").add(1).rip().add(0x293).add(3).rip().as<uintptr_t>();
    spdlog::info("AimCPedPointer                : {:0X}", AimCPedPointer);

    g_settings = std::make_unique<settings>();
    std::thread(main_thread).detach();
    std::thread(trigger_bot_thread).detach();
    std::thread(aimbot_thread).detach();
    std::thread(update_esp_data_thread).detach();

    WNDCLASSEXW wc = { sizeof(wc), CS_VREDRAW | CS_HREDRAW, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED, wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_POPUP, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    {
        //static ImFontConfig config;
        //config.SizePixels = 26.f;
        //ImGui::GetIO().Fonts->AddFontDefault(&config);
    }

    {
        auto& style = ImGui::GetStyle();
        style.WindowPadding = { 10.f, 10.f };
        style.PopupRounding = 0.f;
        style.FramePadding = { 8.f, 4.f };
        style.ItemSpacing = { 10.f, 8.f };
        style.ItemInnerSpacing = { 6.f, 6.f };
        style.TouchExtraPadding = { 0.f, 0.f };
        style.IndentSpacing = 21.f;
        style.ScrollbarSize = 15.f;
        style.GrabMinSize = 8.f;
        style.WindowBorderSize = 1.f;
        style.ChildBorderSize = 0.f;
        style.PopupBorderSize = 1.f;
        style.FrameBorderSize = 0.f;
        style.TabBorderSize = 0.f;
        style.WindowRounding = 0.f;
        style.ChildRounding = 0.f;
        style.FrameRounding = 0.f;
        style.ScrollbarRounding = 0.f;
        style.GrabRounding = 0.f;
        style.TabRounding = 0.f;
        style.WindowTitleAlign = { 0.5f, 0.5f };
        style.ButtonTextAlign = { 0.5f, 0.5f };
        style.DisplaySafeAreaPadding = { 3.f, 3.f };

        auto& colors = style.Colors;
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.38f, 0.38f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.41f, 0.41f, 0.41f, 0.74f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.78f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 0.87f);
        colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
        colors[ImGuiCol_Separator] = ImVec4(0.38f, 0.38f, 0.38f, 0.50f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.50f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.64f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 0.86f);
        colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 0.86f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        colors[ImGuiCol_ButtonActive] = ImColor(189, 100, 100, 255);
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);

    while (g_running)
    {
        WINDOWINFO info;
        GetWindowInfo(FindWindowA("grcWindow", nullptr), &info);
        MoveWindow(hwnd, info.rcClient.left, info.rcClient.top, info.rcClient.right - info.rcClient.left, info.rcClient.bottom - info.rcClient.top, true);

        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                g_running = false;
        }
        if (!g_running)
            break;

        if (GetAsyncKeyState(VK_INSERT) & 0x1) g_settings->menu_opened = !g_settings->menu_opened;
        if (GetAsyncKeyState(VK_END) & 0x1) g_running = false;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (g_settings->menu_opened)
            main_window();
        esp_window();

        ImGui::EndFrame();
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void main_window()
{
	ImGui::Begin("Aure's Simple External Ovelay");

	ImGui::Text("INS Show/Hide Menu");
	ImGui::Text("END To Quit Program");

    ImGui::Checkbox("Enable Trigger Bot", &g_settings->weapon.trigger_bot);
    ImGui::Checkbox("No Recoil", &g_settings->weapon.no_recoil);
    ImGui::Checkbox("No Spread", &g_settings->weapon.no_spread);
    ImGui::Checkbox("One Shoot Kill", &g_settings->weapon.one_shoot_kill);
    ImGui::Checkbox("Never Wanted", &g_settings->self.never_wanted);
    ImGui::Checkbox("Aimbot (Hold Right Mouse)", &g_settings->weapon.aimbot);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Will select the Ped closest to you on the screen as the target");
    if (g_settings->weapon.aimbot)
    {
        ImGui::SameLine();
        ImGui::Checkbox("Player Only", &g_settings->weapon.aimbot_player_only);
    }

    ImGui::Checkbox("ESP", &g_settings->esp.enable);
    if (g_settings->esp.enable)
    {
        ImGui::SameLine();
        ImGui::ColorEdit4("Color##ESP", (float*)&g_settings->esp.color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        ImGui::Checkbox("Vehicle", &g_settings->esp.vehicle.enable);
        if (g_settings->esp.vehicle.enable)
        {
            ImGui::SameLine();
            ImGui::Checkbox("Line##Vehicle", &g_settings->esp.vehicle.line);
            ImGui::SameLine();
            ImGui::Checkbox("Text##Vehicle", &g_settings->esp.vehicle.text);
            ImGui::SameLine();
            ImGui::ColorEdit4("Color##Vehicle", (float*)&g_settings->esp.vehicle.color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        }
        ImGui::Checkbox("Ped", &g_settings->esp.ped.enable);
        if (g_settings->esp.ped.enable)
        {
            ImGui::SameLine();
            ImGui::Checkbox("Line##Ped", &g_settings->esp.ped.line);
            ImGui::SameLine();
            ImGui::Checkbox("Text##Ped", &g_settings->esp.ped.text);
            ImGui::SameLine();
            ImGui::Checkbox("Bone##Ped", &g_settings->esp.ped.bone);
            ImGui::SameLine();
            ImGui::Checkbox("Box##Ped", &g_settings->esp.ped.box);
            ImGui::SameLine();
            ImGui::ColorEdit4("Color##Ped", (float*)&g_settings->esp.ped.color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
            ImGui::SameLine();
            ImGui::Checkbox("Exclude Self##Ped", &g_settings->esp.ped.exclude_self);
        }
        ImGui::Checkbox("Pickup", &g_settings->esp.pickup.enable);
        if (g_settings->esp.pickup.enable)
        {
            ImGui::SameLine();
            ImGui::Checkbox("Line##Pickup", &g_settings->esp.pickup.line);
            ImGui::SameLine();
            ImGui::Checkbox("Text##Pickup", &g_settings->esp.pickup.text);
            ImGui::SameLine();
            ImGui::ColorEdit4("Color##Pickup", (float*)&g_settings->esp.pickup.color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        }
        ImGui::Checkbox("Object", &g_settings->esp.object.enable);
        if (g_settings->esp.object.enable)
        {
            ImGui::SameLine();
            ImGui::Checkbox("Line##Object", &g_settings->esp.object.line);
            ImGui::SameLine();
            ImGui::Checkbox("Text##Object", &g_settings->esp.object.text);
            ImGui::SameLine();
            ImGui::ColorEdit4("Color##Object", (float*)&g_settings->esp.object.color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        }
    }

	ImGui::End();
}

void esp_window()
{
    if (g_settings->esp.enable)
    { 
        ImGui::GetBackgroundDrawList()->AddText({ 10, (float)esp_game_height / 2 - 2 * 13 }, g_settings->esp.color, std::format("Vehicle: {}\nPed    : {}\nPickup : {}\nObject : {}\nFPS    : {:.1f}", esp_num_vehicle, esp_num_ped, esp_num_pickup, esp_num_object, ImGui::GetIO().Framerate).c_str());
        if (g_settings->esp.vehicle.enable)
        {
            for (int i = 0; i < sizeof(esp_vehicle.item) / sizeof(esp_vehicle.item[0]); i++)
            {
                if (esp_vehicle.item[i].instance)
                {
                    Vector3 image_coords;
                    Vector3 world_coords_2 = esp_vehicle.item[i].world_coords; world_coords_2.z += 1;
                    Vector3 image_coords_2;
                    if (WorldToScreen(esp_vehicle.item[i].world_coords, image_coords, esp_matirx, esp_game_width, esp_game_height) && WorldToScreen(world_coords_2, image_coords_2, esp_matirx, esp_game_width, esp_game_height))
                    {
                        int box_height = (image_coords.y - image_coords_2.y) * 2;
                        int box_width = box_height / 2.4;
                        if (g_settings->esp.vehicle.line)
                        {
                            ImGui::GetBackgroundDrawList()->AddLine({ (float)esp_game_width / 2, 0 }, { image_coords.x, image_coords.y }, g_settings->esp.vehicle.color);
                        }
                        if (g_settings->esp.vehicle.text)
                        {
                            ImGui::GetBackgroundDrawList()->AddText({ image_coords.x + box_width, image_coords.y }, g_settings->esp.vehicle.color, std::format("dist: {:.2f}\nhash: {}\nname: {}\nname: {}", esp_vehicle.item[i].text.dist, esp_vehicle.item[i].text.hash, esp_vehicle.item[i].text.name_1, esp_vehicle.item[i].text.name_2).c_str());
                        }
                    }
                }
            }
        }
        if (g_settings->esp.ped.enable)
        {
            for (int i = 0; i < sizeof(esp_ped.item) / sizeof(esp_ped.item[0]); i++)
            {
                if (esp_ped.item[i].instance)
                {
                    if (g_settings->esp.ped.exclude_self && esp_ped.item[i].instance == esp_self.instance) continue;
                    Vector3 image_coords;
                    Vector3 world_coords_2 = esp_ped.item[i].world_coords; world_coords_2.z += 1;
                    Vector3 image_coords_2;
                    if (WorldToScreen(esp_ped.item[i].world_coords, image_coords, esp_matirx, esp_game_width, esp_game_height) && WorldToScreen(world_coords_2, image_coords_2, esp_matirx, esp_game_width, esp_game_height))
                    {
                        int box_height = (image_coords.y - image_coords_2.y) * 2;
                        int box_width = box_height / 2.4;
                        if (g_settings->esp.ped.line)
                        {
                            ImGui::GetBackgroundDrawList()->AddLine({ (float)esp_game_width / 2, 0 }, { image_coords.x, image_coords.y }, g_settings->esp.ped.color);
                        }
                        if (g_settings->esp.ped.text)
                        {
                            ImGui::GetBackgroundDrawList()->AddText({ image_coords.x + box_width, image_coords.y }, g_settings->esp.ped.color, std::format("dist    : {:.2f}\nhash    : {}\nhealth  : {}\nped type: {}", esp_ped.item[i].text.dist, esp_ped.item[i].text.hash, esp_ped.item[i].text.health, esp_ped.item[i].text.ped_type).c_str());
                        }
                        if (g_settings->esp.ped.bone)
                        {
                            Vector3 image_coords_3[9];
                            if (WorldToScreen(esp_ped.item[i].bone[0].world_coords, image_coords_3[0], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[1].world_coords, image_coords_3[1], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[2].world_coords, image_coords_3[2], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[3].world_coords, image_coords_3[3], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[4].world_coords, image_coords_3[4], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[5].world_coords, image_coords_3[5], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[6].world_coords, image_coords_3[6], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[7].world_coords, image_coords_3[7], esp_matirx, esp_game_width, esp_game_height) &&
                                WorldToScreen(esp_ped.item[i].bone[8].world_coords, image_coords_3[8], esp_matirx, esp_game_width, esp_game_height))
                            {
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::Head].x, image_coords_3[Bone::Head].y }, { image_coords_3[Bone::Neck].x, image_coords_3[Bone::Neck].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::Neck].x, image_coords_3[Bone::Neck].y }, { image_coords_3[Bone::LeftHand].x, image_coords_3[Bone::LeftHand].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::Neck].x, image_coords_3[Bone::Neck].y }, { image_coords_3[Bone::RightHand].x, image_coords_3[Bone::RightHand].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::Neck].x, image_coords_3[Bone::Neck].y }, { image_coords_3[Bone::Abdomen].x, image_coords_3[Bone::Abdomen].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::Abdomen].x, image_coords_3[Bone::Abdomen].y }, { image_coords_3[Bone::LeftAnkle].x, image_coords_3[Bone::LeftAnkle].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::Abdomen].x, image_coords_3[Bone::Abdomen].y }, { image_coords_3[Bone::RightAnkle].x, image_coords_3[Bone::RightAnkle].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::LeftAnkle].x, image_coords_3[Bone::LeftAnkle].y }, { image_coords_3[Bone::LeftToe].x, image_coords_3[Bone::LeftToe].y }, g_settings->esp.ped.color);
                                ImGui::GetBackgroundDrawList()->AddLine({ image_coords_3[Bone::RightAnkle].x, image_coords_3[Bone::RightAnkle].y }, { image_coords_3[Bone::RightToe].x, image_coords_3[Bone::RightToe].y }, g_settings->esp.ped.color);
                            }
                        }
                        if (g_settings->esp.ped.box)
                        {
                            ImGui::GetBackgroundDrawList()->AddRect({ image_coords.x - box_width, image_coords.y - box_height }, { image_coords.x + box_width, image_coords.y + box_height }, g_settings->esp.ped.color);
                        }
                    }
                }
            }
        }
        if (g_settings->esp.pickup.enable)
        {
            for (int i = 0; i < sizeof(esp_pickup.item) / sizeof(esp_pickup.item[0]); i++)
            {
                if (esp_pickup.item[i].instance)
                {
                    Vector3 image_coords;
                    Vector3 world_coords_2 = esp_pickup.item[i].world_coords; world_coords_2.z += 1;
                    Vector3 image_coords_2;
                    if (WorldToScreen(esp_pickup.item[i].world_coords, image_coords, esp_matirx, esp_game_width, esp_game_height) && WorldToScreen(world_coords_2, image_coords_2, esp_matirx, esp_game_width, esp_game_height))
                    {
                        int box_height = (image_coords.y - image_coords_2.y) * 2;
                        int box_width = box_height / 2.4;
                        if (g_settings->esp.pickup.line)
                        {
                            ImGui::GetBackgroundDrawList()->AddLine({ (float)esp_game_width / 2, 0 }, { image_coords.x, image_coords.y }, g_settings->esp.pickup.color);
                        }
                        if (g_settings->esp.pickup.text)
                        {
                            ImGui::GetBackgroundDrawList()->AddText({ image_coords.x + box_width, image_coords.y }, g_settings->esp.pickup.color, std::format("dist: {:.2f}\nhash: {}", esp_pickup.item[i].text.dist, esp_pickup.item[i].text.hash).c_str());
                        }
                    }
                }
            }
        }
        if (g_settings->esp.object.enable)
        {
            for (int i = 0; i < sizeof(esp_object.item) / sizeof(esp_object.item[0]); i++)
            {
                if (esp_object.item[i].instance)
                {
                    Vector3 image_coords;
                    Vector3 world_coords_2 = esp_object.item[i].world_coords; world_coords_2.z += 1;
                    Vector3 image_coords_2;
                    if (WorldToScreen(esp_object.item[i].world_coords, image_coords, esp_matirx, esp_game_width, esp_game_height) && WorldToScreen(world_coords_2, image_coords_2, esp_matirx, esp_game_width, esp_game_height))
                    {
                        int box_height = (image_coords.y - image_coords_2.y) * 2;
                        int box_width = box_height / 2.4;
                        if (g_settings->esp.object.line)
                        {
                            ImGui::GetBackgroundDrawList()->AddLine({ (float)esp_game_width / 2, 0 }, { image_coords.x, image_coords.y }, g_settings->esp.object.color);
                        }
                        if (g_settings->esp.object.text)
                        {
                            ImGui::GetBackgroundDrawList()->AddText({ image_coords.x + box_width, image_coords.y }, g_settings->esp.object.color, std::format("dist: {:.2f}\nhash: {}", esp_object.item[i].text.dist, esp_object.item[i].text.hash).c_str());
                        }
                    }
                }
            }
        }
    }
}