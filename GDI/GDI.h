#pragma once
class GDI
{
public:
	static const COLORREF color = 0xFF;
	inline static HBRUSH brush;
	inline static HDC hdc;
	static void DrawFilledRect(int x, int y, int w, int h);
	static void DrawBorderBox(int x, int y, int w, int h, int thickness);
	static void DrawLine(float StartX, float StartY, float EndX, float EndY);
	static void Init();
	static void Draw();
};