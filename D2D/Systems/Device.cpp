#include "stdafx.h"
#include "Device.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lPCmdLine,
	int nCmdShow
){
	InitWindow(hInstance, nCmdShow);	// 윈도우 초기화
	InitDirect3D(hInstance);

	Running();
	Destroy();

	return 0;
}

// extern 전역 변수
UINT Width = 320 * 4;
UINT Height = 224 * 4;

HWND Hwnd = NULL;
wstring Title = L"D2D";

IDXGISwapChain* SwapChain = NULL;
ID3D11Device* Device = NULL;
ID3D11DeviceContext* DeviceContext = NULL;
ID3D11RenderTargetView* RTV = NULL;

Keyboard* Key = NULL;
CMouse* Mouse = NULL;
AudioSystem* Audio = NULL;

void InitWindow(HINSTANCE hInstance, int nCmdShow) {
	// Register Wnd Class
	{
		WNDCLASSEX wc; // 윈도우 클래스 생성
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;					// 수직, 수평크기 변할시 다시 그림
		wc.lpfnWndProc = WndProc;							// 윈도우 메세지 처리함수 지정
		wc.cbClsExtra = NULL;								// 예약 영역
		wc.cbWndExtra = NULL;
		wc.hInstance = hInstance;							// 응용 프로그램 인스턴스
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// 최소화 되었을때 출력될 아이콘
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// 사용할 마우스 커서
		wc.hbrBackground = static_cast<HBRUSH>(WHITE_BRUSH);// 배경색상 브러시 지정
		wc.lpszMenuName = NULL;								// 프로그램이 사용할 메뉴 지정
		wc.lpszClassName = Title.c_str();					//윈도우 클래스 이름
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		WORD check = RegisterClassEx(&wc);
		assert(check != NULL);
	}
	// Create Window & Show Window
	{
		Hwnd = CreateWindowEx(	// 윈도우 생성
			NULL,
			Title.c_str(),		// 타이틀 클래스 이름
			Title.c_str(),		// 타이틀 바 이름
			WS_OVERLAPPEDWINDOW,// 윈도우 스타일
			CW_USEDEFAULT,		// 생성될 좌표 x
			CW_USEDEFAULT,		// 생성될 좌표 y
			Width,				// 너비 크기
			Height,				// 높이 크기
			NULL,				// 소유주 핸들 지정
			NULL,				// 메뉴의 핸들 지정
			hInstance,			// 인스턴스 핸들 지정
			NULL				// lParam으로 전달될 구조체의 포인터
		);
		assert(Hwnd != NULL);
	}

	ShowWindow(Hwnd, nCmdShow);
	UpdateWindow(Hwnd);
}

void InitDirect3D(HINSTANCE hInstance) {
	// SwapChain
	DXGI_MODE_DESC bufferDesc;											// 후면버퍼 속성 구조체
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = Width;
	bufferDesc.Height = Height;
	bufferDesc.RefreshRate.Numerator = 60;								// 화면 재생 빈도
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 디스플레이 스캔라인 모드
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						// 픽셀 형식(UNORM : 0~1사이의 값)

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;								// 후면 버퍼 개수
	swapDesc.BufferDesc = bufferDesc;						// 후면 버퍼 속성
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 버퍼의 용도 (표면, 자원을 출력 렌더 타겟으로 지정)
	swapDesc.SampleDesc.Count = 1;							// 멀티 샘플링을 위해 추출할 표본의 개수와 품질 수준
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.OutputWindow = Hwnd;							// 렌더링 결과를 출력할 윈도우
	swapDesc.Windowed = TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;			// 이전에 그렸던 것 폐기

	// Featured Level
	vector<D3D_FEATURE_LEVEL> featured_level =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// Create Device and SwapChain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,	// 2D랑 병행할때 쓰는 플래그
		featured_level.data(),
		featured_level.size(),
		D3D11_SDK_VERSION,
		&swapDesc,
		&SwapChain,
		&Device,
		NULL,
		&DeviceContext
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer();
}

void Destroy() {
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(Device);
	SAFE_RELEASE(DeviceContext);

	DeleteBackBuffer();
}

WPARAM Running() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Init Singleton
	ImGui::Create(Hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();

	DirectWrite::Create();

	Key = new Keyboard();
	Mouse = new CMouse(Hwnd);
	Audio = new AudioSystem();

	Time::Create();
	Time::Get()->Start();

	InitScene();

	while (true) {
		// 메세지가 들어와 있는지 검사 후 리턴
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);	// 해석
			DispatchMessage(&msg);	// 보고
		}
		else {
			Time::Get()->Update();
			Update();
			Mouse->Update();
			Audio->Update();
			ImGui::Update();
			Render();
		}
	}

	DestroyScene();
	
	// Delete Singleton
	SAFE_DELETE(Key);
	SAFE_DELETE(Mouse);
	SAFE_DELETE(Audio);

	Time::Delete();
	ImGui::Delete();
	DirectWrite::Delete();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui::WndProc((UINT*)Hwnd, msg, wParam, lParam))
		return true;

	if (Mouse != NULL)
		Mouse->WndProc(msg, wParam, lParam);

	switch (msg) {
	case WM_SIZE: {
		if (Device != NULL) {

			Width = LOWORD(lParam);
			Height = HIWORD(lParam);

			DirectWrite::DeleteBackBuffer();
			DeleteBackBuffer();

			ImGui::Invalidate();

			HRESULT hr = SwapChain->ResizeBuffers(0, Width, Height, DXGI_FORMAT_UNKNOWN, 0);
			assert(SUCCEEDED(hr));

			DirectWrite::CreateBackBuffer();
			CreateBackBuffer();

			ImGui::Validate();
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void CreateBackBuffer() {
	//Get BackBuffer
	ID3D11Texture2D* BackBuffer;
	HRESULT hr = SwapChain->GetBuffer(
		0,							// 백버퍼의 번호
		__uuidof(ID3D11Texture2D),	// 백버퍼에 접근하는 인터페이스
		(void**)&BackBuffer			// 백버퍼를 받아올 변수
	);	
	assert(SUCCEEDED(hr));

	//Create RTV
	hr = Device->CreateRenderTargetView(
		BackBuffer,	// 뷰에서 엑세스하는 리소스
		NULL,		// 렌더 타겟 뷰 정의
		&RTV		// 렌더 타겟 뷰를 받아올 변수
	);
	assert(SUCCEEDED(hr));
	SAFE_RELEASE(BackBuffer);

	//OM Set
	DeviceContext->OMSetRenderTargets(
		1,		// 렌더 타겟의 수
		&RTV,	// 렌더 타겟 뷰의 배열
		NULL	// 깊이/스텐실 버퍼
	);

	//Create Viewport
	{
		D3D11_VIEWPORT viewPort;
		ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = (float)Width;
		viewPort.Height = (float)Height;

		DeviceContext->RSSetViewports(1, &viewPort);
	}
}

void DeleteBackBuffer() {
	SAFE_RELEASE(RTV);
}
