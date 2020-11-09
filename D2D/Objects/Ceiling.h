#pragma once

class Ceiling {
public:
	Ceiling(Vector2 position, Vector2 scale);
	~Ceiling();

	void Update(Matrix& V, Matrix& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2& position);
	void Position(D3DXVECTOR2&& position);
	D3DXVECTOR2 Position();

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& scale);
	void Scale(D3DXVECTOR2&& scale);
	D3DXVECTOR2 Scale();

	void FrameNumber(UINT val) { frameNumber = val; animation->Stop();}
	void Stage(UINT val) { currentStage = val; }
private:
	Animation *animation;

	UINT currentStage;
	UINT frameNumber;
};