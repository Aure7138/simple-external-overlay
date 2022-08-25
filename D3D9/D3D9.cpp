LRESULT CALLBACK D3D9::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_PAINT:
        Render();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void D3D9::Init()
{
    wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, CreateSolidBrush(RGB(0, 0, 0)), window_name, window_class, NULL };
    ::RegisterClassEx(&wc);

    target_hwnd = FindWindow(target_window_class, target_window_name);

    RECT rect;
    GetWindowRect(target_hwnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    hwnd = ::CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, window_class, window_name, WS_POPUP, 1, 1, width, height, nullptr, nullptr, wc.hInstance, nullptr);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOW);

    D3D9Init();

	Loop();
}

int D3D9::Loop()
{
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        RECT rect;
        GetWindowRect(target_hwnd, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

        MoveWindow(hwnd, rect.left, rect.top, width, height, true);
    }
	return (int)msg.wParam;
}

void D3D9::D3D9Init()
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &d3dObject))) {
        exit(1);
    }
    ZeroMemory(&d3dparams, sizeof(d3dparams));
    d3dparams.BackBufferWidth = width;
    d3dparams.BackBufferHeight = height;
    d3dparams.Windowed = TRUE;
    d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dparams.hDeviceWindow = hwnd;
    d3dparams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    d3dparams.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dparams.EnableAutoDepthStencil = TRUE;
    d3dparams.AutoDepthStencilFormat = D3DFMT_D16;
    HRESULT res = d3dObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dparams, 0, &d3dDevice);
    if (FAILED(res)) {
        std::wstring ws(DXGetErrorString(res));
        std::string str(ws.begin(), ws.end());
        std::wstring ws2(DXGetErrorDescription(res));
        std::string str2(ws2.begin(), ws2.end());
        std::string error = "Error: " + str + " error description: " + str2;
        exit(1);
    }
    D3DXCreateFont(d3dDevice, 18, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Comic Sans", &d3dFont);

	D3DXCreateFont(d3dDevice, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Tahoma", &pFontVisualsLarge);
	D3DXCreateFont(d3dDevice, 16, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Tahoma", &pFontVisualsSmall);

	D3DXCreateFont(d3dDevice, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Tahoma", &pFontUILarge);
	D3DXCreateFont(d3dDevice, 16, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Tahoma", &pFontUISmall);

	D3DXCreateFont(d3dDevice, 24, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Microsoft YaHei", &font_big);
	D3DXCreateFont(d3dDevice, 16, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Microsoft YaHei", &font_small);
}

int D3D9::Render()
{
    if (d3dDevice == nullptr)
        return 1;
    d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
    d3dDevice->BeginScene();

	if(!enable_esp)
		goto CONTINUE;

	if (target_hwnd != GetForegroundWindow() && render_only_in_game)
		goto CONTINUE;

	update_data();
	update_automobiles();
	update_peds();
	update_pickups();
	update_objects();
	update_players();

	if (text_info)
	{
		StringW(10, height / 3, text_info_color, font_big, false, fmt::format(L"Frame Rate: {}\nCAutomobile Pool: {}/{}\nCPed Pool: {}/{}\nCPickup Pool: {}/{}\nCObject Pool: {}/{}\nOnline Player: {}/32", FrameRate(), CAutombileCurrentCount, CAutombileMaxCount, CPedCurrentCount, CPedMaxCount, CPickupCurrentCount, CPickupMaxCount, CObjectCurrentCount, CObjectMaxCount, players.size()).c_str());
	}
	if (cautomobile_esp)
	{
		for (size_t i = 0; i < automobiles.size(); i++)
		{
			Automobile& automobile = automobiles[i];
			if (automobile.is_world_to_screen_success)
			{
				if (cautomobile_box)
				{
					int box_height = (automobile.image_coordinates.y - automobile.image_head_coordinates.y) * 2;
					int box_width = box_height * 2.4;
					BorderedBox(automobile.image_coordinates.x - box_width / 2, automobile.image_coordinates.y - box_height / 2, box_width, box_height, 1, cautomobile_box_color);
					Line(D3D9::width / 2, 0, automobile.image_head_coordinates.x, automobile.image_head_coordinates.y, cautomobile_box_color);
				}
				if (cautomobile_text_info)
				{
					int box_height = (automobile.image_coordinates.y - automobile.image_head_coordinates.y) * 2;
					int box_width = box_height * 2.4;
					String(automobile.image_coordinates.x + box_width / 2, automobile.image_coordinates.y - box_height / 2, cautomobile_text_info_color, font_small, false, fmt::format("Hash: {}\nName1: {}\nName2: {}", automobile.hash, automobile.name1, automobile.name2).c_str());
				}
			}
		}
	}
	if (cped_esp)
	{
		for (size_t i = 0; i < peds.size(); i++)
		{
			Ped& ped = peds[i];
			if (ped.is_world_to_screen_success)
			{
				if (cped_esp_exclude_self && ped.instance == local_cped) continue;

				if (cped_box)
				{
					int box_height = (ped.image_coordinates.y - ped.image_head_coordinates.y) * 2;
					int box_width = box_height / 2.4;
					BorderedBox(ped.image_coordinates.x - box_width / 2, ped.image_coordinates.y - box_height / 2, box_width, box_height, 1, cped_box_color);
					Line(D3D9::width / 2, 0, ped.image_head_coordinates.x, ped.image_head_coordinates.y, cped_box_color);
				}
				if (cped_text_info)
				{
					int box_height = (ped.image_coordinates.y - ped.image_head_coordinates.y) * 2;
					int box_width = box_height / 2.4;
					String(ped.image_coordinates.x + box_width / 2, ped.image_coordinates.y - box_height / 2, cped_text_info_color, font_small, false, fmt::format("Hash: {}\nPed Type: {}\nHealth: {}", ped.hash, ped.ped_type, ped.health).c_str());
				}
				if (cped_bone)
				{
					Line(ped.bones_image_coordinates[Bone::Head].x, ped.bones_image_coordinates[Bone::Head].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::LeftHand].x, ped.bones_image_coordinates[Bone::LeftHand].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::RightHand].x, ped.bones_image_coordinates[Bone::RightHand].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::Abdomen].x, ped.bones_image_coordinates[Bone::Abdomen].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::Abdomen].x, ped.bones_image_coordinates[Bone::Abdomen].y, ped.bones_image_coordinates[Bone::LeftAnkle].x, ped.bones_image_coordinates[Bone::LeftAnkle].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::Abdomen].x, ped.bones_image_coordinates[Bone::Abdomen].y, ped.bones_image_coordinates[Bone::RightAnkle].x, ped.bones_image_coordinates[Bone::RightAnkle].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::RightAnkle].x, ped.bones_image_coordinates[Bone::RightAnkle].y, ped.bones_image_coordinates[Bone::RightToe].x, ped.bones_image_coordinates[Bone::RightToe].y, cped_bone_color);
					Line(ped.bones_image_coordinates[Bone::LeftAnkle].x, ped.bones_image_coordinates[Bone::LeftAnkle].y, ped.bones_image_coordinates[Bone::LeftToe].x, ped.bones_image_coordinates[Bone::LeftToe].y, cped_bone_color);
				}
			}
		}
	}
	if (cpickup_esp)
	{
		for (size_t i = 0; i < pickups.size(); i++)
		{
			Pickup& pickup = pickups[i];
			if (pickup.is_world_to_screen_success)
			{
				if (cpickup_box)
				{
					int box_height = (pickup.image_coordinates.y - pickup.image_head_coordinates.y) * 2;
					int box_width = box_height / 2.4;
					BorderedBox(pickup.image_coordinates.x - box_width / 2, pickup.image_coordinates.y - box_height / 2, box_width, box_height, 1, cpickup_box_color);
					Line(D3D9::width / 2, 0, pickup.image_head_coordinates.x, pickup.image_head_coordinates.y, cpickup_box_color);
				}
				if (cpickup_text_info)
				{
					int box_height = (pickup.image_coordinates.y - pickup.image_head_coordinates.y) * 2;
					int box_width = box_height / 2.4;
					String(pickup.image_coordinates.x + box_width / 2, pickup.image_coordinates.y - box_height / 2, cpickup_text_info_color, font_small, false, fmt::format("Hash: {}", pickup.hash).c_str());
				}
			}
		}
	}
	if (cobject_esp)
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			Object& object = objects[i];
			if (object.is_world_to_screen_success)
			{
				if (cobject_box)
				{
					int box_height = (object.image_coordinates.y - object.image_head_coordinates.y) * 2;
					int box_width = box_height * 2.4;
					BorderedBox(object.image_coordinates.x - box_width / 2, object.image_coordinates.y - box_height / 2, box_width, box_height, 1, cobject_box_color);
					Line(D3D9::width / 2, 0, object.image_head_coordinates.x, object.image_head_coordinates.y, cobject_box_color);
				}
				if (cobject_text_info)
				{
					int box_height = (object.image_coordinates.y - object.image_head_coordinates.y) * 2;
					int box_width = box_height * 2.4;
					String(object.image_coordinates.x + box_width / 2, object.image_coordinates.y - box_height / 2, cobject_text_info_color, font_small, false, fmt::format("Hash: {}", object.hash).c_str());
				}
			}
		}
	}
	if (player_esp)
	{
		for (size_t i = 0; i < players.size(); i++)
		{
			Player& player = players[i];
			if (player.is_world_to_screen_success)
			{
				if (player_esp_exclude_self && player.instance == local_cped) continue;

				if (player_box)
				{
					int box_height = (player.image_coordinates.y - player.image_head_coordinates.y) * 2;
					int box_width = box_height / 2.4;
					BorderedBox(player.image_coordinates.x - box_width / 2, player.image_coordinates.y - box_height / 2, box_width, box_height, 1, player_box_color);
					Line(D3D9::width / 2, 0, player.image_head_coordinates.x, player.image_head_coordinates.y, player_box_color);
				}
				if (player_text_info)
				{
					int box_height = (player.image_coordinates.y - player.image_head_coordinates.y) * 2;
					int box_width = box_height / 2.4;
					String(player.image_coordinates.x + box_width / 2, player.image_coordinates.y - box_height / 2, player_text_info_color, font_small, false, fmt::format("Id: {}\nHash: {}", player.id, player.hash).c_str());
				}
			}
		}
	}
	CONTINUE:
    d3dDevice->EndScene();
    d3dDevice->PresentEx(0, 0, 0, 0, 0);
}

void D3D9::String(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, const char* string, ...) {
	va_list args;
	char cBuffer[256];

	va_start(args, string);
	vsprintf_s(cBuffer, string, args);
	va_end(args);

	RECT pRect;
	if (outlined) {
		pRect.left = x - 1;
		pRect.top = y;
		font->DrawTextA(NULL, cBuffer, strlen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
		pRect.left = x + 1;
		pRect.top = y;
		font->DrawTextA(NULL, cBuffer, strlen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
		pRect.left = x;
		pRect.top = y - 1;
		font->DrawTextA(NULL, cBuffer, strlen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
		pRect.left = x;
		pRect.top = y + 1;
		font->DrawTextA(NULL, cBuffer, strlen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
	}
	pRect.left = x;
	pRect.top = y;
	font->DrawTextA(NULL, cBuffer, strlen(cBuffer), &pRect, DT_NOCLIP, colour);
}

int D3D9::StringWidth(ID3DXFont* font, const char* string) {
	RECT pRect = RECT();
	font->DrawTextA(NULL, string, strlen(string), &pRect, DT_CALCRECT, D3DCOLOR_RGBA(0, 0, 0, 0));
	return pRect.right - pRect.left;
}

void D3D9::drawText(const char* String, int x, int y, int a, int r, int g, int b)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	d3dFont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}

void D3D9::StringW(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, const wchar_t* string, ...)
{
	va_list args;
	wchar_t cBuffer[256];

	va_start(args, string);
	vswprintf_s(cBuffer, string, args);
	va_end(args);

	RECT pRect;
	if (outlined) {
		pRect.left = x - 1;
		pRect.top = y;
		font->DrawText(NULL, cBuffer, wcslen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
		pRect.left = x + 1;
		pRect.top = y;
		font->DrawText(NULL, cBuffer, wcslen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
		pRect.left = x;
		pRect.top = y - 1;
		font->DrawText(NULL, cBuffer, wcslen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
		pRect.left = x;
		pRect.top = y + 1;
		font->DrawText(NULL, cBuffer, wcslen(cBuffer), &pRect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, 255));
	}
	pRect.left = x;
	pRect.top = y;
	font->DrawText(NULL, cBuffer, wcslen(cBuffer), &pRect, DT_NOCLIP, colour);
}

int D3D9::StringWidthW(ID3DXFont* font, const wchar_t* string)
{
	RECT pRect = RECT();
	font->DrawText(NULL, string, wcslen(string), &pRect, DT_CALCRECT, D3DCOLOR_RGBA(0, 0, 0, 0));
	return pRect.right - pRect.left;
}

void D3D9::drawTextW(const wchar_t* String, int x, int y, int a, int r, int g, int b)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	d3dFont->DrawText(0, String, wcslen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}

void D3D9::Line(int x, int y, int x2, int y2, D3DCOLOR colour) {
	SD3DVertex pVertex[2] = { { x, y, 0.0f, 1.0f, colour }, { x2, y2, 0.0f, 1.0f, colour } };
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &pVertex, sizeof(SD3DVertex));
}

void D3D9::FilledBox(int x, int y, int width, int height, D3DCOLOR colour) {
	SD3DVertex pVertex[4] = { { x, y + height, 0.0f, 1.0f, colour }, { x, y, 0.0f, 1.0f, colour }, { x + width, y + height, 0.0f, 1.0f, colour }, { x + width, y, 0.0f, 1.0f, colour } };
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(SD3DVertex));
}

void D3D9::FilledBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR outlinecolor) {
	BorderedBox(x, y, width, height, thickness, outlinecolor);
	FilledBox(x + thickness, y + thickness, width - (thickness * 2), height - (thickness * 2), colour);
}

void D3D9::BorderedBox(int x, int y, int width, int height, int thickness, D3DCOLOR colour) {
	FilledBox(x, y, width, thickness, colour);
	FilledBox(x, y, thickness, height, colour);
	FilledBox(x + width - thickness, y, thickness, height, colour);
	FilledBox(x, y + height - thickness, width, thickness, colour);
}

void D3D9::BorderedBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR outlinecolor) {
	BorderedBox(x, y, width, height, thickness, outlinecolor);
	BorderedBox(x + thickness, y + thickness, width - (thickness * 2), height - (thickness * 2), thickness, colour);
	BorderedBox(x + (thickness * 2), y + (thickness * 2), width - (thickness * 4), height - (thickness * 4), thickness, outlinecolor);
}

void D3D9::GradientBox(int x, int y, int width, int height, D3DCOLOR colour, D3DCOLOR color2, bool vertical) {
	SD3DVertex pVertex[4] = { { x, y, 0.0f, 1.0f, colour }, { x + width, y, 0.0f, 1.0f, vertical ? colour : color2 }, { x, y + height, 0.0f, 1.0f, vertical ? color2 : colour }, { x + width, y + height, 0.0f, 1.0f, color2 } };
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(SD3DVertex));
}

void D3D9::GradientBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR color2, D3DCOLOR outlinecolor, bool vertical) {
	BorderedBox(x, y, width, height, thickness, outlinecolor);
	GradientBox(x + thickness, y + thickness, width - (thickness * 2), height - (thickness * 2), colour, color2, vertical);
}

void D3D9::Circle(int x, int y, int radius, int points, D3DCOLOR colour) {
	SD3DVertex* pVertex = new SD3DVertex[points + 1];
	for (int i = 0; i <= points; i++) pVertex[i] = { x + radius * cos(D3DX_PI * (i / (points / 2.0f))), y - radius * sin(D3DX_PI * (i / (points / 2.0f))), 0.0f, 1.0f, colour };
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, points, pVertex, sizeof(SD3DVertex));
	delete[] pVertex;
}

void D3D9::FilledCircle(int x, int y, int radius, int points, D3DCOLOR colour) {
	SD3DVertex* pVertex = new SD3DVertex[points + 1];
	for (int i = 0; i <= points; i++) pVertex[i] = { x + radius * cos(D3DX_PI * (i / (points / 2.0f))), y + radius * sin(D3DX_PI * (i / (points / 2.0f))), 0.0f, 1.0f, colour };
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, points, pVertex, sizeof(SD3DVertex));
	delete[] pVertex;
}

int D3D9::FrameRate() {
	static int iFps, iLastFps;
	static float flLastTickCount, flTickCount;
	flTickCount = clock() * 0.001f;
	iFps++;
	if ((flTickCount - flLastTickCount) >= 1.0f) {
		flLastTickCount = flTickCount;
		iLastFps = iFps;
		iFps = 0;
	}
	return iLastFps;
}