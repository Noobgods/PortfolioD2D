#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(Vector2 position, Vector2 scale)
	: frameNumber(0)
	, targetLeft(false)
	, targetRight(false)
{
	animation = new Animation();

	wstring spriteFile = L"./puzzleBubble.png";
	wstring shaderFile = L"Effect.fx";

	Clip* clip;
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1545, 65, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 66, 1545, 130, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 1545, 195, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 196, 1545, 260, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 261, 1545, 325, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 326, 1545, 390, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 391, 1545, 455, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 456, 1545, 520, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 521, 1545, 585, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 586, 1545, 650, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 651, 1545, 715, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 716, 1545, 780, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 781, 1545, 845, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 846, 1545, 910, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 911, 1545, 975, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 976, 1545, 1040, 1609), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1610, 65, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 66, 1610, 130, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 1610, 195, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 196, 1610, 260, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 261, 1610, 325, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 326, 1610, 390, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 391, 1610, 455, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 456, 1610, 520, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 521, 1610, 585, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 586, 1610, 650, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 651, 1610, 715, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 716, 1610, 780, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 781, 1610, 845, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 846, 1610, 910, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 911, 1610, 975, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 976, 1610, 1040, 1674), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1675, 65, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 66, 1675, 130, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 1675, 195, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 196, 1675, 260, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 261, 1675, 325, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 326, 1675, 390, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 391, 1675, 455, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 456, 1675, 520, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 521, 1675, 585, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 586, 1675, 650, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 651, 1675, 715, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 716, 1675, 780, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 781, 1675, 845, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 846, 1675, 910, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 911, 1675, 975, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 976, 1675, 1040, 1739), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1740, 65, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 66, 1740, 130, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 1740, 195, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 196, 1740, 260, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 261, 1740, 325, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 326, 1740, 390, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 391, 1740, 455, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 456, 1740, 520, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 521, 1740, 585, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 586, 1740, 650, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 651, 1740, 715, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 716, 1740, 780, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 781, 1740, 845, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 846, 1740, 910, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 911, 1740, 975, 1804), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 976, 1740, 1040, 1804), 0.1f);

		animation->AddClip(clip);
	}
	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
	animation->Stop();
}

Arrow::~Arrow()
{
	SAFE_DELETE(animation);
}

void Arrow::Update(Matrix & V, Matrix & P)
{
	// 범위 제한
	if (frameNumber >= LAUNCHER_ANGLE)
		frameNumber = LAUNCHER_ANGLE;
	if (frameNumber <= -LAUNCHER_ANGLE)
		frameNumber = -LAUNCHER_ANGLE;

	// 각도 조절
	if (frameNumber <= 0.0f) {
		animation->RotationDegree(0, 180, 0);
		animation->GetClip()->SetFrame(-frameNumber);
	}
	else {
		animation->RotationDegree(0, 0, 0);
		animation->GetClip()->SetFrame(frameNumber);
	}

	animation->Update(V, P);
}
void Arrow::Render()
{
	animation->Render();
}

void Arrow::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Arrow::Position(D3DXVECTOR2 & position)
{
	Position(std::move(position));
}

void Arrow::Position(D3DXVECTOR2 && position)
{
	animation->Position(position);
}

D3DXVECTOR2 Arrow::Position()
{
	return animation->Position();
}

void Arrow::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Arrow::Scale(D3DXVECTOR2 & scale)
{
	Scale(std::move(scale));
}

void Arrow::Scale(D3DXVECTOR2 && scale)
{
	animation->Scale(scale);
}

D3DXVECTOR2 Arrow::Scale()
{
	return animation->Scale();
}
