void GDI::DrawFilledRect(int x, int y, int w, int h)
{
	RECT rect{ x,y,x + w,y + h };
	FillRect(hdc, &rect, brush);
}
void GDI::DrawBorderBox(int x, int y, int w, int h, int thickness)
{
	DrawFilledRect(x, y, w, thickness);
	DrawFilledRect(x, y, thickness, h);
	DrawFilledRect(x + w, y, thickness, h);
	DrawFilledRect(x, y + h, w + thickness, thickness);
}
void GDI::DrawLine(float StartX, float StartY, float EndX, float EndY)
{
	int a, b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, 2, color);
	hOPen = (HPEN)SelectObject(hdc, hNPen);
	MoveToEx(hdc, StartX, StartY, NULL);
	a = LineTo(hdc, EndX, EndY);
	DeleteObject(SelectObject(hdc, hOPen));
}
void GDI::Init()
{
	brush = CreateSolidBrush(color);
	hdc = GetDC(FindWindowA("grcWindow", 0));
}