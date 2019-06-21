#pragma once
class Light
{
public:
	Light( );
	void SetDiffuseColor( float, float, float, float );
	void SetDirection( float, float, float );

	XMFLOAT4 GetDiffuseColor( );
	XMFLOAT3 GetDirection( );

private:
	XMFLOAT4 mDiffuseColor;
	XMFLOAT3 mDirection;
};

