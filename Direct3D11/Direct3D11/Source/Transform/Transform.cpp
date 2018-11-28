#include "Transform.h"

using namespace DirectX;

Transform::Transform()
{
	XMStoreFloat4x4(&m_LocalMatrix, XMMatrixIdentity());
}


Transform::~Transform()
{
}

DirectX::XMFLOAT3 Transform::GetPos() const
{
	float x, y, z;
	x = m_LocalMatrix._41;
	y = m_LocalMatrix._42;
	z = m_LocalMatrix._43;
	return DirectX::XMFLOAT3(x, y, z);
}
