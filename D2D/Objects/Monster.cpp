#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Vector2 position, Vector2 scale, UINT color)
	: monsterColor(color)
	, animationSpeed(0.1f)
	, fallSpeed(300.0f)
	, fallDirection(-1.0f)
	, gravity(-800.0f)
	, state(MState::FALL)
{
	animation = new Animation();

	wstring spriteFile = L"./puzzleBubble.png";
	wstring shaderFile = L"Effect.fx";

	Clip* clip;
	switch (monsterColor) {
	/// 파란색
	case 1: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 402, 1854, 418, 1870), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 419, 1854, 435, 1870), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 436, 1854, 452, 1870), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 453, 1854, 469, 1870), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	/// 노란색
	case 2: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 956, 1854, 972, 1870), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 973, 1854, 989, 1870), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 990, 1854, 1006, 1870), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 1007, 1854, 1023, 1870), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	/// 빨간색
	case 3: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 402, 1887, 418, 1903), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 419, 1887, 435, 1903), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 436, 1887, 452, 1903), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 453, 1887, 469, 1903), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	/// 녹색
	case 4: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 956, 1887, 972, 1903), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 973, 1887, 989, 1903), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 990, 1887, 1006, 1903), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 1007, 1887, 1023, 1903), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	/// 보라색
	case 5: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 402, 1920, 418, 1936), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 419, 1920, 435, 1936), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 436, 1920, 452, 1936), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 453, 1920, 469, 1936), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	/// 주황색
	case 6: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 956, 1920, 972, 1936), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 973, 1920, 989, 1936), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 990, 1920, 1006, 1936), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 1007, 1920, 1023, 1936), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	// 검정색
	case 7: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 402, 1953, 418, 1969), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 419, 1953, 435, 1969), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 436, 1953, 452, 1969), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 453, 1953, 469, 1969), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	/// 흰색
	case 8: {
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 956, 1953, 972, 1969), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 973, 1953, 989, 1969), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 990, 1953, 1006, 1969), animationSpeed);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 1007, 1953, 1023, 1969), animationSpeed);
			animation->AddClip(clip);
		}
	}break;
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	fallDirection += (float)((Math::Random(0, 1)) * 2.0f);
}

Monster::~Monster()
{
	SAFE_DELETE(animation);
}

void Monster::Update(Matrix & V, Matrix & P)
{
	Vector2 position = animation->Position();
	fallSpeed += gravity * Time::Delta();
	position.y += fallSpeed * Time::Delta();
	position.x += fallDirection * 20.f * Time::Delta();
	if (position.y < -360.0f) {
		state = MState::DEL;
	}

	animation->Position(position);
	animation->Play(0);
	animation->Update(V, P);
}

void Monster::Render()
{
	animation->Render();
}
