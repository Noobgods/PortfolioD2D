#pragma once
#include "Scene.h"

#define BALL_LINE_SIZE_X 9
#define BALL_LINE_SIZE_Y 12

class S02_EditorScene : public Scene {
public:
	S02_EditorScene(SceneValues* values);
	~S02_EditorScene();

	void Update() override;
	void Render() override;

private:

};