#include "stdafx.h"
#include "Filemanager.h"


void FileManager::Save(wstring fileName)
{
	int msg = MessageBox(Hwnd, L"Save File?", L"Save Object", MB_YESNO);

	if (msg == IDYES) {
		BinaryWriter* w = 
	}
}

void FileManager::Load(wstring fileName)
{
}

void FileManager::SetMarker(vector<Vector2>& v)
{
}

vector<Vector2>& FileManager::GetBubbles()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
}
