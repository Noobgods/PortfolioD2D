#pragma once

class Arrow {
public:
	Arrow(Vector2 position, Vector2 scale);
	~Arrow();

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

	void FrameNumber(int val) { frameNumber = val; }
private:
	Animation* animation;
	float moveSpeed;

	bool targetLeft;
	bool targetRight;
	int frameNumber;
};