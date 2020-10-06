#include "stdafx.h"
#include "Filemanager.h"


UINT FileManager::stageBubbles[BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];

void FileManager::Save(wstring fileName)
{
	int msg = MessageBox(Hwnd, L"Save File?", L"Save Object", MB_YESNO);

	if (msg == IDYES) {
		BinaryWriter* w = new BinaryWriter();

		string str = String::ToString(fileName);
		w->Open(fileName);

		for (int i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
			for (int j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
				w->UInt(stageBubbles[i][j]);
			}
		}

		w->Close();
		SAFE_DELETE(w);

		memset(stageBubbles, 0, sizeof(stageBubbles));
		wstring temp = L"\n 저장이 완료되었습니다.";
		MessageBox(Hwnd, temp.c_str(), L"저장완료", MB_OK);
	}
}

void FileManager::Load(wstring fileName)
{
	BinaryReader* r = new BinaryReader();

	if (Path::ExistFile(fileName) == true)
		r->Open(fileName);
	else
		assert(false);

	memset(stageBubbles, 0, sizeof(stageBubbles));

	for (int i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
		for (int j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			stageBubbles[i][j] = r->UInt();
		}
	}

	r->Close();
	SAFE_DELETE(r);
}

void* FileManager::GetBubbles()
{
	return stageBubbles;
}