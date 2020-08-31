#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(0, 0)
{
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{
}

void Camera::Position(float x, float y)
{
	Position(Vector2(x, y));
}

void Camera::Position(Vector2& vec)
{
	Position(std::move(vec));
}

void Camera::Position(Vector2&& vec)
{
	position = vec;
}

void Camera::Update()
{
	//View
	Vector3 eye = Vector3(position.x, position.y, 0.0f);
	Vector3 at(0, 0, 1);
	Vector3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&view, &eye, &(eye + at), &up);
}
