#pragma once

//Launching Dragon State
enum class LDState {
	IDLE = 0, SHOT, WAIT, HURRY, WIN
};
class LaunchDragon {
public:
	LaunchDragon(Vector2 position, Vector2 scale);
	~LaunchDragon();

	void Update(Matrix& V, Matrix& P);
	void Render();

	void ShootBubble();
	void ClearStage();
	void ReadyStage();
private:
	Animation* animation;
	Animation* animationPipe;
	
	LDState state;
	Vector2 defaultPosition;

	float animationSpeed;
	float jumpDistance;
	float jumpSpeed;
};