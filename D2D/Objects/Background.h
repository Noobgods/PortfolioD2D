#pragma once

class Background {
public:
	Background(Vector2 position, Vector2 scale);
	~Background();

	void Update(Matrix& V, Matrix& P);
	void Render();

	void Stage(UINT val) { currentStage = val; }

private:
	vector<Sprite*> stages;
	vector<Sprite*> stageWalls;
	UINT currentStage;
};