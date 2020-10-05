#include "stdafx.h"
#include "S02_EditorScene.h"

#include "Objects/Background.h"

S02_EditorScene::S02_EditorScene(SceneValues * values)
	: Scene(values)
{
	background = new Background(Vector2(0, 0), Vector2(SCALE_X, SCALE_Y));

	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
		Vector2 position = Vector2(-228.0f, 324.0f);
		if (i % 2 == 1) position.x += BUBBLE_SIZE_X / 2;
		position.y -= (i * BUBBLE_SIZE_Y);

		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			boxLine[i][j] = position;
			position.x += BUBBLE_SIZE_X;
		}
	}
}

S02_EditorScene::~S02_EditorScene()
{
	SAFE_DELETE(background);
}

void S02_EditorScene::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	background->Update(V, P);
}

void S02_EditorScene::Render()
{
	background->Render();
}
