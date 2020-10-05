#pragma once

class FileManager {
public:
	static void Save(wstring fileName);
	static void Load(wstring fileName);
	static void SetMarker(vector<Vector2>& v);
	static vector<Vector2>& GetBubbles();

private:
	static int stageBubbles[BUBBLE_LINE_SIZE_X][BUBBLE_LINE_SIZE_Y];
};