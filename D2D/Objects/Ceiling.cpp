#include "stdafx.h"
#include "Ceiling.h"

Ceiling::Ceiling(Vector2 position, Vector2 scale)
	: currentStage(0)
	, frameNumber(0)
{
	animation = new Animation();

	wstring spriteFile = L"./Background/puzzleBubbleBG2.png";
	wstring shaderFile = L"Effect.fx";

	Clip* clip;
	{	   
		// Stage 1-3 (0)
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 162, 10, 290, 18), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 291, 10, 419, 32), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 420, 10, 548, 46), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 549, 10, 677, 60), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 678, 10, 806, 74), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 807, 10, 935, 88), 0.1f);

		clip->AddFrame(new Sprite(spriteFile, shaderFile, 162, 91, 290, 183), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 291, 91, 419, 197), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 420, 91, 548, 211), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 549, 91, 677, 225), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 678, 91, 806, 239), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 807, 91, 935, 253), 0.1f);
		animation->AddClip(clip);
	}
	{
		// Stage 4-6 (1)
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 162, 260, 290, 268), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 291, 260, 419, 282), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 420, 260, 548, 296), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 549, 260, 677, 310), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 678, 260, 806, 324), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 807, 260, 935, 338), 0.1f);

		clip->AddFrame(new Sprite(spriteFile, shaderFile, 162, 341, 290, 433), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 291, 341, 419, 447), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 420, 341, 548, 461), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 549, 341, 677, 475), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 678, 341, 806, 489), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 807, 341, 935, 503), 0.1f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
	animation->Stop();
}

Ceiling::~Ceiling()
{
	SAFE_DELETE(animation);
}

void Ceiling::Update(Matrix & V, Matrix & P)
{
	animation->Play(currentStage);
	animation->GetClip()->SetFrame(frameNumber);
	animation->Update(V, P);
}

void Ceiling::Render()
{
	animation->Render();
}

void Ceiling::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Ceiling::Position(D3DXVECTOR2 & position)
{
	Position(std::move(position));
}

void Ceiling::Position(D3DXVECTOR2 && position)
{
	animation->Position(position);
}

D3DXVECTOR2 Ceiling::Position()
{
	return animation->Position();
}

void Ceiling::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Ceiling::Scale(D3DXVECTOR2 & scale)
{
	Scale(std::move(scale));
}

void Ceiling::Scale(D3DXVECTOR2 && scale)
{
	animation->Scale(scale);
}

D3DXVECTOR2 Ceiling::Scale()
{
	return animation->Scale();
}
