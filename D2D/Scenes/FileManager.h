#pragma once

class FileManager {
public:
	static void Save(wstring fileName);
	static void Load(wstring fileName);
	static void* GetBubbles();
private:
	static UINT stageBubbles[BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];
};