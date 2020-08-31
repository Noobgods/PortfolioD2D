#include "stdafx.h"
#include "Collider.h"

Collider::Collider()
	:bDrawColliderColor(false)
{
	shader = new Shader(L"Bounding.fx");
	D3DXMatrixIdentity(&world);

	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");
	sColor = shader->AsVector("LineColor");

	CreateBuffer();
	
	initLineColor = D3DXCOLOR(0, 1, 0, 1);
	collidedColor = D3DXCOLOR(1, 0, 0, 1);

}

void Collider::CreateBuffer()
{
	Vertex vertices[5];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	// NULL로 초기화
		desc.Usage = D3D11_USAGE_DEFAULT;	// 접근권한 DEFAULT(), DYNAMIC(CPU)
		desc.ByteWidth = sizeof(Vertex) * 5;	// 크기
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 사용용도

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));	// NULL로 초기화
		data.pSysMem = vertices;	// 시작 주소

		// description, 서브릭 소스, 만들 객체
		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}


Collider::~Collider()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_DELETE(shader);
}

void Collider::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	colliderSize = Vector2(world._11, world._22);

	Matrix S,T;
	D3DXMatrixScaling(&S, colliderSize.x * 0.7f, colliderSize.y * 0.7f, 1.0f);
	D3DXMatrixTranslation(&T, world._41, world._42, 0.0f);
	world = S * T;

	sWorld->SetMatrix(world);
	sView->SetMatrix(V);
	sProjection->SetMatrix(P);
}

void Collider::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;	// 몇번 인덱스부터 가져오느냐

	// IA stage
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	sColor->SetFloatVector(bDrawColliderColor ? collidedColor : initLineColor);

	shader->Draw(0, 0, 5);
}

bool Collider::Aabb(D3DXMATRIX & world, D3DXVECTOR2 & position)
{
	// 위치 좌표
	D3DXVECTOR2 position1 = D3DXVECTOR2(world._41, world._42);
	D3DXVECTOR2 position2 = position;

	D3DXVECTOR2 distance;
	distance.x = fabsf(position1.x - position2.x);
	distance.y = fabsf(position1.y - position2.y);

	D3DXVECTOR2 halfSize;
	halfSize = D3DXVECTOR2(fabsf(world._11), fabsf(world._22)) * 0.5f;

	if (distance.x > halfSize.x) return false;
	if (distance.y > halfSize.y) return false;

	return true;

}

bool Collider::Aabb(D3DXMATRIX world1, D3DXMATRIX world2)
{
	// 위치 좌표
	D3DXVECTOR2 position1 = D3DXVECTOR2(world1._41, world1._42);
	D3DXVECTOR2 position2 = D3DXVECTOR2(world2._41, world2._42);

	D3DXVECTOR2 distance;
	distance.x = fabsf(position1.x - position2.x);
	distance.y = fabsf(position1.y - position2.y);

	D3DXVECTOR2 halfSize1, halfSize2;
	halfSize1 = D3DXVECTOR2(fabsf(world1._11), fabsf(world1._22)) * 0.5f;
	halfSize2 = D3DXVECTOR2(fabsf(world2._11), fabsf(world2._22)) * 0.5f;

	if (distance.x > halfSize1.x + halfSize2.x) return false;
	if (distance.y > halfSize1.y + halfSize2.y) return false;

	return true;
}

bool Collider::Cbb(D3DXMATRIX world1, D3DXMATRIX world2) {
	// 위치 좌표
	D3DXVECTOR2 A = D3DXVECTOR2(world1._41, world1._42);
	D3DXVECTOR2 B = D3DXVECTOR2(world2._41, world2._42);

	// 두 점의 거리
	float distance = pow(A.x-B.x,2)+pow(A.y-B.y,2)/2;

	// 반지름
	float halfSize1, halfSize2;
	halfSize1 = fabsf(world1._11) * 0.5f;
	halfSize2 = fabsf(world2._11) * 0.5f;

	// 두 거리가 반지름의 합보다 작다면
	if ( distance <= pow(halfSize1 + halfSize2, 2)) return true;
	else return false;
}