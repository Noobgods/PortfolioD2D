#include "stdafx.h"
#include "Bubble.h"

Bubble::Bubble(Vector2 position, Vector2 scale, UINT color)
	: shotSpeed(Vector2(680.0f, 680.0f))
	, bubbleState(BState::IDLE)
	, bubbleSpeed(200.0f)
	, bubbleDistance(0.0f)
	, bubbleAngle(0.0f)
	, animationSpeed(0.07f)
	, bubbleColor(color)
	, animationState(AState::IDLE)
{
	//Animation : Begin
	animation = new Animation();

	wstring spriteFile = L"./puzzleBubble.png";
	wstring shaderFile = L"Effect.fx";

	Clip* clip;
	switch (color) {
		// 파란색
		case 1:{
			/// 파란색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1854, 34, 1870), animationSpeed);
				animation->AddClip(clip);
			}
			/// 파란색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 69, 1854, 85, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 86, 1854, 102, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 103, 1854, 119, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 1854, 136, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 1854, 153, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 154, 1854, 170, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1854, 34, 1870), animationSpeed);
				animation->AddClip(clip);
			}
			/// 파란색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 1854, 51, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 1854, 68, 1870), animationSpeed);
				animation->AddClip(clip);
			}
			/// 파란색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 171, 1846, 203, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 204, 1846, 236, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 237, 1846, 269, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 270, 1846, 302, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 303, 1846, 335, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 336, 1846, 368, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 369, 1846, 401, 1878), animationSpeed);
				animation->AddClip(clip);
			}
			/// 파란색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1978, 34, 1994), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 노란색
		case 2: {
			/// 노란색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1854, 588, 1870), animationSpeed);
				animation->AddClip(clip);
			}
			/// 노란색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 623, 1854, 639, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 640, 1854, 656, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 657, 1854, 673, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 674, 1854, 690, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 691, 1854, 707, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 708, 1854, 724, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1854, 588, 1870), animationSpeed);
				animation->AddClip(clip);
			}
			/// 노란색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 589, 1854, 605, 1870), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 606, 1854, 622, 1870), animationSpeed);
				animation->AddClip(clip);
			}
			/// 노란색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 725, 1846, 757, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 758, 1846, 790, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 791, 1846, 823, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 824, 1846, 856, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 857, 1846, 889, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 890, 1846, 922, 1878), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 923, 1846, 955, 1878), animationSpeed);
				animation->AddClip(clip);
			}
			/// 노란색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 205, 1978, 221, 1994), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 빨간색
		case 3: {
			/// 빨간색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1887, 17, 1903), animationSpeed);
				animation->AddClip(clip);
			}
			/// 빨간색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 69, 1887, 85, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 86, 1887, 102, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 103, 1887, 119, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 1887, 136, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 1887, 153, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 154, 1887, 170, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 1887, 17, 1903), animationSpeed);
				animation->AddClip(clip);
			}
			/// 빨간색 boring
			{
				clip = new Clip(PlayMode::End);
				animation->AddClip(clip);
			}
			/// 빨간색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 171, 1879, 203, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 204, 1879, 236, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 237, 1879, 269, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 270, 1879, 302, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 303, 1879, 335, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 336, 1879, 368, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 369, 1879, 401, 1911), animationSpeed);
				animation->AddClip(clip);
			}
			/// 빨간색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 392, 1978, 408, 1994), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 녹색
		case 4: {
			/// 녹색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1887, 588, 1903), animationSpeed);
				animation->AddClip(clip);
			}
			/// 녹색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 623, 1887, 639, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 640, 1887, 656, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 657, 1887, 673, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 674, 1887, 690, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 691, 1887, 707, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 708, 1887, 724, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1887, 588, 1903), animationSpeed);
				animation->AddClip(clip);
			}
			/// 녹색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 589, 1887, 605, 1903), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 606, 1887, 622, 1903), animationSpeed);
				animation->AddClip(clip);
			}
			/// 녹색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 725, 1879, 757, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 758, 1879, 790, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 791, 1879, 823, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 824, 1879, 856, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 857, 1879, 889, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 890, 1879, 922, 1911), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 923, 1879, 955, 1911), animationSpeed);
				animation->AddClip(clip);
			}
			/// 녹색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 579, 1978, 595, 1994), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 보라색
		case 5: {
			/// 보라색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1920, 34, 1936), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile,69, 1920, 85, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile,86, 1920, 102, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile,103, 1920, 119, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile,120, 1920, 136, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile,137, 1920, 153, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile,154, 1920, 170, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1920, 34, 1936), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 1920, 51, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 1920, 68, 1936), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 171, 1912, 203, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 204, 1912, 236, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 237, 1912, 269, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 270, 1912, 302, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 303, 1912, 335, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 336, 1912, 368, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 369, 1912, 401, 1944), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1995, 34, 2011), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 주황색
		case 6: {
			/// 보라색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1920, 588, 1936), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 623, 1920, 639, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 640, 1920, 656, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 657, 1920, 673, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 674, 1920, 690, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 691, 1920, 707, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 708, 1920, 724, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1920, 588, 1936), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 589, 1920, 605, 1936), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 606, 1920, 622, 1936), animationSpeed);
				animation->AddClip(clip);
			}
			/// 보라색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 725, 1912, 757, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 758, 1912, 790, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 791, 1912, 823, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 824, 1912, 856, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 857, 1912, 889, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 890, 1912, 922, 1944), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 923, 1912, 955, 1944), animationSpeed);
				animation->AddClip(clip);
			}
			/// 주황색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 205, 1995, 221, 2011), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 검정색
		case 7: {
			/// 검정색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1953, 34, 1969), animationSpeed);
				animation->AddClip(clip);
			}
			/// 검정색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 69, 1953, 85, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 86, 1953, 102, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 103, 1953, 119, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 1953, 136, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 1953, 153, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 154, 1953, 170, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 18, 1953, 34, 1969), animationSpeed);
				animation->AddClip(clip);
			}
			/// 검정색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 1953, 51, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 1953, 68, 1969), animationSpeed);
				animation->AddClip(clip);
			}
			/// 검정색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 171, 1945, 203, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 204, 1945, 236, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 237, 1945, 269, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 270, 1945, 302, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 303, 1945, 335, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 336, 1945, 368, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 369, 1945, 401, 1977), animationSpeed);
				animation->AddClip(clip);
			}
			/// 검정색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 392, 1995, 408, 2011), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
		// 흰색
		case 8: {
			/// 흰색 Idle
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1953, 588, 1969), animationSpeed);
				animation->AddClip(clip);
			}
			/// 흰색 blink
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 623, 1953, 639, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 640, 1953, 656, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 657, 1953, 673, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 674, 1953, 690, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 691, 1953, 707, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 708, 1953, 724, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 572, 1953, 588, 1969), animationSpeed);
				animation->AddClip(clip);
			}
			/// 흰색 boring
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 589, 1953, 605, 1969), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 606, 1953, 622, 1969), animationSpeed);
				animation->AddClip(clip);
			}
			/// 흰색 explode
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 725, 1945, 757, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 758, 1945, 790, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 791, 1945, 823, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 824, 1945, 856, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 857, 1945, 889, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 890, 1945, 922, 1977), animationSpeed);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 923, 1945, 955, 1977), animationSpeed);
				animation->AddClip(clip);
			}
			/// 흰색 GAMEOVER
			{
				clip = new Clip(PlayMode::End);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 579, 1995, 595, 2011), animationSpeed);
				animation->AddClip(clip);
			}
		}break;
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
	//Animation : End

	collider = new Collider();
}

Bubble::~Bubble()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(collider);
}

void Bubble::Update(Matrix & V, Matrix & P)
{
	Vector2 position = animation->Position();

	switch (bubbleState) {
	case BState::SPAWN: {
		if (bubbleDistance < 100.0f) {
			bubbleDistance += bubbleSpeed * Time::Delta();
			position.x += bubbleSpeed * Time::Delta();
		}
		else {
			bubbleDistance = 0;
			bubbleState = BState::NEXT;
		}
	} break;

	case BState::MOVEREADY: {
		bubbleDistance += bubbleSpeed * Time::Delta();
		if (bubbleDistance < 40.0f)
			position = Vector2(-120.0f, -360.0f);
		else if (bubbleDistance < 60.0f)
			position = Vector2(-100.0f, -350.0f);
		else if (bubbleDistance < 80.0f)
			position = Vector2(-90.0f, -340.0f);
		else if (bubbleDistance < 100.0f)
			position = Vector2(-30.0f, -330.0f);
		else if (bubbleDistance < 120.0f)
			position = Vector2(-0.0f, -320.0f);
		else {
			bubbleDistance = 0;
			bubbleState = BState::READY;
			position = Vector2(0.0f, -320.0f);
		}
	} break;

	case BState::SHOT: {
		position.x += shotSpeed.x * cosf(bubbleAngle) * Time::Delta();
		position.y += shotSpeed.y * sinf(bubbleAngle) * Time::Delta();
		if (position.x > 224.0f || position.x < -224.0f) {
			Audio->Play("BUMP");
			shotSpeed.x = -shotSpeed.x;
		}
	} break;

	case BState::BURST: {
		animationState = AState::BURST;
		animation->Play(3);
		if (animation->GetClip()->EndFrame()) {
			bubbleState = BState::DEL;
		}
	} break;

	case BState::INAIR: {
		bubbleSpeed += bubbleSpeed * 3.0f * Time::Delta();
		position.y -= bubbleSpeed * Time::Delta();
		if (position.y < -360.0f) {
			bubbleState = BState::DEL;
		}
	} break;

	case BState::IDLE: {
		animationState = AState::BLINK;
	} break;
	case BState::GAMEOVER: {
		animationState = AState::GAMEOVER;
	}break;

	}
	// Idle
	animation->Play((UINT)animationState);
	animation->Position(position);
	animation->Update(V, P);

	collider->World(animation->GetSprite()->World());
	collider->Update(V, P);
}
void Bubble::Render()
{
	//collider->Render();
	animation->Render();
}

void Bubble::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Bubble::Position(D3DXVECTOR2 & position)
{
	Position(std::move(position));
}

void Bubble::Position(D3DXVECTOR2 && position)
{
	animation->Position(position);
}

D3DXVECTOR2 Bubble::Position()
{
	return animation->Position();
}

void Bubble::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Bubble::Scale(D3DXVECTOR2 & scale)
{
	Scale(std::move(scale));
}

void Bubble::Scale(D3DXVECTOR2 && scale)
{
	animation->Scale(scale);
}

D3DXVECTOR2 Bubble::Scale()
{
	return animation->Scale();
}

void Bubble::shootBubble(float angle)
{
	bubbleAngle = Math::ToRadian(angle);
	bubbleState = BState::SHOT;
}

void Bubble::BubbleState(BState state) {
	this->bubbleState = state;
}

Matrix Bubble::World() {
	return animation->GetSprite()->World();
}