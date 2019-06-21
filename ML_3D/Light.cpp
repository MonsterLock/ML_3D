#include "Global.h"
#include "Light.h"


Light::Light( )
{ }

void Light::SetDiffuseColor( float red, float green, float blue, float alpha )
{
	mDiffuseColor = XMFLOAT4( red, green, blue, alpha );
}

void Light::SetDirection( float x, float y, float z )
{
	mDirection = XMFLOAT3( x, y, z );
}

XMFLOAT4 Light::GetDiffuseColor( )
{
	return mDiffuseColor;
}

XMFLOAT3 Light::GetDirection( )
{
	return mDirection;
}
