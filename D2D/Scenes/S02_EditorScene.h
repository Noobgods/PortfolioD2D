#pragma once
#include "Scene.h"

class S02_EditorScene : public Scene {
public:
	S02_EditorScene(SceneValues* values);
	~S02_EditorScene();

	void Update() override;
	void Render() override;

private:
	class Background* background;
	Vector2 boxLine[BUBBLE_LINE_SIZE_Y][BUBBLE_LINE_SIZE_X];
};