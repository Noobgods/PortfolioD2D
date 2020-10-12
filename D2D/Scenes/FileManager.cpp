#include "stdafx.h"
#include "Filemanager.h"


UINT FileManager::stageBubbles[MAX_STAGE][BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];
UINT FileManager::stages;

void FileManager::Save(wstring fileName)
{
	int msg = MessageBox(Hwnd, L"Save File?", L"Save Object", MB_YESNO);

	if (msg == IDYES) {
		BinaryWriter* w = new BinaryWriter();

		string str = String::ToString(fileName);
		w->Open(fileName);

		w->UInt(MAX_STAGE);
		for (int s = 0; s < MAX_STAGE; s++)
		for (int i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
			for (int j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
				w->UInt(stageBubbles[s][i][j]);
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
	stages = r->UInt();

	for(int s= 0; s<stages; s++)
	for (int i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
		for (int j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			stageBubbles[s][i][j] = r->UInt();
		}
	}

	r->Close();
	SAFE_DELETE(r);
}

void FileManager::SetBubbles(UINT(* bubbles)[BUBBLE_LINE_SIZE_X], UINT stage)
{
	for (int i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
		for (int j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			stageBubbles[stage][i][j] = bubbles[i][j];
		}
	}
}

void* FileManager::GetBubbles(int stage)
{
	return stageBubbles[stage];
}