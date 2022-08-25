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
	inline static LPCWSTR window_class = L"Aure's External Ovelay";
	inline static LPCWSTR window_name = L"Aure's External Ovelay";
	inline static WNDCLASSEX wc;
	inline static HWND hwnd;
	inline static LPCWSTR target_window_class = L"grcWindow";
	inline static LPCWSTR target_window_name = NULL;
	inline static HWND target_hwnd;
	inline static int width, height;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static void Init();
	static int Loop();
public:
	inline static IDirect3D9Ex* d3dObject{};
	inline static IDirect3DDevice9Ex* d3dDevice{};
	inline static D3DPRESENT_PARAMETERS d3dparams{};
	inline static ID3DXFont* d3dFont{};
	inline static ID3DXFont* pFontVisualsLarge{};
	inline static ID3DXFont* pFontVisualsSmall{};
	inline static ID3DXFont* pFontUILarge{};
	inline static ID3DXFont* pFontUISmall{};
	inline static ID3DXFont* font_big{};
	inline static ID3DXFont* font_small{};
	static void D3D9Init();
	static int Render();
	static void String(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, const char* string, ...);
	static int StringWidth(ID3DXFont* font, const char* string);
	static void drawText(const char* String, int x, int y, int a, int r, int g, int b);
	static void StringW(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, const wchar_t* string, ...);
	static int StringWidthW(ID3DXFont* font, const wchar_t* string);
	static void drawTextW(const wchar_t* String, int x, int y, int a, int r, int g, int b);
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
	
	struct SD3DVertex {
		float x, y, z, rhw;
		DWORD colour;
	};
public:
	// 255, 171, 0, 182
	// 197, 66, 244, 255
	// 255, 255, 255, 255
	inline static bool enable_esp = true;
	inline static bool render_only_in_game = false;
	inline static bool text_info = true;
	inline static D3DCOLOR text_info_color = D3DCOLOR_RGBA(255, 255, 0, 255);

	inline static bool cautomobile_esp = false;
	inline static bool cautomobile_box = true;
	inline static D3DCOLOR cautomobile_box_color = WHITE(255);
	inline static bool cautomobile_text_info = true;
	inline static D3DCOLOR cautomobile_text_info_color = WHITE(255);

	inline static bool cped_esp = true;
	inline static bool cped_esp_exclude_self = true;
	inline static bool cped_box = true;
	inline static D3DCOLOR cped_box_color = WHITE(255);
	inline static bool cped_text_info = true;
	inline static D3DCOLOR cped_text_info_color = WHITE(255);
	inline static bool cped_bone = true;
	inline static D3DCOLOR cped_bone_color = WHITE(255);

	inline static bool cpickup_esp = false;
	inline static bool cpickup_box = true;
	inline static D3DCOLOR cpickup_box_color = WHITE(255);
	inline static bool cpickup_text_info = true;
	inline static D3DCOLOR cpickup_text_info_color = WHITE(255);

	inline static bool cobject_esp = false;
	inline static bool cobject_box = true;
	inline static D3DCOLOR cobject_box_color = WHITE(255);
	inline static bool cobject_text_info = true;
	inline static D3DCOLOR cobject_text_info_color = WHITE(255);

	inline static bool player_esp = false;
	inline static bool player_esp_exclude_self = true;
	inline static bool player_box = true;
	inline static D3DCOLOR player_box_color = WHITE(255);
	inline static bool player_text_info = true;
	inline static D3DCOLOR player_text_info_color = WHITE(255);
	
};