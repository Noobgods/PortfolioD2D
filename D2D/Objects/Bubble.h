#pragma once

// Ball State
enum class BState {
	SPAWN =0, NEXT, MOVEREADY, READY, SHOT, IDLE, BURST, INAIR, DEL, GAMEOVER
};
// Animation State
enum class AState {
	IDLE = 0, BLINK, BORING, BURST, GAMEOVER
};
class Bubble {
public:
	Bubble(Vector2 position, Vector2 scale, UINT color);
	~Bubble();

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

	void shootBubble(float angle);

	void BubbleState(BState state);
	BState BubbleState() { return bubbleState; }

	Collider* getCollider() { return collider; }
	UINT GetBubbleColor() { return bubbleColor; }

	Matrix World();
private:
	Animation* animation;

	Vector2 shotSpeed;

	float animationSpeed;
	float bubbleAngle;
	float bubbleSpeed;
	float bubbleDistance;
	UINT bubbleColor;

	BState bubbleState;
	AState animationState;

	Collider* collider;
};