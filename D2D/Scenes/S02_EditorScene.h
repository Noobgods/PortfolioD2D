#pragma once
#include "Scene.h"

class S02_EditorScene : public Scene {
public:
	S02_EditorScene(SceneValues* values);
	~S02_EditorScene();

	void Update() override;
	void Render() override;

private:
	void EditBubble();
	void RenderImGui();
private:
	class Background* background;

	Vector2 mouse;
	Vector2 boxLine[BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];
	Rect* bubbleBox[BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];
	UINT bubbles[BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];

	int stage;
	int bubbleColor;

};