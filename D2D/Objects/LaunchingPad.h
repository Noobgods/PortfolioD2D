#pragma once

//Spinning dragon State
enum class SDState {
	IDLE = 0, SPIN, BORING1, BORING2, CLEAR
};
class LaunchingPad {
public:
	LaunchingPad(Vector2 position, Vector2 scale);
	~LaunchingPad();

	void Update(Matrix& V, Matrix& P);
	void Render();

	void FrameNumber(UINT val) { frameNumber = val; }
	void State(SDState state) { spinState = state; }
private:
	Animation* animation_Pad;
	Animation* animation_Turn;
	Animation* animation_SpinDragon;

	SDState spinState;
	Vector2 defaultPosition;
	UINT frameNumber;
	float animationSpeed;
	float moveSpeed;
	float moveDistance;

	bool targetLeft;
	bool targetRight;

};