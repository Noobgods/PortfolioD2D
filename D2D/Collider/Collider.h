#pragma once
class Collider
{
public:
	Collider();
	~Collider();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void World(const D3DXMATRIX& world) { this->world = world; }
	D3DXMATRIX World() { return world; }

	static bool Aabb(D3DXMATRIX world, D3DXVECTOR2 position);
	static bool Aabb(D3DXMATRIX world1, D3DXMATRIX world2);
	static bool Cbb(D3DXMATRIX world1, D3DXMATRIX world2);

	void DrawColliderColor(bool val) { bDrawColliderColor = val; }
private:
	void CreateBuffer();

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
	};

private:
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXMATRIX world;

	D3DXVECTOR2	colliderSize;
	D3DXCOLOR initLineColor;
	D3DXCOLOR collidedColor;
	bool bDrawColliderColor;

	ID3DX11EffectMatrixVariable* sWorld;
	ID3DX11EffectMatrixVariable* sView;
	ID3DX11EffectMatrixVariable* sProjection;

	ID3DX11EffectVectorVariable* sColor;
};

