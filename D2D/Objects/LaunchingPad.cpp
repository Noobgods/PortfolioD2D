#include "stdafx.h"
#include "LaunchingPad.h"

LaunchingPad::LaunchingPad(Vector2 position, Vector2 scale)
	: defaultPosition(position)
	, animationSpeed(0.1f)
	, frameNumber(0)
	, moveSpeed(200.0f)
	, moveDistance(0.0f)
	, spinState(SDState::IDLE)
	, targetLeft(false)
	, targetRight(false)
{
	animation_Pad = new Animation();
	animation_Turn = new Animation();
	animation_SpinDragon = new Animation();

	wstring spriteFile = L"./puzzleBubble.png";
	wstring shaderFile = L"Effect.fx";

	Clip* clip;
	// 발사대
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1805, 65, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 66, 1805, 130, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 1805, 195, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 196, 1805, 260, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 261, 1805, 325, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 326, 1805, 390, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 391, 1805, 455, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 456, 1805, 520, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 521, 1805, 585, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 586, 1805, 650, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 651, 1805, 715, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 716, 1805, 780, 1845), animationSpeed);

		animation_Pad->AddClip(clip);
	}
	animation_Pad->Position(position);
	animation_Pad->Scale(scale);
	animation_Pad->Play(0);
	animation_Pad->Stop();

	// 발사대 돌리는 거
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1041, 1812, 1057, 1828), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1058, 1812, 1074, 1828), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1075, 1812, 1091, 1828), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1092, 1812, 1108, 1828), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1041, 1829, 1057, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1058, 1829, 1074, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1075, 1829, 1091, 1845), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1092, 1829, 1108, 1845), animationSpeed);

		animation_Turn->AddClip(clip);
	}

	animation_Turn->Position(Vector2(position.x + 100.0f, position.y - 48.0f));
	animation_Turn->Scale(scale);
	animation_Turn->Play(0);
	animation_Turn->Stop();

	// 돌리는 공룡
	// Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 760, 2012, 792, 2044), animationSpeed);

		animation_SpinDragon->AddClip(clip);
	}

	// Spin
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 2045, 33, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 34, 2045, 66, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 67, 2045, 99, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 100, 2045, 132, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 133, 2045, 165, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 166, 2045, 198, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 2045, 231, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 2045, 264, 2078), animationSpeed);

		animation_SpinDragon->AddClip(clip);
	}
	// Boring1
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 793, 2012, 825, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 826, 2012, 858, 2044), animationSpeed);

		animation_SpinDragon->AddClip(clip);
	}
	// Boring2
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 892, 2012, 924, 2044), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 925, 2012, 957, 2044), animationSpeed);

		animation_SpinDragon->AddClip(clip);
	}
	// Win
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 265, 2045, 297, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 298, 2045, 330, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 331, 2045, 363, 2078), animationSpeed);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 364, 2045, 396, 2078), animationSpeed);

		animation_SpinDragon->AddClip(clip);
	}
	defaultPosition = Vector2(position.x + 132.0f, position.y - 16.0f);
	animation_SpinDragon->Position(defaultPosition);
	animation_SpinDragon->Scale(scale);
	animation_SpinDragon->Play(0);
	animation_SpinDragon->Stop();

}

LaunchingPad::~LaunchingPad()
{
	SAFE_DELETE(animation_Pad);
	SAFE_DELETE(animation_Turn);
	SAFE_DELETE(animation_SpinDragon);
}

void LaunchingPad::Update(Matrix & V, Matrix & P)
{
	Vector2 position = animation_SpinDragon->Position();

	// 발사대 움직임
	animation_Pad->GetClip()->SetFrame(frameNumber % 12);
	animation_Pad->Update(V, P);
	// 돌리는거 움직임
	animation_Turn->GetClip()->SetFrame(frameNumber % 8);
	animation_Turn->Update(V, P);
	// 돌리는 공룡 움직임
	switch (spinState) {
	case SDState::IDLE: {
		position = defaultPosition;
	}break;
	case SDState::SPIN: {
		animation_SpinDragon->GetClip()->SetFrame(frameNumber % 8);
	}break;
	case SDState::CLEAR: {
		position.x += moveSpeed * Time::Delta();
		moveDistance += moveSpeed * Time::Delta();
		if (moveDistance > 50.0f) {
			animation_SpinDragon->RotationDegree(0, 0, 0);
			moveSpeed = -200.0f;
		}
		if (moveDistance < 0) {
			animation_SpinDragon->RotationDegree(0, 180, 0);
			moveSpeed = 200.0f;
		}
	}break;
	}
	animation_SpinDragon->Position(position);
	animation_SpinDragon->Play((UINT)spinState);
	animation_SpinDragon->Update(V, P);
}

void LaunchingPad::Render()
{
	animation_Pad->Render();
	animation_Turn->Render();
	animation_SpinDragon->Render();
}