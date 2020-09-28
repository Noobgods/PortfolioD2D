#include "stdafx.h"
#include "Background.h"

Background::Background(Vector2 position, Vector2 scale)
	: currentStage(0)
{
	wstring spriteFile1 = L"./Background/puzzleBubbleBG1.png";
	wstring spriteFile2 = L"./Background/puzzleBubbleBG2.png";
	wstring shaderFile = L"Effect.fx";

	// Stages
	Sprite* background;

	background = new Sprite(spriteFile1, shaderFile, 16, 16, 336, 240);
	stages.push_back(background);

	background = new Sprite(spriteFile1, shaderFile, 344, 16, 664, 240);
	stages.push_back(background);

	for (Sprite* stage : stages) {
		stage->Position(position);
		stage->Scale(scale);
	}

	// StageWalls
	Sprite* wall;

	wall = new Sprite(spriteFile2, shaderFile, 1, 10, 161, 210);
	stageWalls.push_back(wall);

	wall = new Sprite(spriteFile2, shaderFile, 1, 260, 161, 460);
	stageWalls.push_back(wall);

	for (Sprite* stageWall : stageWalls) {
		stageWall->Position(position.x, position.y-16.f);
		stageWall->Scale(scale);
	}

}

Background::~Background()
{
	for (Sprite* stage : stages)
		SAFE_DELETE(stage);
	for (Sprite* stageWall : stageWalls)
		SAFE_DELETE(stageWall);
}

void Background::Update(Matrix & V, Matrix & P)
{
	stages[currentStage]->Update(V, P);
	stageWalls[currentStage]->Update(V, P);
}

void Background::Render()
{
	stages[currentStage]->Render();
	stageWalls[currentStage]->Render();
}