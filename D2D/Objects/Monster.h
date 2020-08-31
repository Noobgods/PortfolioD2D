#pragma once

enum class MState {
	FALL = 0, DEL
};
class Monster {
public:
	Monster(Vector2 position, Vector2 scale, UINT color);
	~Monster();

	void Update(Matrix& V, Matrix& P);
	void Render();
	
	MState State() { return state; }

private:
	Animation* animation;

	UINT monsterColor;

	float animationSpeed;
	float fallSpeed;
	float fallDirection;
	float gravity;

	MState state;
};