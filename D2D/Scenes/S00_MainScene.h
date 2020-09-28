#pragma once
#include "Scene.h"

class S00_MainScene : public Scene {
public:
	S00_MainScene(SceneValues* values);
	~S00_MainScene();

	void Update() override;
	void Render() override;

private:

};