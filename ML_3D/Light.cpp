#include "Global.h"
#include "Light.h"


Light::Light( )
{ }

void Light::SetAmbientColor( float red, float green, float blue, float alpha )
{
	mAmbientColor = XMFLOAT4( red, green, blue, alpha );
}

void Light::SetDiffuseColor( float red, float green, float blue, float alpha )
{
	mDiffuseColor = XMFLOAT4( red, green, blue, alpha );
}

void Light::SetDirection( float x, float y, float z )
{
	mDirection = XMFLOAT3( x, y, z );
}

void Light::SetSpecularColor( float red, float green, float blue, float alpha )
{
	mSpecularColor = XMFLOAT4( red, green, blue, alpha );
}

void Light::SetSpecularPower( float power )
{
	mSpecularPower = power;
}

XMFLOAT4 Light::GetAmbientColor( )
{
	return mAmbientColor;
}

XMFLOAT4 Light::GetDiffuseColor( )
{
	return mDiffuseColor;
}

XMFLOAT3 Light::GetDirection( )
{
	return mDirection;
}

XMFLOAT4 Light::GetSpecularColor( )
{
	return mSpecularColor;
}

float Light::GetSpecularPower( )
{
	return mSpecularPower;
}
