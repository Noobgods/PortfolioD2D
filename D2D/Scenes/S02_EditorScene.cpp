#include "stdafx.h"
#include "S02_EditorScene.h"

#include "Objects/Background.h"
#include "FileManager.h"

S02_EditorScene::S02_EditorScene(SceneValues * values)
	: Scene(values)
	, stage(1)
{
	background = new Background(Vector2(0, 0), Vector2(SCALE_X, SCALE_Y));
	
	// Collider Box 위치 초기화
	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y; i++) {
		Vector2 position = Vector2(-228.0f, 324.0f);
		if (i % 2 == 1) position.x += BUBBLE_SIZE_X / 2;
		position.y -= (i * BUBBLE_SIZE_Y);

		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			boxLine[i][j] = position;
			position.x += BUBBLE_SIZE_X;
		}
	}
	
	// Collider Box 초기화
	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y-1; i++) {
		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			if (i % 2 == 1 && j == BUBBLE_LINE_SIZE_X - 1);
			else {
				bubbleBox[i][j] = new Rect(boxLine[i][j], Vector2(BUBBLE_SIZE_X, BUBBLE_SIZE_Y));
				bubbles[i][j] = 0;
			}
		}
	}

	// Stage Load
	FileManager::Load(L"CustomStage.bin");
	int(*tempBubbles)[BUBBLE_LINE_SIZE_X] = (int(*)[BUBBLE_LINE_SIZE_X])FileManager::GetBubbles(stage);
	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y - 1; i++) {
		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			bubbles[i][j] = tempBubbles[i][j];
		}
	}
}

S02_EditorScene::~S02_EditorScene()
{
	SAFE_DELETE(background);

	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y-1; i++) {
		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			SAFE_DELETE(bubbleBox[i][j]);
		}
	}
}

void S02_EditorScene::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	GENERATE_MOUSE_UNPROJECT(mouse);

	background->Update(V, P);
	
	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y-1; i++) {
		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			if (i % 2 == 1 && j == BUBBLE_LINE_SIZE_X - 1);
			else
			bubbleBox[i][j]->Update(V, P);
		}
	}
}

void S02_EditorScene::Render()
{
	background->Render();
	for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y-1; i++) {
		for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
			if (i % 2 == 1 && j == BUBBLE_LINE_SIZE_X - 1);
			else {
				switch (bubbles[i][j]) {
				case 0:
					bubbleBox[i][j]->Color(0, 0, 0, 0);
					break;
					//파랑
				case 1:
					bubbleBox[i][j]->Color(0, 0.2, 0.9, 1);
					break;
					//노랑
				case 2:
					bubbleBox[i][j]->Color(0.9, 0.8, 0, 1);
					break;
					//빨강
				case 3:
					bubbleBox[i][j]->Color(0.9, 0.1, 0, 1);
					break;
					//초록
				case 4:
					bubbleBox[i][j]->Color(0.0, 0.7, 0, 1);
					break;
					//보라
				case 5:
					bubbleBox[i][j]->Color(0.3, 0.1, 0.6, 1);
					break;
					//주황
				case 6:
					bubbleBox[i][j]->Color(1, 0.5, 0.1, 1);
					break;
					//검정
				case 7:
					bubbleBox[i][j]->Color(0.1, 0.1, 0.1, 1);
					break;
					//하양
				case 8:
					bubbleBox[i][j]->Color(0.5, 0.5, 0.6, 1);
					break;
				default:
					break;
				}
				bubbleBox[i][j]->Render();
			}
		}
	}
	
	RenderImGui();
}

void S02_EditorScene::EditBubble() {
	if (ImGui::GetIO().WantCaptureMouse)
		return;

	// 클릭시 버블 배치
	if (Mouse->Down(0)){
		for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y - 1; i++) {
			for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
				if (i % 2 == 1 && j == BUBBLE_LINE_SIZE_X - 1);
				else {
					if (Collider::Aabb(bubbleBox[i][j]->GetCollider()->World(), mouse)) {
						// 색설정
						bubbles[i][j] = bubbleColor;
					}
				}
			}
		}
	}
}
void S02_EditorScene::RenderImGui() {
	ImGui::Combo("BubbleColor", &bubbleColor, "None\0Blue\0Yellow\0Red\0Green\0Purple\0Orange\0Black\0White");

	ImGui::DragInt("StageNumber", &stage, 0.1f, 1, 30);
	// Save Bubbles
	if (ImGui::Button("SaveStage")) {
		FileManager::SetBubbles(bubbles, stage);
		FileManager::Save(L"CustomStage.bin");
	}
	ImGui::SameLine();

	// Load Bubbles
	if (ImGui::Button("LoadStage")) {
		FileManager::Load(L"CustomStage.bin");
		int(* tempBubbles)[BUBBLE_LINE_SIZE_X] = (int(*)[BUBBLE_LINE_SIZE_X])FileManager::GetBubbles(stage);
		for (UINT i = 0; i < BUBBLE_LINE_SIZE_Y - 1; i++) {
			for (UINT j = 0; j < BUBBLE_LINE_SIZE_X; j++) {
				bubbles[i][j] = tempBubbles[i][j];
			}
		}
	}

	EditBubble();
}