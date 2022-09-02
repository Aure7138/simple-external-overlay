void render_thread()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW,
        [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT
        {
            switch (message) {
            case WM_PAINT:
            {
                D3D9::d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
                D3D9::d3dDevice->BeginScene();
                if (!g->render_thread.enable_esp)
                    goto CONTINUE;
                if (g->render_thread.render_only_in_game && target_hwnd != GetForegroundWindow())
                    goto CONTINUE;
                {
                    int width = RPM<int>(WindowWidth);
                    int height = RPM<int>(WindowWidth + 4);
                    float matrix[16];
                    ReadProcessMemory(handle, LPCVOID(RPM<uintptr_t>(CViewportGamePointer) + 0x250), matrix, 4 * 16, 0);
                    uintptr_t local_ped = RPM<uintptr_t>(CPedFactoryPointer, { 0x8 });
                    uintptr_t automobile = RPM<uintptr_t>(ReplayInterfacePointer, { 0x10 });
                    int automobile_max_count = RPM<int>(automobile + 0x188);
                    int automobile_current_count = RPM<int>(automobile + 0x190);
                    uintptr_t ped = RPM<uintptr_t>(ReplayInterfacePointer, { 0x18 });
                    int ped_max_count = RPM<int>(ped + 0x108);
                    int ped_current_count = RPM<int>(ped + 0x110);
                    uintptr_t pickup = RPM<uintptr_t>(ReplayInterfacePointer, { 0x20 });
                    int pickup_max_count = RPM<int>(pickup + 0x108);
                    int pickup_current_count = RPM<int>(pickup + 0x110);
                    uintptr_t object = RPM<uintptr_t>(ReplayInterfacePointer, { 0x28 });
                    int object_max_count = RPM<int>(object + 0x160);
                    int object_current_count = RPM<int>(object + 0x168);
                    uintptr_t player = RPM<uintptr_t>(CNetworkPlayerMgrPointer);
                    int player_current_count = 0;
                    for (int i = 0; i < 32; i++)
                    {
                        uintptr_t p = RPM<uintptr_t>(player + 0x180 + i * 8);
                        if (p == 0) continue;
                        player_current_count++;
                    }
                    if (g->render_thread.text_info)
                        D3D9::StringW(10, height / 3, g->render_thread.text_info_color, D3D9::font_big, false, fmt::format(L"Frame Rate: {}\nCAutomobile Pool: {}/{}\nCPed Pool: {}/{}\nCPickup Pool: {}/{}\nCObject Pool: {}/{}\nOnline Player: {}/32", D3D9::FrameRate(), automobile_current_count, automobile_max_count, ped_current_count, ped_max_count, pickup_current_count, pickup_max_count, object_current_count, object_max_count, player_current_count).c_str());
                    if (g->render_thread.automobile_esp)
                    {
                        uintptr_t list = RPM<uintptr_t>(automobile + 0x180);
                        for (int i = 0, j = 0; i < automobile_max_count; i++)
                        {
                            if (j == automobile_current_count)
                                break;
                            uintptr_t instance = RPM<uintptr_t>(list + i * 0x10);
                            if (instance == 0)
                                continue;
                            j++;
                            Vector3 world_coordinates = RPM<Vector3>(instance + 0x90);
                            Vector3 image_coordinates;
                            if (WorldToScreen(world_coordinates, image_coordinates, matrix, width, height))
                            {
                                Vector3 head_world_coordinates = world_coordinates;
                                head_world_coordinates.z += 1;
                                Vector3 head_image_coordinates;
                                WorldToScreen(head_world_coordinates, head_image_coordinates, matrix, width, height);
                                int box_height = (image_coordinates.y - head_image_coordinates.y) * 2;
                                int box_width = box_height * 2.4;
                                if (g->render_thread.automobile_box)
                                {
                                    D3D9::BorderedBox(image_coordinates.x - box_width / 2, image_coordinates.y - box_height / 2, box_width, box_height, 1, g->render_thread.automobile_box_color);
                                    D3D9::Line(width / 2, 0, head_image_coordinates.x, head_image_coordinates.y, g->render_thread.automobile_box_color);
                                }
                                if (g->render_thread.automobile_text_info)
                                {
                                    uintptr_t model_info = RPM<uintptr_t>(instance + 0x20);
                                    uint32_t hash = RPM<uint32_t>(model_info + 0x18);
                                    char name1[20];
                                    ReadProcessMemory(handle, LPCVOID(model_info + 0x298), name1, 20, 0);
                                    char name2[20];
                                    ReadProcessMemory(handle, LPCVOID(model_info + 0x2A4), name2, 20, 0);
                                    D3D9::String(image_coordinates.x + box_width / 2 + 3, image_coordinates.y - box_height / 2, g->render_thread.automobile_text_info_color, D3D9::font_small, false, fmt::format("Hash: {}\nName1: {}\nName2: {}", hash, name1, name2).c_str());
                                }
                            }
                        }
                    } 
                    if (g->render_thread.ped_esp)
                    {
                        uintptr_t list = RPM<uintptr_t>(ped + 0x100);
                        for (int i = 0, j = 0; i < ped_max_count; i++)
                        {
                            if (j == ped_current_count)
                                break;
                            uintptr_t instance = RPM<uintptr_t>(list + i * 0x10);
                            if (instance == 0)
                                continue;
                            j++;
                            if (g->render_thread.ped_esp_exclude_self && instance == local_ped)
                                continue;
                            Vector3 world_coordinates = RPM<Vector3>(instance + 0x90);
                            Vector3 image_coordinates;
                            if (WorldToScreen(world_coordinates, image_coordinates, matrix, width, height))
                            {
                                Vector3 head_world_coordinates = world_coordinates;
                                head_world_coordinates.z += 1;
                                Vector3 head_image_coordinates;
                                WorldToScreen(head_world_coordinates, head_image_coordinates, matrix, width, height);
                                int box_height = (image_coordinates.y - head_image_coordinates.y) * 2;
                                int box_width = box_height / 2.4;
                                if (g->render_thread.ped_box)
                                {
                                    D3D9::BorderedBox(image_coordinates.x - box_width / 2, image_coordinates.y - box_height / 2, box_width, box_height, 1, g->render_thread.ped_box_color);
                                    D3D9::Line(width / 2, 0, head_image_coordinates.x, head_image_coordinates.y, g->render_thread.ped_box_color);
                                }
                                if (g->render_thread.automobile_text_info)
                                {
                                    uintptr_t model_info = RPM<uintptr_t>(instance + 0x20);
                                    uint32_t hash = RPM<uint32_t>(model_info + 0x18);
                                    float health = RPM<float>(instance + 0x280);
                                    uint32_t ped_type = RPM<uint32_t>(instance + 0x10B8);
                                    ped_type = ped_type << 11 >> 25;
                                    D3D9::String(image_coordinates.x + box_width / 2 + 3, image_coordinates.y - box_height / 2, g->render_thread.ped_text_info_color, D3D9::font_small, false, fmt::format("Hash: {}\nPed Type: {}\nHealth: {}", hash, ped_type, health).c_str());
                                }
                                if (g->render_thread.ped_bone)
                                {
                                    float model_matrix[16];
                                    ReadProcessMemory(handle, LPCVOID(instance + 0x60), model_matrix, 4 * 16, 0);
                                    Vector3 bones_model_coordinates[9];
                                    Vector3 bones_world_coordinates[9];
                                    Vector3 bones_image_coordinates[9];
                                    for (int k = 0; k < 9; k++)
                                    {
                                        bones_model_coordinates[k] = RPM<Vector3>(instance + 0x430 + k * 0x10);
                                        bones_world_coordinates[k].x = bones_model_coordinates[k].x * model_matrix[0] + bones_model_coordinates[k].y * model_matrix[4] + bones_model_coordinates[k].z * model_matrix[8] + model_matrix[12];
                                        bones_world_coordinates[k].y = bones_model_coordinates[k].x * model_matrix[1] + bones_model_coordinates[k].y * model_matrix[5] + bones_model_coordinates[k].z * model_matrix[9] + model_matrix[13];
                                        bones_world_coordinates[k].z = bones_model_coordinates[k].x * model_matrix[2] + bones_model_coordinates[k].y * model_matrix[6] + bones_model_coordinates[k].z * model_matrix[10] + model_matrix[14];
                                        WorldToScreen(bones_world_coordinates[k], bones_image_coordinates[k], matrix, width, height);
                                    }
                                    D3D9::Line(bones_image_coordinates[Bone::Head].x, bones_image_coordinates[Bone::Head].y, bones_image_coordinates[Bone::Neck].x, bones_image_coordinates[Bone::Neck].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::LeftHand].x, bones_image_coordinates[Bone::LeftHand].y, bones_image_coordinates[Bone::Neck].x, bones_image_coordinates[Bone::Neck].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::RightHand].x, bones_image_coordinates[Bone::RightHand].y, bones_image_coordinates[Bone::Neck].x, bones_image_coordinates[Bone::Neck].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::Abdomen].x, bones_image_coordinates[Bone::Abdomen].y, bones_image_coordinates[Bone::Neck].x, bones_image_coordinates[Bone::Neck].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::Abdomen].x, bones_image_coordinates[Bone::Abdomen].y, bones_image_coordinates[Bone::LeftAnkle].x, bones_image_coordinates[Bone::LeftAnkle].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::Abdomen].x, bones_image_coordinates[Bone::Abdomen].y, bones_image_coordinates[Bone::RightAnkle].x, bones_image_coordinates[Bone::RightAnkle].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::RightAnkle].x, bones_image_coordinates[Bone::RightAnkle].y, bones_image_coordinates[Bone::RightToe].x, bones_image_coordinates[Bone::RightToe].y, g->render_thread.ped_bone_color);
                                    D3D9::Line(bones_image_coordinates[Bone::LeftAnkle].x, bones_image_coordinates[Bone::LeftAnkle].y, bones_image_coordinates[Bone::LeftToe].x, bones_image_coordinates[Bone::LeftToe].y, g->render_thread.ped_bone_color);
                                }
                            }
                        }
                    }
                    if (g->render_thread.pickup_esp)
                    {
                        uintptr_t list = RPM<uintptr_t>(pickup + 0x100);
                        for (int i = 0, j = 0; i < pickup_max_count; i++)
                        {
                            if (j == pickup_current_count)
                                break;
                            uintptr_t instance = RPM<uintptr_t>(list + i * 0x10);
                            if (instance == 0)
                                continue;
                            j++;
                            Vector3 world_coordinates = RPM<Vector3>(instance + 0x90);
                            Vector3 image_coordinates;
                            if (WorldToScreen(world_coordinates, image_coordinates, matrix, width, height))
                            {
                                Vector3 head_world_coordinates = world_coordinates;
                                head_world_coordinates.z += 0.5;
                                Vector3 head_image_coordinates;
                                WorldToScreen(head_world_coordinates, head_image_coordinates, matrix, width, height);
                                int box_height = (image_coordinates.y - head_image_coordinates.y) * 2;
                                int box_width = box_height / 2.4;
                                if (g->render_thread.pickup_box)
                                {
                                    D3D9::BorderedBox(image_coordinates.x - box_width / 2, image_coordinates.y - box_height / 2, box_width, box_height, 1, g->render_thread.pickup_box_color);
                                    D3D9::Line(width / 2, 0, head_image_coordinates.x, head_image_coordinates.y, g->render_thread.pickup_box_color);
                                }
                                if (g->render_thread.pickup_text_info)
                                {
                                    uintptr_t model_info = RPM<uintptr_t>(instance + 0x20);
                                    uint32_t hash = RPM<uint32_t>(model_info + 0x18);
                                    D3D9::String(image_coordinates.x + box_width / 2 + 3, image_coordinates.y - box_height / 2, g->render_thread.pickup_text_info_color, D3D9::font_small, false, fmt::format("Hash: {}", hash).c_str());
                                }
                            }
                        }
                    }
                    if (g->render_thread.object_esp)
                    {
                        uintptr_t list = RPM<uintptr_t>(object + 0x158);
                        for (int i = 0, j = 0; i < pickup_max_count; i++)
                        {
                            if (j == object_current_count)
                                break;
                            uintptr_t instance = RPM<uintptr_t>(list + i * 0x10);
                            if (instance == 0)
                                continue;
                            j++;
                            Vector3 world_coordinates = RPM<Vector3>(instance + 0x90);
                            Vector3 image_coordinates;
                            if (WorldToScreen(world_coordinates, image_coordinates, matrix, width, height))
                            {
                                Vector3 head_world_coordinates = world_coordinates;
                                head_world_coordinates.z += 0.5;
                                Vector3 head_image_coordinates;
                                WorldToScreen(head_world_coordinates, head_image_coordinates, matrix, width, height);
                                int box_height = (image_coordinates.y - head_image_coordinates.y) * 2;
                                int box_width = box_height * 2.4;
                                if (g->render_thread.object_box)
                                {
                                    D3D9::BorderedBox(image_coordinates.x - box_width / 2, image_coordinates.y - box_height / 2, box_width, box_height, 1, g->render_thread.object_box_color);
                                    D3D9::Line(width / 2, 0, head_image_coordinates.x, head_image_coordinates.y, g->render_thread.object_box_color);
                                }
                                if (g->render_thread.object_text_info)
                                {
                                    uintptr_t model_info = RPM<uintptr_t>(instance + 0x20);
                                    uint32_t hash = RPM<uint32_t>(model_info + 0x18);
                                    D3D9::String(image_coordinates.x + box_width / 2 + 3, image_coordinates.y - box_height / 2, g->render_thread.object_text_info_color, D3D9::font_small, false, fmt::format("Hash: {}", hash).c_str());
                                }
                            }
                        }
                    }
                    if (g->render_thread.player_esp)
                    {
                        for (int i = 0; i < 32; i++)
                        {
                            uintptr_t instance = RPM<uintptr_t>(player + 0xA0, { 0x1E8 });
                            if (instance == 0)
                                continue;
                            if (g->render_thread.player_esp_exclude_self && instance == local_ped)
                                continue;
                            Vector3 world_coordinates = RPM<Vector3>(instance + 0x90);
                            Vector3 image_coordinates;
                            if (WorldToScreen(world_coordinates, image_coordinates, matrix, width, height))
                            {
                                Vector3 head_world_coordinates = world_coordinates;
                                head_world_coordinates.z += 0.5;
                                Vector3 head_image_coordinates;
                                WorldToScreen(head_world_coordinates, head_image_coordinates, matrix, width, height);
                                int box_height = (image_coordinates.y - head_image_coordinates.y) * 2;
                                int box_width = box_height * 2.4;
                                if (g->render_thread.player_box)
                                {
                                    D3D9::BorderedBox(image_coordinates.x - box_width / 2, image_coordinates.y - box_height / 2, box_width, box_height, 1, g->render_thread.player_box_color);
                                    D3D9::Line(width / 2, 0, head_image_coordinates.x, head_image_coordinates.y, g->render_thread.player_box_color);
                                }
                                if (g->render_thread.player_text_info)
                                {
                                    uintptr_t model_info = RPM<uintptr_t>(instance + 0x20);
                                    uint32_t hash = RPM<uint32_t>(model_info + 0x18);
                                    D3D9::String(image_coordinates.x + box_width / 2 + 3, image_coordinates.y - box_height / 2, g->render_thread.player_text_info_color, D3D9::font_small, false, fmt::format("Id: {}\nHash: {}", i, hash).c_str());
                                }
                            }
                        }
                    }
                }
            CONTINUE:
                D3D9::d3dDevice->EndScene();
                D3D9::d3dDevice->PresentEx(0, 0, 0, 0, 0);
            }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            return 0;
        },
        0L, 0L, GetModuleHandle(NULL), NULL, NULL, CreateSolidBrush(RGB(0, 0, 0)), L"Aure's External Ovelay", L"Aure's External Ovelay", NULL};
    ::RegisterClassEx(&wc);

    RECT rect;
    GetWindowRect(target_hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HWND hwnd = ::CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, wc.lpszClassName, wc.lpszMenuName, WS_POPUP, 1, 1, width, height, nullptr, nullptr, wc.hInstance, nullptr);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOW);

    D3D9::Init(width, height, hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        RECT rect;
        GetWindowRect(target_hwnd, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

        MoveWindow(hwnd, rect.left, rect.top, width, height, true);

        D3D9::d3dparams.BackBufferWidth = width;
        D3D9::d3dparams.BackBufferHeight = height;
    }
}