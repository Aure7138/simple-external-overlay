#pragma once
#define WHITE(alpha)         D3DCOLOR_ARGB(alpha, 255, 255, 255)
#define BLACK(alpha)         D3DCOLOR_ARGB(alpha, 0, 0, 0)
#define RED(alpha)           D3DCOLOR_ARGB(alpha, 255, 0, 0)
#define GREEN(alpha)         D3DCOLOR_ARGB(alpha, 0, 128, 0)
#define LAWNGREEN(alpha)     D3DCOLOR_ARGB(alpha, 124, 252, 0)
#define BLUE(alpha)          D3DCOLOR_ARGB(alpha, 0, 200, 255)
#define DEEPSKYBLUE(alpha)   D3DCOLOR_ARGB(alpha, 0, 191, 255)
#define SKYBLUE(alpha)       D3DCOLOR_ARGB(alpha, 0, 122, 204)
#define YELLOW(alpha)        D3DCOLOR_ARGB(alpha, 255, 255, 0)
#define ORANGE(alpha)        D3DCOLOR_ARGB(alpha, 255, 165, 0)
#define DARKORANGE(alpha)    D3DCOLOR_ARGB(alpha, 255, 140, 0)
#define PURPLE(alpha)        D3DCOLOR_ARGB(alpha, 125, 0, 255)
#define CYAN(alpha)          D3DCOLOR_ARGB(alpha, 0, 255, 255)
#define PINK(alpha)          D3DCOLOR_ARGB(alpha, 255, 20, 147)
#define GRAY(alpha)          D3DCOLOR_ARGB(alpha, 128, 128, 128)
#define DARKGRAY(alpha)      D3DCOLOR_ARGB(alpha, 73, 73, 73)
#define DARKERGRAY(alpha)    D3DCOLOR_ARGB(alpha, 31, 31, 31)
class D3D9
{
public:
	static void Init(int width, int height, HWND hwnd);
public:
	inline static IDirect3D9Ex* d3dObject{};
	inline static IDirect3DDevice9Ex* d3dDevice{};
	inline static D3DPRESENT_PARAMETERS d3dparams{};
	inline static ID3DXFont* font_big{};
	inline static ID3DXFont* font_small{};
	static void String(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, const char* string, ...);
	static int StringWidth(ID3DXFont* font, const char* string);
	static void StringW(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, const wchar_t* string, ...);
	static int StringWidthW(ID3DXFont* font, const wchar_t* string);
	static void Line(int x, int y, int x2, int y2, D3DCOLOR colour);
	static void FilledBox(int x, int y, int width, int height, D3DCOLOR colour);
	static void FilledBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR outlinecolor);
	static void BorderedBox(int x, int y, int width, int height, int thickness, D3DCOLOR colour);
	static void BorderedBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR outlinecolor);
	static void GradientBox(int x, int y, int width, int height, D3DCOLOR colour, D3DCOLOR color2, bool vertical);
	static void GradientBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR color2, D3DCOLOR outlinecolor, bool vertical);
	static void Circle(int x, int y, int radius, int points, D3DCOLOR colour);
	static void FilledCircle(int x, int y, int radius, int points, D3DCOLOR colour);
	static int FrameRate();
public:
	struct SD3DVertex {
		float x, y, z, rhw;
		DWORD colour;
	};
};