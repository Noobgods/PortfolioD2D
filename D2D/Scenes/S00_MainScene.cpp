#include "stdafx.h"
#include "S00_MainScene.h";

S00_MainScene::S00_MainScene(SceneValues * values)
	: Scene(values)
{
	wstring spriteFile = L"./puzzleBubble.png";
	wstring shaderFile = L"Effect.fx";

	// 메인 배경 1, 10, 321, 234
	background = new Sprite(spriteFile, shaderFile, 1, 10, 321, 234);
	background->Scale(4.0f, 4.0f);
	// 타이틀 글씨 595, 462, 787, 606
	mainTitle = new Sprite(spriteFile, shaderFile, 595, 462, 787, 606);
	mainTitle->Scale(4.0f, 4.0f);
	mainTitle->Position(mainTitle->Position().x, mainTitle->Position().y + 100);
}

S00_MainScene::~S00_MainScene()
{
	SAFE_DELETE(background);
	SAFE_DELETE(mainTitle);
}

void S00_MainScene::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;


	mainTitle->Update(V, P);
	background->Update(V, P);

}

void S00_MainScene::Render()
{
	background->Render();
	mainTitle->Render();

	DirectWrite::GetDC()->BeginDraw();
	{

		RECT rect1 = { Width/2-100, 700, Width/2+300, 730 };
		wstring text1 = L"Game Mode (F1 Key)";
		DirectWrite::RenderText(text1, rect1);

		RECT rect2 = { Width / 2 - 100, 730, Width / 2 + 300, 760 };
		wstring text2 = L"Edit Mode (F2 Key)";
		DirectWrite::RenderText(text2, rect2);
	}
	DirectWrite::GetDC()->EndDraw();

}
