#pragma once
class FileManager {
public:
	static void Save(wstring fileName);
	static void Load(wstring fileName);
	static void SetBubbles(UINT(* bubbles)[BUBBLE_LINE_SIZE_X], UINT stage);
	static void* GetBubbles(int stage);
private:
	static UINT stages;
	static UINT stageBubbles[MAX_STAGE][BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];
};