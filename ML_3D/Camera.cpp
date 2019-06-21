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
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3( &up );

	// Setup the position of the camera in the world.
	position.x = mPositionX;
	position.y = mPositionY;
	position.z = mPositionZ;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3( &position );

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3( &lookAt );

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = mRotationX * 0.0174532925f;
	yaw = mRotationY * 0.0174532925f;
	roll = mRotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw( pitch, yaw, roll );

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord( lookAtVector, rotationMatrix );
	upVector = XMVector3TransformCoord( upVector, rotationMatrix );

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd( positionVector, lookAtVector );

	// Finally create the view matrix from the three updated vectors.
	mView = XMMatrixLookAtLH( positionVector, lookAtVector, upVector );

	return;
}

void Camera::GetViewMatrix( DirectX::XMMATRIX & viewMatrix)
{
	viewMatrix = mView;
	return;
}