#include "stdafx.h"
#include "Systems/Device.h"
#include "Scenes/Scene.h"

#include "Scenes/S00_MainScene.h"
#include "Scenes/S01_GameScene.h"
#include "Scenes/S02_EditorScene.h"

SceneValues* values;
vector<Scene*> scenes; 

void InitScene() {
	values = new SceneValues();

	values->MainCamera = new Camera();
	D3DXMatrixIdentity(&values->Projection);	

	scenes.push_back(new S02_EditorScene(values));

	// Sound
	Audio->AddSound("BGM", "./_Sounds/Puzzle Bobble - Theme.mp3",true);
	Audio->AddSound("SHOT", "./_Sounds/pbobble-002.wav");
	Audio->AddSound("BUMP", "./_Sounds/pbobble-004.wav");
	Audio->AddSound("PONG", "./_Sounds/pbobble-005.wav");
	Audio->AddSound("PING", "./_Sounds/pbobble-009.wav");
	Audio->AddSound("READY", "./_Sounds/pbobble-024 (READYYYYYY).wav");
	Audio->AddSound("GO", "./_Sounds/pbobble-025 (GO!).wav");
	Audio->AddSound("LOSE", "./_Sounds/pbobble-026.wav");
	Audio->AddSound("CLEAR", "./_Sounds/CLEAR.wav");
}

void DestroyScene() {
	for (Scene* scene : scenes)
		SAFE_DELETE(scene);
			
	SAFE_DELETE(values);
}

void Update() {

	values->MainCamera->Update();

	//Projection 
	D3DXMatrixOrthoOffCenterLH(
		&values->Projection,
		(float)Width * -0.5f, (float)Width * 0.5f,
		(float)Height * -0.5f, (float)Height * 0.5f,
		-1, 1
	);
	if (Key->Press(VK_F1)) {
		SAFE_DELETE(scenes[0]);
		scenes.clear();
		scenes.push_back(new S01_GameScene(values));
	}
	if (Key->Press(VK_F2)) {
		SAFE_DELETE(scenes[0]);
		scenes.clear();
		scenes.push_back(new S02_EditorScene(values));
	}
	for (Scene* scene : scenes)
		scene->Update();

}

void Render() {
	D3DXCOLOR bgcolor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		for (Scene* scene : scenes)
			scene->Render();
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		/*
		RECT rect = { 0, 0, 500, 200 };
		wstring text = L"";
		text = L"FPS : " + to_wstring(Time::Get()->FPS());
		DirectWrite::RenderText(text, rect);
		*/

		RECT rect = { 0, 0, 500, 200 };
		wstring text = L"FPS(ImGui) : " + to_wstring((int)ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);
	}
	DirectWrite::GetDC()->EndDraw();

	SwapChain->Present(0, 0);
}