#include "stdafx.h"
#include "LaunchDragon.h"

LaunchDragon::LaunchDragon(Vector2 position, Vector2 scale)
	: animationSpeed(0.1f)
	, state(LDState::IDLE)
	, jumpDistance(0.f)
	, jumpSpeed(200.0f)
	, defaultPosition(position)
{
	animation = new Animation();
	animationPipe = new Animation();
	wstring spriteFile = L"./puzzleBubble.png";
	wstring shaderFile = L"Effect.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 2012, 33, 2044), animationSpeed);

		animation->AddClip(clip);
	}
	// Move
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 100, 2012, 132, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 133, 2012, 165, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 166, 2012, 198, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 2012, 231, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 2012, 264, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 265, 2012, 297, 2044), animationSpeed);
		animation->AddClip(clip);
	}
	// Wait
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 34, 2012, 66, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 67, 2012, 99, 2044), animationSpeed);

		animation->AddClip(clip);
	}
	// Hurry
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 298, 2012, 330, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 331, 2012, 363, 2044), animationSpeed);
		animation->AddClip(clip);
	}
	// Win
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 364, 2012, 396, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 397, 2012, 429, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 430, 2012, 462, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 463, 2012, 495, 2044), animationSpeed);
		animation->AddClip(clip);
	}
	animation->Position(position);
	animation->Scale(scale);
	animation->Play((UINT)state);

	/// Pipe Move
	// Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1041, 1779, 1057, 1811), animationSpeed);

		animationPipe->AddClip(clip);
	}
	// Shoot
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1058, 1779, 1074, 1811), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1075, 1779, 1091, 1811), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1092, 1779, 1108, 1811), animationSpeed);
		animationPipe->AddClip(clip);
	}
	animationPipe->Position(0.0f, position.y);
	animationPipe->Scale(scale);
	animationPipe->Play((UINT)state);
}

LaunchDragon::~LaunchDragon()
{
	SAFE_DELETE(animation);
}

void LaunchDragon::Update(Matrix & V, Matrix & P)
{
	Vector2 position = animation->Position();
	// Animation
	/// 공쏘고 공나르기
	switch (state) {
	case LDState::IDLE: {
		position = defaultPosition;
	}
	case LDState::SHOT: {
		if (animation->GetClip()->EndFrame()) {
			state = LDState::IDLE;
		}
	}break;
	case LDState::WIN: {
		position.y += jumpSpeed * Time::Delta();
		jumpDistance += jumpSpeed * Time::Delta();
		if (jumpDistance > 50.0f ) {
			jumpSpeed = -200.0f ;
		}
		if (jumpDistance < 0) {
			jumpSpeed = 200.0f;
		}
		
	}break;
	}
	
	animation->Position(position);
	animation->Play((UINT)state);
	animation->Update(V, P);

	// Animation Pipe
	animationPipe->Play((UINT)((UINT)state < 2 ? state : LDState::IDLE));
	animationPipe->Update(V, P);
}

void LaunchDragon::Render()
{
	animationPipe->Render();
	animation->Render();
}

void LaunchDragon::ShootBubble()
{
	state = LDState::SHOT;
	animation->Play((UINT)LDState::SHOT);
}

void LaunchDragon::ClearStage()
{
	state = LDState::WIN;
	animation->Play((UINT)LDState::WIN);
}
void LaunchDragon::ReadyStage()
{
	state = LDState::IDLE;
}

