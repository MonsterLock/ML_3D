#include "Global.h"
#include "Camera.h"

Camera::Camera() noexcept
	:
	mPositionX( 0.0f ), mPositionY( 0.0f ), mPositionZ( 0.0f ),
	mRotationX( 0.0f ), mRotationY( 0.0f ), mRotationZ( 0.0f )
{}

void Camera::SetPosition( float x, float y, float z )
{
	mPositionX = x;
	mPositionY = y;
	mPositionZ = z;
}

void Camera::SetRotation( float x, float y, float z )
{
	mRotationX = x;
	mRotationY = y;
	mRotationZ = z;
}

DirectX::XMFLOAT3 Camera::GetPosition()
{
	return DirectX::XMFLOAT3( mPositionX, mPositionY, mPositionZ );
}

DirectX::XMFLOAT3 Camera::GetRotation()
{
	return DirectX::XMFLOAT3( mRotationX, mRotationY, mRotationZ );
}

void Camera::Render()
{
	//DirectX::XMVECTOR
	//	up = DirectX::XMLoadFloat3( &DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) ),
	//	position( mPositionX, mPositionY, mPositionZ ),
	//	lookAt( 0.0f, 0.0f, 1.0f );
	//float
	//	pitch = mRotationX * 0.0174532925f,
	//	yaw = mRotationY * 0.0174532925f,
	//	roll = mRotationZ * 0.0174532925f;

	//DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw( pitch, yaw, roll );
	//DirectX::XMVector3TransformCoord( lookAt, rotation );
}

void Camera::GetViewMatrix( DirectX::XMMATRIX & )
{}

