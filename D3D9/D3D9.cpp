void D3D9::Init(int width, int height, HWND hwnd)
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

	D3DXCreateFont(d3dDevice, 24, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Microsoft YaHei", &font_big);
	D3DXCreateFont(d3dDevice, 16, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Microsoft YaHei", &font_small);
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