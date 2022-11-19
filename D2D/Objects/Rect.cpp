#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
	: position(0, 0), scale(1, 1), color(1, 1, 1, 0)
{
	Initialize();

}

Rect::Rect(D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	:position(position), scale(scale), color(color)
{
	Initialize();

	Color(color);
}

void Rect::Initialize()
{
	shader = new Shader(L"Rect.fx");
	collider = new Collider();

	CreateBuffer();

	D3DXMatrixIdentity(&world);

	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");
	sColor = shader->AsVector("Color");

}

void Rect::CreateBuffer()
{
	Vertex vertices[4];

	//Vertices
	{
		vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
		vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
		vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
		vertices[3].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	}

	//Indices
	// 그릴 정점의 번호
	UINT indices[6] = { 0, 1, 2, 2, 1, 3 };

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = indices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &indexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Rect::~Rect()
{
	SAFE_DELETE(shader);
	SAFE_DELETE(collider);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void Rect::Update(Matrix& V, Matrix& P)
{
	D3DXMATRIX S, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	world = S * T;

	sWorld->SetMatrix(world);
	sView->SetMatrix(V);
	sProjection->SetMatrix(P);

	collider->World(world);
	collider->Update(V, P);
}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// indexBuffer를 통해서 넘길때 4Byte (우리가 넘길 데이터 크기)
	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, 0, 6);

	collider->Render();
}

void Rect::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Rect::Position(D3DXVECTOR2 & vec)
{
	Position(std::move(vec));
}

void Rect::Position(D3DXVECTOR2 && vec)
{
	position = vec;
}

void Rect::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Rect::Scale(D3DXVECTOR2 & vec)
{
	Scale(std::move(vec));
}

void Rect::Scale(D3DXVECTOR2 && vec)
{
	scale = vec;
}

void Rect::Color(float r, float g, float b, float a)
{
	Color(D3DXCOLOR(r, g, b, a));
}

void Rect::Color(D3DXCOLOR & vec)
{
	Color(std::move(vec));
}

void Rect::Color(D3DXCOLOR && vec)
{
	color = vec;
	sColor->SetFloatVector(color);
}