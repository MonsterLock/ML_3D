#pragma once
class Camera
{
	float
		mPositionX, mPositionY, mPositionZ,
		mRotationX, mRotationY, mRotationZ;
	XMMATRIX mView;

public:
	Camera() noexcept;
	void SetPosition( float, float, float );
	void SetRotation( float, float, float );

	XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix( DirectX::XMMATRIX & );
};
