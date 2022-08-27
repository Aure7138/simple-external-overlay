bool is_menu_visible = true;
void LoadIO();
void LoadStyle();
void MainWindow();
int main()//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	GetWindowThreadProcessId(FindWindowA("grcWindow", 0), &process_id);
	handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, process_id);
	std::cout << fmt::format("process_id: {}\nhandle: {}\n", process_id, handle);
	ReplayInterfacePointer = Signature("\xE8\x00\x00\x00\x00\x40\x02\xFB\x40\x0A\xF0\x40\x3A\xFB\x72\xE1\x40\x84\xF6\x75\x72\x81\x7D\x00\x00\x00\x00\x00\x75\x69\x81\x7D\x00\x00\x00\x00\x00\x75\x60\x8B\x05\x00\x00\x00\x00\x39\x45\xBC", "x????xxxxxxxxxxxxxxxxxx?????xxxx?????xxxx????xxx"); // E8 ? ? ? ? 40 02 FB 40 0A F0 40 3A FB 72 E1 40 84 F6 75 72 81 7D ? ? ? ? ? 75 69 81 7D ? ? ? ? ? 75 60 8B 05 ? ? ? ? 39 45 BC
	ReplayInterfacePointer = ReplayInterfacePointer + RPM<int>(ReplayInterfacePointer + 1) + 5;
	ReplayInterfacePointer = ReplayInterfacePointer + 0x84;
	ReplayInterfacePointer = ReplayInterfacePointer + RPM<int>(ReplayInterfacePointer + 3) + 7;
	std::cout << fmt::format("ReplayInterfacePointer: {}\n", ReplayInterfacePointer);
	CPedFactoryPointer = Signature("\x75\x17\x48\x8B\x0D\x00\x00\x00\x00\x8B\xC3", "xxxxx????xx"); // 75 17 48 8B 0D ? ? ? ? 8B C3
	CPedFactoryPointer = CPedFactoryPointer + 2;
	CPedFactoryPointer = CPedFactoryPointer + RPM<int>(CPedFactoryPointer + 3) + 7;
	std::cout << fmt::format("CPedFactoryPointer: {}\n", CPedFactoryPointer);
	CViewportGamePointer = Signature("\x48\x8B\x15\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x48\x8B\xCD", "xxx????xxx????xxx"); // 48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD
	CViewportGamePointer = CViewportGamePointer + RPM<int>(CViewportGamePointer + 3) + 7;
	std::cout << fmt::format("CViewportGamePointer: {}\n", CViewportGamePointer);
	WindowWidth = Signature("\xF3\x0F\x10\x1D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00", "xxxx????xx????"); // F3 0F 10 1D ? ? ? ? 8B 0D ? ? ? ?
	WindowWidth = WindowWidth + 8;
	WindowWidth = WindowWidth + RPM<int>(WindowWidth + 2) + 6;
	std::cout << fmt::format("WindowWidth: {}\n", WindowWidth);
	camGameplayDirectorPointer = Signature("\x48\x8B\x05\x00\x00\x00\x00\x38\x98\x00\x00\x00\x00\x8A\xC3", "xxx????xx????xx"); // 48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3
	camGameplayDirectorPointer = camGameplayDirectorPointer + RPM<int>(camGameplayDirectorPointer + 3) + 7;
	std::cout << fmt::format("camGameplayDirectorPointer: {}\n", camGameplayDirectorPointer);
    CNetworkPlayerMgrPointer = Signature("\xE9\x00\x00\x00\x00\xCC\x41\x54\x41\xFF\x50\x10", "x????xxxxxxx"); // E9 ? ? ? ? CC 41 54 41 FF 50 10
    CNetworkPlayerMgrPointer = CNetworkPlayerMgrPointer + RPM<int>(CNetworkPlayerMgrPointer + 1) + 5;
    CNetworkPlayerMgrPointer = CNetworkPlayerMgrPointer + RPM<int>(CNetworkPlayerMgrPointer + 3) + 7;
    std::cout << fmt::format("CNetworkPlayerMgrPointer: {}\n", CNetworkPlayerMgrPointer);
    AimCPedPTR = Signature("\xE8\x00\x00\x00\x00\xB1\x01\x48\x81\xC4", "x????xxxxx"); // E8 ? ? ? ? B1 01 48 81 C4 ? ? ? ?
    AimCPedPTR = AimCPedPTR + RPM<int>(AimCPedPTR + 1) + 5;
    AimCPedPTR = AimCPedPTR + 0x293;
    AimCPedPTR = AimCPedPTR + RPM<int>(AimCPedPTR + 3) + 7;
    std::cout << fmt::format("AimCPedPTR: {}\n", AimCPedPTR);
	//GDI::Init();
	//while (true)
	//{
	//	update_data();
	//	update_automobiles();
	//	update_peds();
	//	update_pickups();
	//	update_objects();
	//	GDI::Draw();
	//}


    //D3D9::Init();
    {
        std::ifstream i("file.json");
        json j;
        if(i.is_open()) i >> j;
        if (!j["enable_esp"].is_null()) D3D9::enable_esp = j["enable_esp"];
        if (!j["render_only_in_game"].is_null()) D3D9::render_only_in_game = j["render_only_in_game"];
        if (!j["text_info"].is_null()) D3D9::text_info = j["text_info"];
        if (!j["text_info_color"].is_null()) D3D9::text_info_color = j["text_info_color"];

        if (!j["cautomobile_esp"].is_null()) D3D9::cautomobile_esp = j["cautomobile_esp"];
        if (!j["cautomobile_box"].is_null()) D3D9::cautomobile_box = j["cautomobile_box"];
        if (!j["cautomobile_box_color"].is_null()) D3D9::cautomobile_box_color = j["cautomobile_box_color"];
        if (!j["cautomobile_text_info"].is_null()) D3D9::cautomobile_text_info = j["cautomobile_text_info"];
        if (!j["cautomobile_text_info_color"].is_null()) D3D9::cautomobile_text_info_color = j["cautomobile_text_info_color"];

        if (!j["cped_esp"].is_null()) D3D9::cped_esp = j["cped_esp"];
        if (!j["cped_esp_exclude_self"].is_null()) D3D9::cped_esp_exclude_self = j["cped_esp_exclude_self"];
        if (!j["cped_box"].is_null()) D3D9::cped_box = j["cped_box"];
        if (!j["cped_box_color"].is_null()) D3D9::cped_box_color = j["cped_box_color"];
        if (!j["cped_text_info"].is_null()) D3D9::cped_text_info = j["cped_text_info"];
        if (!j["cped_text_info_color"].is_null()) D3D9::cped_text_info_color = j["cped_text_info_color"];
        if (!j["cped_bone"].is_null()) D3D9::cped_bone = j["cped_bone"];
        if (!j["cped_bone_color"].is_null()) D3D9::cped_bone_color = j["cped_bone_color"];

        if (!j["cpickup_esp"].is_null()) D3D9::cpickup_esp = j["cpickup_esp"];
        if (!j["cpickup_box"].is_null()) D3D9::cpickup_box = j["cpickup_box"];
        if (!j["cpickup_box_color"].is_null()) D3D9::cpickup_box_color = j["cpickup_box_color"];
        if (!j["cpickup_text_info"].is_null()) D3D9::cpickup_text_info = j["cpickup_text_info"];
        if (!j["cpickup_text_info_color"].is_null()) D3D9::cpickup_text_info_color = j["cpickup_text_info_color"];

        if (!j["cobject_esp"].is_null()) D3D9::cobject_esp = j["cobject_esp"];
        if (!j["cobject_box"].is_null()) D3D9::cobject_box = j["cobject_box"];
        if (!j["cobject_box_color"].is_null()) D3D9::cobject_box_color = j["cobject_box_color"];
        if (!j["cobject_text_info"].is_null()) D3D9::cobject_text_info = j["cobject_text_info"];
        if (!j["cobject_text_info_color"].is_null()) D3D9::cobject_text_info_color = j["cobject_text_info_color"];

        if (!j["player_esp"].is_null()) D3D9::player_esp = j["player_esp"];
        if (!j["player_esp_exclude_self"].is_null()) D3D9::player_esp_exclude_self = j["player_esp_exclude_self"];
        if (!j["player_box"].is_null()) D3D9::player_box = j["player_box"];
        if (!j["player_box_color"].is_null()) D3D9::player_box_color = j["player_box_color"];
        if (!j["player_text_info"].is_null()) D3D9::player_text_info = j["player_text_info"];
        if (!j["player_text_info_color"].is_null()) D3D9::player_text_info_color = j["player_text_info_color"];
        if (!j["trigger_bot_thread_globals"]["enable_trigger_bot"].is_null()) trigger_bot_thread_globals.enable_trigger_bot = j["trigger_bot_thread_globals"]["enable_trigger_bot"];
        if (!j["main_script_thread_globals"]["no_recoil"].is_null()) main_script_thread_globals.no_recoil = j["main_script_thread_globals"]["no_recoil"];
        if (!j["main_script_thread_globals"]["no_spread"].is_null()) main_script_thread_globals.no_spread = j["main_script_thread_globals"]["no_spread"];
        if (!j["main_script_thread_globals"]["one_shoot_kill"].is_null()) main_script_thread_globals.one_shoot_kill = j["main_script_thread_globals"]["one_shoot_kill"];
        if (!j["aimbot_thread_globals"]["enable_aimbot"].is_null()) aimbot_thread_globals.enable_aimbot = j["aimbot_thread_globals"]["enable_aimbot"];
        if (!j["aimbot_thread_globals"]["exclude_player"].is_null()) aimbot_thread_globals.exclude_player = j["aimbot_thread_globals"]["exclude_player"];
    }

	std::thread(D3D9::Init).detach();
    std::thread(trigger_bot_thread).detach();
    std::thread(main_script_thread).detach();
    std::thread(aimbot_thread).detach();

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Aure's Simple External Overlay"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Aure's Simple External Overlay"), WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_HIDE);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         

    LoadIO();
    LoadStyle();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX12_Init(g_pd3dDevice, NUM_FRAMES_IN_FLIGHT,
        DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap,
        g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (GetAsyncKeyState(VK_INSERT) & 1) is_menu_visible = !is_menu_visible;
        if (GetAsyncKeyState(VK_END) & 1) done = true;

        if (is_menu_visible)
            MainWindow();

        //if (show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();

        FrameContext* frameCtx = WaitForNextFrameResources();
        UINT backBufferIdx = g_pSwapChain->GetCurrentBackBufferIndex();
        frameCtx->CommandAllocator->Reset();

        D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier.Transition.pResource = g_mainRenderTargetResource[backBufferIdx];
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        g_pd3dCommandList->Reset(frameCtx->CommandAllocator, NULL);
        g_pd3dCommandList->ResourceBarrier(1, &barrier);

        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dCommandList->ClearRenderTargetView(g_mainRenderTargetDescriptor[backBufferIdx], clear_color_with_alpha, 0, NULL);
        g_pd3dCommandList->OMSetRenderTargets(1, &g_mainRenderTargetDescriptor[backBufferIdx], FALSE, NULL);
        g_pd3dCommandList->SetDescriptorHeaps(1, &g_pd3dSrvDescHeap);
        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pd3dCommandList);
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        g_pd3dCommandList->ResourceBarrier(1, &barrier);
        g_pd3dCommandList->Close();

        g_pd3dCommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&g_pd3dCommandList);

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault(NULL, (void*)g_pd3dCommandList);
        }

        g_pSwapChain->Present(1, 0);

        UINT64 fenceValue = g_fenceLastSignaledValue + 1;
        g_pd3dCommandQueue->Signal(g_fence, fenceValue);
        g_fenceLastSignaledValue = fenceValue;
        frameCtx->FenceValue = fenceValue;
    }

    WaitForLastSubmittedFrame();

    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    {
        std::ofstream o("file.json");
        json j;
        j["enable_esp"] = D3D9::enable_esp;
        j["render_only_in_game"] = D3D9::render_only_in_game;
        j["text_info"] = D3D9::text_info;
        j["text_info_color"] = D3D9::text_info_color;

        j["cautomobile_esp"] = D3D9::cautomobile_esp;
        j["cautomobile_box"] = D3D9::cautomobile_box;
        j["cautomobile_box_color"] = D3D9::cautomobile_box_color;
        j["cautomobile_text_info"] = D3D9::cautomobile_text_info;
        j["cautomobile_text_info_color"] = D3D9::cautomobile_text_info_color;

        j["cped_esp"] = D3D9::cped_esp;
        j["cped_esp_exclude_self"] = D3D9::cped_esp_exclude_self;
        j["cped_box"] = D3D9::cped_box;
        j["cped_box_color"] = D3D9::cped_box_color;
        j["cped_text_info"] = D3D9::cped_text_info;
        j["cped_text_info_color"] = D3D9::cped_text_info_color;
        j["cped_bone"] = D3D9::cped_bone;
        j["cped_bone_color"] = D3D9::cped_bone_color;

        j["cpickup_esp"] = D3D9::cpickup_esp;
        j["cpickup_box"] = D3D9::cpickup_box;
        j["cpickup_box_color"] = D3D9::cpickup_box_color;
        j["cpickup_text_info"] = D3D9::cpickup_text_info;
        j["cpickup_text_info_color"] = D3D9::cpickup_text_info_color;

        j["cobject_esp"] = D3D9::cobject_esp;
        j["cobject_box"] = D3D9::cobject_box;
        j["cobject_box_color"] = D3D9::cobject_box_color;
        j["cobject_text_info"] = D3D9::cobject_text_info;
        j["cobject_text_info_color"] = D3D9::cobject_text_info_color;

        j["player_esp"] = D3D9::player_esp;
        j["player_esp_exclude_self"] = D3D9::player_esp_exclude_self;
        j["player_box"] = D3D9::player_box;
        j["player_box_color"] = D3D9::player_box_color;
        j["player_text_info"] = D3D9::player_text_info;
        j["player_text_info_color"] = D3D9::player_text_info_color;
        j["trigger_bot_thread_globals"]["enable_trigger_bot"] = trigger_bot_thread_globals.enable_trigger_bot;
        j["main_script_thread_globals"]["no_recoil"] = main_script_thread_globals.no_recoil;
        j["main_script_thread_globals"]["no_spread"] = main_script_thread_globals.no_spread;
        j["main_script_thread_globals"]["one_shoot_kill"] = main_script_thread_globals.one_shoot_kill;
        j["aimbot_thread_globals"]["enable_aimbot"] = aimbot_thread_globals.enable_aimbot;
        j["aimbot_thread_globals"]["exclude_player"] = aimbot_thread_globals.exclude_player;
        o << std::setw(4) << j << std::endl;
    }

    return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC1 sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = NUM_BACK_BUFFERS;
        sd.Width = 0;
        sd.Height = 0;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.Stereo = FALSE;
    }

    // [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
    ID3D12Debug* pdx12Debug = NULL;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pdx12Debug))))
        pdx12Debug->EnableDebugLayer();
#endif

    // Create device
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    if (D3D12CreateDevice(NULL, featureLevel, IID_PPV_ARGS(&g_pd3dDevice)) != S_OK)
        return false;

    // [DEBUG] Setup debug interface to break on any warnings/errors
#ifdef DX12_ENABLE_DEBUG_LAYER
    if (pdx12Debug != NULL)
    {
        ID3D12InfoQueue* pInfoQueue = NULL;
        g_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pInfoQueue));
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
        pInfoQueue->Release();
        pdx12Debug->Release();
    }
#endif

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = NUM_BACK_BUFFERS;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask = 1;
        if (g_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dRtvDescHeap)) != S_OK)
            return false;

        SIZE_T rtvDescriptorSize = g_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();
        for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
        {
            g_mainRenderTargetDescriptor[i] = rtvHandle;
            rtvHandle.ptr += rtvDescriptorSize;
        }
    }

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = 1;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        if (g_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dSrvDescHeap)) != S_OK)
            return false;
    }

    {
        D3D12_COMMAND_QUEUE_DESC desc = {};
        desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 1;
        if (g_pd3dDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&g_pd3dCommandQueue)) != S_OK)
            return false;
    }

    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (g_pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_frameContext[i].CommandAllocator)) != S_OK)
            return false;

    if (g_pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_frameContext[0].CommandAllocator, NULL, IID_PPV_ARGS(&g_pd3dCommandList)) != S_OK ||
        g_pd3dCommandList->Close() != S_OK)
        return false;

    if (g_pd3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)) != S_OK)
        return false;

    g_fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (g_fenceEvent == NULL)
        return false;

    {
        IDXGIFactory4* dxgiFactory = NULL;
        IDXGISwapChain1* swapChain1 = NULL;
        if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)) != S_OK)
            return false;
        if (dxgiFactory->CreateSwapChainForHwnd(g_pd3dCommandQueue, hWnd, &sd, NULL, NULL, &swapChain1) != S_OK)
            return false;
        if (swapChain1->QueryInterface(IID_PPV_ARGS(&g_pSwapChain)) != S_OK)
            return false;
        swapChain1->Release();
        dxgiFactory->Release();
        g_pSwapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
        g_hSwapChainWaitableObject = g_pSwapChain->GetFrameLatencyWaitableObject();
    }

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->SetFullscreenState(false, NULL); g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_hSwapChainWaitableObject != NULL) { CloseHandle(g_hSwapChainWaitableObject); }
    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (g_frameContext[i].CommandAllocator) { g_frameContext[i].CommandAllocator->Release(); g_frameContext[i].CommandAllocator = NULL; }
    if (g_pd3dCommandQueue) { g_pd3dCommandQueue->Release(); g_pd3dCommandQueue = NULL; }
    if (g_pd3dCommandList) { g_pd3dCommandList->Release(); g_pd3dCommandList = NULL; }
    if (g_pd3dRtvDescHeap) { g_pd3dRtvDescHeap->Release(); g_pd3dRtvDescHeap = NULL; }
    if (g_pd3dSrvDescHeap) { g_pd3dSrvDescHeap->Release(); g_pd3dSrvDescHeap = NULL; }
    if (g_fence) { g_fence->Release(); g_fence = NULL; }
    if (g_fenceEvent) { CloseHandle(g_fenceEvent); g_fenceEvent = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }

#ifdef DX12_ENABLE_DEBUG_LAYER
    IDXGIDebug1* pDebug = NULL;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug))))
    {
        pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
        pDebug->Release();
    }
#endif
}

void CreateRenderTarget()
{
    for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
    {
        ID3D12Resource* pBackBuffer = NULL;
        g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, g_mainRenderTargetDescriptor[i]);
        g_mainRenderTargetResource[i] = pBackBuffer;
    }
}

void CleanupRenderTarget()
{
    WaitForLastSubmittedFrame();

    for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
        if (g_mainRenderTargetResource[i]) { g_mainRenderTargetResource[i]->Release(); g_mainRenderTargetResource[i] = NULL; }
}

void WaitForLastSubmittedFrame()
{
    FrameContext* frameCtx = &g_frameContext[g_frameIndex % NUM_FRAMES_IN_FLIGHT];

    UINT64 fenceValue = frameCtx->FenceValue;
    if (fenceValue == 0)
        return;

    frameCtx->FenceValue = 0;
    if (g_fence->GetCompletedValue() >= fenceValue)
        return;

    g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);
}

FrameContext* WaitForNextFrameResources()
{
    UINT nextFrameIndex = g_frameIndex + 1;
    g_frameIndex = nextFrameIndex;

    HANDLE waitableObjects[] = { g_hSwapChainWaitableObject, NULL };
    DWORD numWaitableObjects = 1;

    FrameContext* frameCtx = &g_frameContext[nextFrameIndex % NUM_FRAMES_IN_FLIGHT];
    UINT64 fenceValue = frameCtx->FenceValue;
    if (fenceValue != 0)
    {
        frameCtx->FenceValue = 0;
        g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
        waitableObjects[1] = g_fenceEvent;
        numWaitableObjects = 2;
    }

    WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

    return frameCtx;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            WaitForLastSubmittedFrame();
            CleanupRenderTarget();
            HRESULT result = g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);
            assert(SUCCEEDED(result) && "Failed to resize swapchain.");
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}


void LoadIO()
{
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(NotoSans_Regular_compressed_data, NotoSans_Regular_compressed_size, 24.0f);

    ImFontConfig config;
    config.MergeMode = true;
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa_regular_400_compressed_data, fa_regular_400_compressed_size, 18.0f, &config, icon_ranges);
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data, fa_solid_900_compressed_size, 18.0f, &config, icon_ranges);

    static const ImWchar ranges[] = { 0x1, 0x1FFFF, 0 };
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(seguisym_compressed_data, seguisym_compressed_size, 18.0f, &config, ranges);
}

void LoadStyle()
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

void MainWindow()
{
    auto D3DCOLOR2ImVec4 = [](D3DCOLOR color) -> ImVec4
    {
        return ImVec4(
            static_cast<float>(((color >> 16) & 0xFF) / 255.0),
            static_cast<float>(((color >> 8) & 0xFF) / 255.0),
            static_cast<float>((color & 0xFF) / 255.0),
            static_cast<float>(((color >> 24) & 0xFF) / 255.0));
    };
    auto ImVec42D3DCOLOR = [](ImVec4 color) -> D3DCOLOR {return ImColor(color.z, color.y, color.x, color.w); };

	ImGui::Begin("Aure's Simple External Ovelay", &is_menu_visible);

    float width = ImGui::GetContentRegionAvail().x;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, width * 0.3);
    ImGui::SetColumnWidth(1, width * 0.7);

	ImGui::Text("INS Show/Hide Menu");
	ImGui::Text("END To Quit Program");
    ImGui::Checkbox("Enable ESP", &D3D9::enable_esp);
    ImGui::Checkbox("Render Only In Game", &D3D9::render_only_in_game);

    {
        ImGui::Checkbox("Show Text", &D3D9::text_info);
        static ImVec4 color = D3DCOLOR2ImVec4(D3D9::text_info_color);
        if (ImGui::ColorEdit4("Text Color", (float*)&color)) { D3D9::text_info_color = ImVec42D3DCOLOR(color); }
    }

    ImGui::NextColumn();

    static int index = 0;

    int btn_count = 5;
    float btn_width = (ImGui::GetContentRegionAvail().x - (btn_count - 1) * ImGui::GetStyle().ItemSpacing.x - 0.5) / btn_count;

    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[index == 0 ? ImGuiCol_ButtonActive : ImGuiCol_Button]);
    if (ImGui::Button("Automobile", ImVec2(btn_width, 0))) index = 0;
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[index == 1 ? ImGuiCol_ButtonActive : ImGuiCol_Button]);
    if (ImGui::Button("Ped", ImVec2(btn_width, 0))) index = 1;
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[index == 2 ? ImGuiCol_ButtonActive : ImGuiCol_Button]);
    if (ImGui::Button("Pickup", ImVec2(btn_width, 0))) index = 2;
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[index == 3 ? ImGuiCol_ButtonActive : ImGuiCol_Button]);
    if (ImGui::Button("Object", ImVec2(btn_width, 0))) index = 3;
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[index == 4 ? ImGuiCol_ButtonActive : ImGuiCol_Button]);
    if (ImGui::Button("Player", ImVec2(btn_width, 0))) index = 4;
    ImGui::PopStyleColor();

    switch (index)
    {
    case 0:
    {
        ImGui::Checkbox("Automobile Esp", &D3D9::cautomobile_esp);

        {
            ImGui::Checkbox("Automobile Box", &D3D9::cautomobile_box);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cautomobile_box_color);
            if (ImGui::ColorEdit4("Automobile Box Color", (float*)&color)) { D3D9::cautomobile_box_color = ImVec42D3DCOLOR(color); }
        }

        {
            ImGui::Checkbox("Automobile Text Info", &D3D9::cautomobile_text_info);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cautomobile_text_info_color);
            if (ImGui::ColorEdit4("Automobile Text Info Color", (float*)&color)) { D3D9::cautomobile_text_info_color = ImVec42D3DCOLOR(color); }
        }
    }
    break;
    case 1:
    {
        ImGui::Checkbox("Ped Esp", &D3D9::cped_esp);

        ImGui::Checkbox("Ped Esp Exclude Self", &D3D9::cped_esp_exclude_self);

        {
            ImGui::Checkbox("Ped Box", &D3D9::cped_box);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cped_box_color);
            if (ImGui::ColorEdit4("Ped Box Color", (float*)&color)) { D3D9::cped_box_color = ImVec42D3DCOLOR(color); }
        }

        {
            ImGui::Checkbox("Ped Text Info", &D3D9::cped_text_info);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cped_text_info_color);
            if (ImGui::ColorEdit4("Ped Text Info Color", (float*)&color)) { D3D9::cped_text_info_color = ImVec42D3DCOLOR(color); }
        }

        {
            ImGui::Checkbox("Ped Bone", &D3D9::cped_bone);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cped_bone_color);
            if (ImGui::ColorEdit4("Ped Bone Color", (float*)&color)) { D3D9::cped_bone_color = ImVec42D3DCOLOR(color); }
        }
    }
    break;
    case 2:
    {
        ImGui::Checkbox("Pickup Esp", &D3D9::cpickup_esp);

        {
            ImGui::Checkbox("Pickup Box", &D3D9::cpickup_box);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cpickup_box_color);
            if (ImGui::ColorEdit4("Pickup Box Color", (float*)&color)) { D3D9::cpickup_box_color = ImVec42D3DCOLOR(color); }
        }

        {
            ImGui::Checkbox("Pickup Text Info", &D3D9::cpickup_text_info);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cpickup_text_info_color);
            if (ImGui::ColorEdit4("Pickup Text Info Color", (float*)&color)) { D3D9::cpickup_text_info_color = ImVec42D3DCOLOR(color); }
        }
    }
    break;
    case 3:
    {
        ImGui::Checkbox("Object Esp", &D3D9::cobject_esp);

        {
            ImGui::Checkbox("Object Box", &D3D9::cobject_box);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cobject_box_color);
            if (ImGui::ColorEdit4("Object Box Color", (float*)&color)) { D3D9::cobject_box_color = ImVec42D3DCOLOR(color); }
        }

        {
            ImGui::Checkbox("Object Text Info", &D3D9::cobject_text_info);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::cobject_text_info_color);
            if (ImGui::ColorEdit4("Object Text Info Color", (float*)&color)) { D3D9::cobject_text_info_color = ImVec42D3DCOLOR(color); }
        }
    }
    break;
    case 4:
    {
        ImGui::Checkbox("Player Esp", &D3D9::player_esp);

        ImGui::Checkbox("Player Esp Exclude Self", &D3D9::player_esp_exclude_self);

        {
            ImGui::Checkbox("Player Box", &D3D9::player_box);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::player_box_color);
            if (ImGui::ColorEdit4("Player Box Color", (float*)&color)) { D3D9::player_box_color = ImVec42D3DCOLOR(color); }
        }

        {
            ImGui::Checkbox("Player Text Info", &D3D9::player_text_info);
            static ImVec4 color = D3DCOLOR2ImVec4(D3D9::player_text_info_color);
            if (ImGui::ColorEdit4("Player Text Info Color", (float*)&color)) { D3D9::player_text_info_color = ImVec42D3DCOLOR(color); }
        }
    }
    break;
    default:
        break;
    }
    ImGui::Columns(1);
    ImGui::BeginGroup();
    ImGui::Checkbox("Enable Trigger Bot", &trigger_bot_thread_globals.enable_trigger_bot);
    ImGui::Checkbox("No Recoil", &main_script_thread_globals.no_recoil);
    ImGui::Checkbox("No Spread", &main_script_thread_globals.no_spread);
    ImGui::Checkbox("One Shoot Kill", &main_script_thread_globals.one_shoot_kill);
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
    ImGui::Checkbox("Enable Aimbot (Hold Right Mouse)", &aimbot_thread_globals.enable_aimbot);
    ImGui::Checkbox("Aimbot Exclude Player", &aimbot_thread_globals.exclude_player);
    ImGui::EndGroup();
	ImGui::End();
}