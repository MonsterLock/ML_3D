#include "ML_Matrix.h"
#ifdef ml3d_MATH_USE_LH

#define m00 0
#define m01 1
#define m02 2
#define m03 3
#define	m10 4
#define	m11 5
#define	m12 6
#define	m13 7
#define m20 8
#define	m21 9
#define	m22 10
#define	m23 11
#define	m30 12
#define	m31 13
#define	m32 14
#define	m33 15

using namespace ml3d;
using namespace MATH;

matrix::matrix( ) noexcept :
	row1( Vector::Zero ) , row2( Vector::Zero ) , row3( Vector::Zero ) , row4( Vector::Zero )
{
}

matrix::matrix( const vector& rhs1 , const vector& rhs2 , const vector& rhs3 , const vector& rhs4 ) noexcept :
	row1( rhs1 ) , row2( rhs2 ) , row3( rhs3 ) , row4( rhs4 )
{
}

matrix::matrix( const matrix& rhs ) noexcept : row1( rhs.row1 ) , row2( rhs.row2 ) , row3( rhs.row3 ) , row4( rhs.row4 ) { }

matrix& matrix::operator=( const matrix& rhs )
{
	row1 = rhs.row1;
	row2 = rhs.row2;
	row3 = rhs.row3;
	row4 = rhs.row4;
	return *this;
}

matrix matrix::operator-( ) const
{
	return matrix(
		-this->row1 ,
		-this->row2 ,
		-this->row3 ,
		-this->row4 );
}

matrix matrix::operator-( const matrix& rhs ) const
{
	return matrix(
		this->row1 - rhs.row1 ,
		this->row2 - rhs.row2 ,
		this->row3 - rhs.row3 ,
		this->row4 - rhs.row4 );
}

matrix& matrix::operator-=( const matrix& rhs )
{
	this->row1 -= rhs.row1;
	this->row2 -= rhs.row2;
	this->row3 -= rhs.row3;
	this->row4 -= rhs.row4;
	return *this;
}

matrix matrix::operator+( const matrix& rhs ) const
{
	return matrix(
		this->row1 + rhs.row1 ,
		this->row2 + rhs.row2 ,
		this->row3 + rhs.row3 ,
		this->row4 + rhs.row4 );
}

matrix& matrix::operator+=( const matrix& rhs )
{
	this->row1 += rhs.row1;
	this->row2 += rhs.row2;
	this->row3 += rhs.row3;
	this->row4 += rhs.row4;
	return *this;
}

matrix matrix::operator*( const float& rhs ) const
{
	return matrix(
		this->row1 * rhs ,
		this->row2 * rhs ,
		this->row3 * rhs ,
		this->row4 * rhs );
}

matrix& matrix::operator*=( const float& rhs )
{
	this->row1 *= rhs;
	this->row2 *= rhs;
	this->row3 *= rhs;
	this->row4 *= rhs;
	return *this;
}

matrix matrix::operator*( const matrix& rhs ) const
{
	matrix output;

	output.row1 = {
		m[ m00 ] * rhs.m[ m00 ] + m[ m01 ] * rhs.m[ m10 ] + m[ m02 ] * rhs.m[ m20 ] + m[ m03 ] * rhs.m[ m30 ],
		m[ m00 ] * rhs.m[ m01 ] + m[ m01 ] * rhs.m[ m11 ] + m[ m02 ] * rhs.m[ m21 ] + m[ m03 ] * rhs.m[ m31 ],
		m[ m00 ] * rhs.m[ m02 ] + m[ m01 ] * rhs.m[ m12 ] + m[ m02 ] * rhs.m[ m22 ] + m[ m03 ] * rhs.m[ m32 ],
		m[ m00 ] * rhs.m[ m03 ] + m[ m01 ] * rhs.m[ m13 ] + m[ m02 ] * rhs.m[ m23 ] + m[ m03 ] * rhs.m[ m33 ] };

	output.row2 = {
		m[ m10 ] * rhs.m[ m00 ] + m[ m11 ] * rhs.m[ m10 ] + m[ m12 ] * rhs.m[ m20 ] + m[ m13 ] * rhs.m[ m30 ] ,
		m[ m10 ] * rhs.m[ m01 ] + m[ m11 ] * rhs.m[ m11 ] + m[ m12 ] * rhs.m[ m21 ] + m[ m13 ] * rhs.m[ m31 ] ,
		m[ m10 ] * rhs.m[ m02 ] + m[ m11 ] * rhs.m[ m12 ] + m[ m12 ] * rhs.m[ m22 ] + m[ m13 ] * rhs.m[ m32 ] ,
		m[ m10 ] * rhs.m[ m03 ] + m[ m11 ] * rhs.m[ m13 ] + m[ m12 ] * rhs.m[ m23 ] + m[ m13 ] * rhs.m[ m33 ] };

	output.row3 = {
		m[ m20 ] * rhs.m[ m00 ] + m[ m21 ] * rhs.m[ m10 ] + m[ m22 ] * rhs.m[ m20 ] + m[ m23 ] * rhs.m[ m30 ] ,
		m[ m20 ] * rhs.m[ m01 ] + m[ m21 ] * rhs.m[ m11 ] + m[ m22 ] * rhs.m[ m21 ] + m[ m23 ] * rhs.m[ m31 ] ,
		m[ m20 ] * rhs.m[ m02 ] + m[ m21 ] * rhs.m[ m12 ] + m[ m22 ] * rhs.m[ m22 ] + m[ m23 ] * rhs.m[ m32 ] ,
		m[ m20 ] * rhs.m[ m03 ] + m[ m21 ] * rhs.m[ m13 ] + m[ m22 ] * rhs.m[ m23 ] + m[ m23 ] * rhs.m[ m33 ] };

	output.row4 = {
		m[ m30 ] * rhs.m[ m00 ] + m[ m31 ] * rhs.m[ m10 ] + m[ m32 ] * rhs.m[ m20 ] + m[ m33 ] * rhs.m[ m30 ] ,
		m[ m30 ] * rhs.m[ m01 ] + m[ m31 ] * rhs.m[ m11 ] + m[ m32 ] * rhs.m[ m21 ] + m[ m33 ] * rhs.m[ m31 ] ,
		m[ m30 ] * rhs.m[ m02 ] + m[ m31 ] * rhs.m[ m12 ] + m[ m32 ] * rhs.m[ m22 ] + m[ m33 ] * rhs.m[ m32 ] ,
		m[ m30 ] * rhs.m[ m03 ] + m[ m31 ] * rhs.m[ m13 ] + m[ m32 ] * rhs.m[ m23 ] + m[ m33 ] * rhs.m[ m33 ] };

	return output;
}

matrix& matrix::operator*=( const matrix& rhs )
{
	row1 = {
		m[ m00 ] * rhs.m[ m00 ] + m[ m01 ] * rhs.m[ m10 ] + m[ m02 ] * rhs.m[ m20 ] + m[ m03 ] * rhs.m[ m30 ],
		m[ m00 ] * rhs.m[ m01 ] + m[ m01 ] * rhs.m[ m11 ] + m[ m02 ] * rhs.m[ m21 ] + m[ m03 ] * rhs.m[ m31 ],
		m[ m00 ] * rhs.m[ m02 ] + m[ m01 ] * rhs.m[ m12 ] + m[ m02 ] * rhs.m[ m22 ] + m[ m03 ] * rhs.m[ m32 ],
		m[ m00 ] * rhs.m[ m03 ] + m[ m01 ] * rhs.m[ m13 ] + m[ m02 ] * rhs.m[ m23 ] + m[ m03 ] * rhs.m[ m33 ] };

	row2 = {
		m[ m10 ] * rhs.m[ m00 ] + m[ m11 ] * rhs.m[ m10 ] + m[ m12 ] * rhs.m[ m20 ] + m[ m13 ] * rhs.m[ m30 ] ,
		m[ m10 ] * rhs.m[ m01 ] + m[ m11 ] * rhs.m[ m11 ] + m[ m12 ] * rhs.m[ m21 ] + m[ m13 ] * rhs.m[ m31 ] ,
		m[ m10 ] * rhs.m[ m02 ] + m[ m11 ] * rhs.m[ m12 ] + m[ m12 ] * rhs.m[ m22 ] + m[ m13 ] * rhs.m[ m32 ] ,
		m[ m10 ] * rhs.m[ m03 ] + m[ m11 ] * rhs.m[ m13 ] + m[ m12 ] * rhs.m[ m23 ] + m[ m13 ] * rhs.m[ m33 ] };

	row3 = {
		m[ m20 ] * rhs.m[ m00 ] + m[ m21 ] * rhs.m[ m10 ] + m[ m22 ] * rhs.m[ m20 ] + m[ m23 ] * rhs.m[ m30 ] ,
		m[ m20 ] * rhs.m[ m01 ] + m[ m21 ] * rhs.m[ m11 ] + m[ m22 ] * rhs.m[ m21 ] + m[ m23 ] * rhs.m[ m31 ] ,
		m[ m20 ] * rhs.m[ m02 ] + m[ m21 ] * rhs.m[ m12 ] + m[ m22 ] * rhs.m[ m22 ] + m[ m23 ] * rhs.m[ m32 ] ,
		m[ m20 ] * rhs.m[ m03 ] + m[ m21 ] * rhs.m[ m13 ] + m[ m22 ] * rhs.m[ m23 ] + m[ m23 ] * rhs.m[ m33 ] };

	row4 = {
		m[ m30 ] * rhs.m[ m00 ] + m[ m31 ] * rhs.m[ m10 ] + m[ m32 ] * rhs.m[ m20 ] + m[ m33 ] * rhs.m[ m30 ] ,
		m[ m30 ] * rhs.m[ m01 ] + m[ m31 ] * rhs.m[ m11 ] + m[ m32 ] * rhs.m[ m21 ] + m[ m33 ] * rhs.m[ m31 ] ,
		m[ m30 ] * rhs.m[ m02 ] + m[ m31 ] * rhs.m[ m12 ] + m[ m32 ] * rhs.m[ m22 ] + m[ m33 ] * rhs.m[ m32 ] ,
		m[ m30 ] * rhs.m[ m03 ] + m[ m31 ] * rhs.m[ m13 ] + m[ m32 ] * rhs.m[ m23 ] + m[ m33 ] * rhs.m[ m33 ] };

	return *this;
}

bool matrix::operator==( const matrix& rhs )
{
	return
		this->row1 == rhs.row1 &&
		this->row2 == rhs.row2 &&
		this->row3 == rhs.row3 &&
		this->row4 == rhs.row4;
}

bool matrix::operator!=( const matrix& rhs )
{
	return
		this->row1 != rhs.row1 ||
		this->row2 != rhs.row2 ||
		this->row3 != rhs.row3 ||
		this->row4 != rhs.row4;
}

float matrix::operator[]( const unsigned int index )
{
	return m[ index ];
}

const float matrix::operator[]( const unsigned int index ) const
{
	return m[ index ];
}


matrix matrix::Translate( const vector& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ rhs.x, rhs.y, rhs.z, 1.0f } );
}

matrix matrix::Translate( const float& x , const float& y , const float& z )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ x, y, z, 1.0f } );
}

matrix matrix::TranslateX( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ rhs, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::TranslateY( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, rhs, 0.0f, 1.0f } );
}

matrix matrix::TranslateZ( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, rhs, 1.0f } );
}

matrix matrix::Scale( const vector& rhs )
{
	return matrix(
		{ rhs.x, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, rhs.y, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, rhs.z, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::Scale( const float& x , const float& y , const float& z )
{
	return matrix(
		{ x, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, y, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, z, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::ScaleX( const float& rhs )
{
	return matrix(
		{ rhs, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::ScaleY( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, rhs, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::ScaleZ( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, rhs, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::Rotate( const vector& rhs )
{
	float cosX = cosf( rhs.x );
	float cosY = cosf( rhs.y );
	float cosZ = cosf( rhs.z );

	float sinX = sinf( rhs.x );
	float sinY = sinf( rhs.y );
	float sinZ = sinf( rhs.z );

	return matrix(
		{ cosY * cosZ, sinX * sinY * cosZ + cosX * sinZ, -cosX * sinY * sinZ + sinX * sinZ, 0.0f } ,
		{ -cosY * sinZ, -sinX * sinY * sinZ + cosX * cosZ, cosX * sinY * sinZ + sinX * cosZ, 0.0f } ,
		{ sinY, -sinX * cosY, cosX * cosY, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::Rotate( const float& x , const float& y , const float& z )
{
	float cosX = cosf( x );
	float cosY = cosf( y );
	float cosZ = cosf( z );

	float sinX = sinf( x );
	float sinY = sinf( y );
	float sinZ = sinf( z );

	return matrix(
		{ cosY * cosZ, sinX * sinY * cosZ + cosX * sinZ, -cosX * sinY * sinZ + sinX * sinZ, 0.0f } ,
		{ -cosY * sinZ, -sinX * sinY * sinZ + cosX * cosZ, cosX * sinY * sinZ + sinX * cosZ, 0.0f } ,
		{ sinY, -sinX * cosY, cosX * cosY, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::RotateX( const float& rhs )
{
	float sinRHS = sinf( rhs );
	float cosRHS = cosf( rhs );

	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, cosRHS, sinRHS, 0.0f } ,
		{ 0.0f, -sinRHS, cosRHS, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::RotateY( const float& rhs )
{
	float sinRHS = sinf( rhs );
	float cosRHS = cosf( rhs );

	return matrix(
		{ cosRHS, 0.0f, -sinRHS, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ sinRHS, 0.0f, cosRHS, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::RotateZ( const float& rhs )
{
	float sinRHS = sinf( rhs );
	float cosRHS = cosf( rhs );

	return matrix(
		{ cosRHS, sinRHS, 0.0f, 0.0f } ,
		{ -sinRHS, cosRHS, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix matrix::Transpose( const matrix & rhs )
{
	return matrix(
		{ rhs.m[ m00 ], rhs.m[ m10 ], rhs.m[ m20 ], rhs.m[ m30 ] } ,
		{ rhs.m[ m01 ], rhs.m[ m11 ], rhs.m[ m21 ], rhs.m[ m31 ] } ,
		{ rhs.m[ m02 ], rhs.m[ m12 ], rhs.m[ m22 ], rhs.m[ m32 ] } ,
		{ rhs.m[ m03 ], rhs.m[ m13 ], rhs.m[ m23 ], rhs.m[ m33 ] } );
}

float matrix::Determinant( const matrix & rhs )
{
	return
		rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m21 ] * rhs.m[ m30 ] - rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m21 ] * rhs.m[ m30 ] -
		rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m22 ] * rhs.m[ m30 ] + rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m22 ] * rhs.m[ m30 ] +
		rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m23 ] * rhs.m[ m30 ] - rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m23 ] * rhs.m[ m30 ] -
		rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m20 ] * rhs.m[ m31 ] + rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m20 ] * rhs.m[ m31 ] +
		rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m22 ] * rhs.m[ m31 ] - rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m22 ] * rhs.m[ m31 ] -
		rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m23 ] * rhs.m[ m31 ] + rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m23 ] * rhs.m[ m31 ] +
		rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m20 ] * rhs.m[ m32 ] - rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m20 ] * rhs.m[ m32 ] -
		rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m21 ] * rhs.m[ m32 ] + rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m21 ] * rhs.m[ m32 ] +
		rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m23 ] * rhs.m[ m32 ] - rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m23 ] * rhs.m[ m32 ] -
		rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m20 ] * rhs.m[ m33 ] + rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m20 ] * rhs.m[ m33 ] +
		rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m21 ] * rhs.m[ m33 ] - rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m21 ] * rhs.m[ m33 ] -
		rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m22 ] * rhs.m[ m33 ] + rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m22 ] * rhs.m[ m33 ];
}

matrix matrix::Inverse( const matrix & rhs )
{
	matrix inv(
		{
			rhs.m[ m11 ] * rhs.m[ m22 ] * rhs.m[ m33 ] + rhs.m[ m12 ] * rhs.m[ m23 ] * rhs.m[ m31 ] + rhs.m[ m13 ] * rhs.m[ m21 ] * rhs.m[ m32 ] - rhs.m[ m11 ] * rhs.m[ m23 ] * rhs.m[ m32 ] - rhs.m[ m12 ] * rhs.m[ m21 ] * rhs.m[ m33 ] - rhs.m[ m13 ] * rhs.m[ m22 ] * rhs.m[ m31 ],
			rhs.m[ m01 ] * rhs.m[ m23 ] * rhs.m[ m32 ] + rhs.m[ m02 ] * rhs.m[ m21 ] * rhs.m[ m33 ] + rhs.m[ m03 ] * rhs.m[ m22 ] * rhs.m[ m31 ] - rhs.m[ m01 ] * rhs.m[ m22 ] * rhs.m[ m33 ] - rhs.m[ m02 ] * rhs.m[ m23 ] * rhs.m[ m31 ] - rhs.m[ m03 ] * rhs.m[ m21 ] * rhs.m[ m32 ],
			rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m33 ] + rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m31 ] + rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m32 ] - rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m32 ] - rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m33 ] - rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m31 ],
			rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m22 ] + rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m23 ] + rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m21 ] - rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m23 ] - rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m21 ] - rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m22 ] } ,

		{
			rhs.m[ m10 ] * rhs.m[ m23 ] * rhs.m[ m32 ] + rhs.m[ m12 ] * rhs.m[ m20 ] * rhs.m[ m33 ] + rhs.m[ m13 ] * rhs.m[ m22 ] * rhs.m[ m30 ] - rhs.m[ m10 ] * rhs.m[ m22 ] * rhs.m[ m33 ] - rhs.m[ m12 ] * rhs.m[ m23 ] * rhs.m[ m30 ] - rhs.m[ m13 ] * rhs.m[ m20 ] * rhs.m[ m32 ] ,
			rhs.m[ m00 ] * rhs.m[ m22 ] * rhs.m[ m33 ] + rhs.m[ m02 ] * rhs.m[ m23 ] * rhs.m[ m30 ] + rhs.m[ m03 ] * rhs.m[ m20 ] * rhs.m[ m32 ] - rhs.m[ m00 ] * rhs.m[ m23 ] * rhs.m[ m32 ] - rhs.m[ m02 ] * rhs.m[ m20 ] * rhs.m[ m33 ] - rhs.m[ m03 ] * rhs.m[ m22 ] * rhs.m[ m30 ] ,
			rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m32 ] + rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m33 ] + rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m30 ] - rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m33 ] - rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m30 ] - rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m32 ] ,
			rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m23 ] + rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m20 ] + rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m22 ] - rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m22 ] - rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m23 ] - rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m20 ] } ,

		{
			rhs.m[ m10 ] * rhs.m[ m21 ] * rhs.m[ m33 ] + rhs.m[ m11 ] * rhs.m[ m23 ] * rhs.m[ m30 ] + rhs.m[ m13 ] * rhs.m[ m20 ] * rhs.m[ m31 ] - rhs.m[ m10 ] * rhs.m[ m23 ] * rhs.m[ m31 ] - rhs.m[ m11 ] * rhs.m[ m20 ] * rhs.m[ m33 ] - rhs.m[ m13 ] * rhs.m[ m21 ] * rhs.m[ m30 ] ,
			rhs.m[ m00 ] * rhs.m[ m23 ] * rhs.m[ m31 ] + rhs.m[ m01 ] * rhs.m[ m20 ] * rhs.m[ m33 ] + rhs.m[ m03 ] * rhs.m[ m21 ] * rhs.m[ m30 ] - rhs.m[ m00 ] * rhs.m[ m21 ] * rhs.m[ m33 ] - rhs.m[ m01 ] * rhs.m[ m23 ] * rhs.m[ m30 ] - rhs.m[ m03 ] * rhs.m[ m20 ] * rhs.m[ m31 ] ,
			rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m33 ] + rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m30 ] + rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m31 ] - rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m31 ] - rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m33 ] - rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m30 ] ,
			rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m21 ] + rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m23 ] + rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m20 ] - rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m23 ] - rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m20 ] - rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m21 ] } ,

		{
			rhs.m[ m10 ] * rhs.m[ m22 ] * rhs.m[ m31 ] + rhs.m[ m11 ] * rhs.m[ m20 ] * rhs.m[ m32 ] + rhs.m[ m12 ] * rhs.m[ m21 ] * rhs.m[ m30 ] - rhs.m[ m10 ] * rhs.m[ m21 ] * rhs.m[ m32 ] - rhs.m[ m11 ] * rhs.m[ m22 ] * rhs.m[ m30 ] - rhs.m[ m12 ] * rhs.m[ m20 ] * rhs.m[ m31 ] ,
			rhs.m[ m00 ] * rhs.m[ m21 ] * rhs.m[ m32 ] + rhs.m[ m01 ] * rhs.m[ m22 ] * rhs.m[ m30 ] + rhs.m[ m02 ] * rhs.m[ m20 ] * rhs.m[ m31 ] - rhs.m[ m00 ] * rhs.m[ m22 ] * rhs.m[ m31 ] - rhs.m[ m01 ] * rhs.m[ m20 ] * rhs.m[ m32 ] - rhs.m[ m02 ] * rhs.m[ m21 ] * rhs.m[ m30 ] ,
			rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m31 ] + rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m32 ] + rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m30 ] - rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m32 ] - rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m30 ] - rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m31 ] ,
			rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m22 ] + rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m20 ] + rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m21 ] - rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m21 ] - rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m22 ] - rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m20 ] } );

	float det = vector( rhs.m[ 0 ] , rhs.m[ 1 ] , rhs.m[ 2 ] ) * vector( inv.m[ 0 ] , inv.m[ 1 ] , inv.m[ 2 ] );

	if( det == 0.0f )
	{
		return rhs;
	}

	det = 1.0F / det;
	return inv * det;
}

matrix matrix::Projection( const float& t_aspect_ratio, const float& t_fov, const float& t_near, const float& t_far )
{
	float fov = 1.0f / atanf( 0.5f * t_fov );
	float deltaZ = 1.0f / ( t_far - t_near );

	return matrix(
		{ fov / t_aspect_ratio, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, fov, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, t_far * deltaZ, 1.0f } ,
		{ 0.0f, 0.0f, -( t_far * t_near ) * deltaZ, 1.0f } );
}

matrix matrix::Orthographic( const float& t_near, const float& t_far )
{
	float deltaZ = 1.0f / ( t_far - t_near );

	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, -2.0f * deltaZ, -( t_far + t_near ) * deltaZ } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

#undef m00
#undef m01
#undef m02
#undef m03
#undef m10
#undef m11
#undef m12
#undef m13
#undef m20
#undef m21
#undef m22
#undef m23
#undef m30
#undef m31
#undef m32
#undef m33

#endif // ml3d_MATH_USE_RH