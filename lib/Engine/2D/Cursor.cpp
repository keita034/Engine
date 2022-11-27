#include "Cursor.h"

Cursor::Cursor()
{
	input = Input::GetInstance();
	mesh = Mesh::GetInstance();
}

Cursor::Cursor(const TextureData& textureData)
{
	input = Input::GetInstance();
	mesh = Mesh::GetInstance();
	sprite.reset(Sprite::Create2DSprite(textureData));
}

Cursor::~Cursor()
{
}

void Cursor::Update()
{
	cursor = input->GetMousePos();
}

void Cursor::DrawCursor(float radiusX, float radiusY, AliceMathF::Vector4 color,bool fillMode)
{
	mesh->DrawEllipse(cursor.x, cursor.y, radiusX, radiusY, 0.0f, color, fillMode);
}

void Cursor::DrawGraphCursor(Transform& transform)
{
	sprite->Draw(transform);
}

AliceMathF::Vector2 Cursor::GetCursor()
{
	return cursor;
}