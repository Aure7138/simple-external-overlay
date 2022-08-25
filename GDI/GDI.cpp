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
void GDI::Draw()
{
	for (size_t i = 0; i < peds.size(); i++)
	{
		Ped& ped = peds[i];
		if (ped.is_world_to_screen_success)
		{
			DrawLine(ped.bones_image_coordinates[Bone::Head].x, ped.bones_image_coordinates[Bone::Head].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y);
			DrawLine(ped.bones_image_coordinates[Bone::LeftHand].x, ped.bones_image_coordinates[Bone::LeftHand].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y);
			DrawLine(ped.bones_image_coordinates[Bone::RightHand].x, ped.bones_image_coordinates[Bone::RightHand].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y);
			DrawLine(ped.bones_image_coordinates[Bone::Abdomen].x, ped.bones_image_coordinates[Bone::Abdomen].y, ped.bones_image_coordinates[Bone::Neck].x, ped.bones_image_coordinates[Bone::Neck].y);
			DrawLine(ped.bones_image_coordinates[Bone::Abdomen].x, ped.bones_image_coordinates[Bone::Abdomen].y, ped.bones_image_coordinates[Bone::LeftAnkle].x, ped.bones_image_coordinates[Bone::LeftAnkle].y);
			DrawLine(ped.bones_image_coordinates[Bone::Abdomen].x, ped.bones_image_coordinates[Bone::Abdomen].y, ped.bones_image_coordinates[Bone::RightAnkle].x, ped.bones_image_coordinates[Bone::RightAnkle].y);
			DrawLine(ped.bones_image_coordinates[Bone::RightAnkle].x, ped.bones_image_coordinates[Bone::RightAnkle].y, ped.bones_image_coordinates[Bone::RightToe].x, ped.bones_image_coordinates[Bone::RightToe].y);
			DrawLine(ped.bones_image_coordinates[Bone::LeftAnkle].x, ped.bones_image_coordinates[Bone::LeftAnkle].y, ped.bones_image_coordinates[Bone::LeftToe].x, ped.bones_image_coordinates[Bone::LeftToe].y);
		}
	}
}