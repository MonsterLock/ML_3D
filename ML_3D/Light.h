#pragma once
class Light
{
public:
	Light( );
	void SetAmbientColor( float, float, float, float );
	void SetDiffuseColor( float, float, float, float );
	void SetDirection( float, float, float );
	void SetSpecularColor( float, float, float, float );
	void SetSpecularPower( float );

	XMFLOAT4 GetAmbientColor( );
	XMFLOAT4 GetDiffuseColor( );
	XMFLOAT3 GetDirection( );
	XMFLOAT4 GetSpecularColor( );
	float GetSpecularPower( );

private:
	XMFLOAT4 mAmbientColor;
	XMFLOAT4 mDiffuseColor;
	XMFLOAT3 mDirection;
	XMFLOAT4 mSpecularColor;
	float mSpecularPower;
};

