#pragma once

class Rect
{
public:
	Rect();
	Rect(D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 0));
	virtual ~Rect();

	virtual void Update(Matrix& V, Matrix& P);
	void Render();

private:
	void CreateBuffer();
	void Initialize();

public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	void Position(D3DXVECTOR2&& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	void Scale(D3DXVECTOR2&& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Color(float r, float g, float b, float a = 1.0f);
	void Color(D3DXCOLOR& vec);
	void Color(D3DXCOLOR&& vec);
	D3DXCOLOR Color() { return color; }

	void Pass(UINT val) { pass = val; }

	Matrix World() { return world; }
	void World(Matrix& matrix) { world = matrix; }

	Collider* GetCollider() { return collider; }
private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
	};

private:
	Shader* shader;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	ID3DX11EffectMatrixVariable* sWorld;
	ID3DX11EffectMatrixVariable* sView;
	ID3DX11EffectMatrixVariable* sProjection;
	ID3DX11EffectVectorVariable* sColor;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXCOLOR color;

	Matrix world;

	UINT pass;

	Collider* collider;
};