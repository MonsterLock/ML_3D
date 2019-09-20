/*
R.A. Bickell [https://github.com/MonsterLock]
ML_Matrix.cpp Last Updated: 2019-09-19 03::07::51 AM
*/
#include "ML_Matrix.h"

#include <cstring>

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

using namespace ML::MATH::Matrix;

matrix::matrix( ) noexcept :
	row{ Vector::Zero, Vector::Zero, Vector::Zero, Vector::Zero }
{
}

matrix::matrix( const vector& rhs1 , const vector& rhs2 , const vector& rhs3 , const vector& rhs4 ) noexcept :
	row{ rhs1, rhs2, rhs3, rhs4 }
{
}

matrix::matrix( const matrix& rhs ) noexcept :
	row{ rhs[ 0 ], rhs[ 1 ], rhs[ 2 ], rhs[ 3 ] }
{
}

ML::MATH::Matrix::matrix::matrix( const float * rhs )
{
	memcpy( m , rhs , 64 );
}

bool matrix::operator==( const matrix& rhs )
{
	return
		this->row[ 0 ] == rhs[ 0 ] &&
		this->row[ 1 ] == rhs[ 1 ] &&
		this->row[ 2 ] == rhs[ 2 ] &&
		this->row[ 3 ] == rhs[ 3 ];
}

bool matrix::operator!=( const matrix& rhs )
{
	return
		this->row[ 0 ] != rhs[ 0 ] ||
		this->row[ 1 ] != rhs[ 1 ] ||
		this->row[ 2 ] != rhs[ 2 ] ||
		this->row[ 3 ] != rhs[ 3 ];
}

matrix& matrix::operator=( const matrix& rhs )
{
	memcpy( m , rhs.m , 64 );
	return *this;
}

vector matrix::operator[]( const unsigned int index )
{
	return row[ index ];
}

const vector matrix::operator[]( const unsigned int index ) const
{
	return row[ index ];
}

float ML::MATH::Matrix::matrix::operator()( const unsigned int t_row , const unsigned int t_column )
{
	return row[ t_row ][ t_column ];
}

const float ML::MATH::Matrix::matrix::operator()( const unsigned int t_row , const unsigned int t_column ) const
{
	return row[ t_row ][ t_column ];
}

matrix matrix::operator+( const matrix& rhs ) const
{
	return matrix(
		this->row[ 0 ] + rhs.row[ 0 ] ,
		this->row[ 1 ] + rhs.row[ 1 ] ,
		this->row[ 2 ] + rhs.row[ 2 ] ,
		this->row[ 3 ] + rhs.row[ 3 ] );
}

matrix& matrix::operator+=( const matrix& rhs )
{
	this->row[ 0 ] += rhs.row[ 0 ];
	this->row[ 1 ] += rhs.row[ 1 ];
	this->row[ 2 ] += rhs.row[ 2 ];
	this->row[ 3 ] += rhs.row[ 3 ];
	return *this;
}

matrix matrix::operator-( ) const
{
	return matrix(
		-this->row[ 0 ] ,
		-this->row[ 1 ] ,
		-this->row[ 2 ] ,
		-this->row[ 3 ] );
}

matrix matrix::operator-( const matrix& rhs ) const
{
	return matrix(
		this->row[ 0 ] - rhs.row[ 0 ] ,
		this->row[ 1 ] - rhs.row[ 1 ] ,
		this->row[ 2 ] - rhs.row[ 2 ] ,
		this->row[ 3 ] - rhs.row[ 3 ] );
}

matrix& matrix::operator-=( const matrix& rhs )
{
	this->row[ 0 ] -= rhs.row[ 0 ];
	this->row[ 1 ] -= rhs.row[ 1 ];
	this->row[ 2 ] -= rhs.row[ 2 ];
	this->row[ 3 ] -= rhs.row[ 3 ];
	return *this;
}

matrix matrix::operator*( const float& rhs ) const
{
	return matrix(
		this->row[ 0 ] * rhs ,
		this->row[ 1 ] * rhs ,
		this->row[ 2 ] * rhs ,
		this->row[ 3 ] * rhs );
}

matrix& matrix::operator*=( const float& rhs )
{
	this->row[ 0 ] *= rhs;
	this->row[ 1 ] *= rhs;
	this->row[ 2 ] *= rhs;
	this->row[ 3 ] *= rhs;
	return *this;
}

matrix matrix::operator*( const matrix& rhs ) const
{
	return matrix(
		{
			m[ m00 ] * rhs.m[ m00 ] + m[ m01 ] * rhs.m[ m10 ] + m[ m02 ] * rhs.m[ m20 ] + m[ m03 ] * rhs.m[ m30 ],
			m[ m00 ] * rhs.m[ m01 ] + m[ m01 ] * rhs.m[ m11 ] + m[ m02 ] * rhs.m[ m21 ] + m[ m03 ] * rhs.m[ m31 ],
			m[ m00 ] * rhs.m[ m02 ] + m[ m01 ] * rhs.m[ m12 ] + m[ m02 ] * rhs.m[ m22 ] + m[ m03 ] * rhs.m[ m32 ],
			m[ m00 ] * rhs.m[ m03 ] + m[ m01 ] * rhs.m[ m13 ] + m[ m02 ] * rhs.m[ m23 ] + m[ m03 ] * rhs.m[ m33 ] } ,
		{
			m[ m10 ] * rhs.m[ m00 ] + m[ m11 ] * rhs.m[ m10 ] + m[ m12 ] * rhs.m[ m20 ] + m[ m13 ] * rhs.m[ m30 ] ,
			m[ m10 ] * rhs.m[ m01 ] + m[ m11 ] * rhs.m[ m11 ] + m[ m12 ] * rhs.m[ m21 ] + m[ m13 ] * rhs.m[ m31 ] ,
			m[ m10 ] * rhs.m[ m02 ] + m[ m11 ] * rhs.m[ m12 ] + m[ m12 ] * rhs.m[ m22 ] + m[ m13 ] * rhs.m[ m32 ] ,
			m[ m10 ] * rhs.m[ m03 ] + m[ m11 ] * rhs.m[ m13 ] + m[ m12 ] * rhs.m[ m23 ] + m[ m13 ] * rhs.m[ m33 ] } ,
		{
			m[ m20 ] * rhs.m[ m00 ] + m[ m21 ] * rhs.m[ m10 ] + m[ m22 ] * rhs.m[ m20 ] + m[ m23 ] * rhs.m[ m30 ] ,
			m[ m20 ] * rhs.m[ m01 ] + m[ m21 ] * rhs.m[ m11 ] + m[ m22 ] * rhs.m[ m21 ] + m[ m23 ] * rhs.m[ m31 ] ,
			m[ m20 ] * rhs.m[ m02 ] + m[ m21 ] * rhs.m[ m12 ] + m[ m22 ] * rhs.m[ m22 ] + m[ m23 ] * rhs.m[ m32 ] ,
			m[ m20 ] * rhs.m[ m03 ] + m[ m21 ] * rhs.m[ m13 ] + m[ m22 ] * rhs.m[ m23 ] + m[ m23 ] * rhs.m[ m33 ] } ,
		{
			m[ m30 ] * rhs.m[ m00 ] + m[ m31 ] * rhs.m[ m10 ] + m[ m32 ] * rhs.m[ m20 ] + m[ m33 ] * rhs.m[ m30 ] ,
			m[ m30 ] * rhs.m[ m01 ] + m[ m31 ] * rhs.m[ m11 ] + m[ m32 ] * rhs.m[ m21 ] + m[ m33 ] * rhs.m[ m31 ] ,
			m[ m30 ] * rhs.m[ m02 ] + m[ m31 ] * rhs.m[ m12 ] + m[ m32 ] * rhs.m[ m22 ] + m[ m33 ] * rhs.m[ m32 ] ,
			m[ m30 ] * rhs.m[ m03 ] + m[ m31 ] * rhs.m[ m13 ] + m[ m32 ] * rhs.m[ m23 ] + m[ m33 ] * rhs.m[ m33 ] } );
}

matrix& matrix::operator*=( const matrix& rhs )
{
	row[ 0 ] = {
		m[ m00 ] * rhs.m[ m00 ] + m[ m01 ] * rhs.m[ m10 ] + m[ m02 ] * rhs.m[ m20 ] + m[ m03 ] * rhs.m[ m30 ],
		m[ m00 ] * rhs.m[ m01 ] + m[ m01 ] * rhs.m[ m11 ] + m[ m02 ] * rhs.m[ m21 ] + m[ m03 ] * rhs.m[ m31 ],
		m[ m00 ] * rhs.m[ m02 ] + m[ m01 ] * rhs.m[ m12 ] + m[ m02 ] * rhs.m[ m22 ] + m[ m03 ] * rhs.m[ m32 ],
		m[ m00 ] * rhs.m[ m03 ] + m[ m01 ] * rhs.m[ m13 ] + m[ m02 ] * rhs.m[ m23 ] + m[ m03 ] * rhs.m[ m33 ] };

	row[ 1 ] = {
		m[ m10 ] * rhs.m[ m00 ] + m[ m11 ] * rhs.m[ m10 ] + m[ m12 ] * rhs.m[ m20 ] + m[ m13 ] * rhs.m[ m30 ] ,
		m[ m10 ] * rhs.m[ m01 ] + m[ m11 ] * rhs.m[ m11 ] + m[ m12 ] * rhs.m[ m21 ] + m[ m13 ] * rhs.m[ m31 ] ,
		m[ m10 ] * rhs.m[ m02 ] + m[ m11 ] * rhs.m[ m12 ] + m[ m12 ] * rhs.m[ m22 ] + m[ m13 ] * rhs.m[ m32 ] ,
		m[ m10 ] * rhs.m[ m03 ] + m[ m11 ] * rhs.m[ m13 ] + m[ m12 ] * rhs.m[ m23 ] + m[ m13 ] * rhs.m[ m33 ] };

	row[ 2 ] = {
		m[ m20 ] * rhs.m[ m00 ] + m[ m21 ] * rhs.m[ m10 ] + m[ m22 ] * rhs.m[ m20 ] + m[ m23 ] * rhs.m[ m30 ] ,
		m[ m20 ] * rhs.m[ m01 ] + m[ m21 ] * rhs.m[ m11 ] + m[ m22 ] * rhs.m[ m21 ] + m[ m23 ] * rhs.m[ m31 ] ,
		m[ m20 ] * rhs.m[ m02 ] + m[ m21 ] * rhs.m[ m12 ] + m[ m22 ] * rhs.m[ m22 ] + m[ m23 ] * rhs.m[ m32 ] ,
		m[ m20 ] * rhs.m[ m03 ] + m[ m21 ] * rhs.m[ m13 ] + m[ m22 ] * rhs.m[ m23 ] + m[ m23 ] * rhs.m[ m33 ] };

	row[ 3 ] = {
		m[ m30 ] * rhs.m[ m00 ] + m[ m31 ] * rhs.m[ m10 ] + m[ m32 ] * rhs.m[ m20 ] + m[ m33 ] * rhs.m[ m30 ] ,
		m[ m30 ] * rhs.m[ m01 ] + m[ m31 ] * rhs.m[ m11 ] + m[ m32 ] * rhs.m[ m21 ] + m[ m33 ] * rhs.m[ m31 ] ,
		m[ m30 ] * rhs.m[ m02 ] + m[ m31 ] * rhs.m[ m12 ] + m[ m32 ] * rhs.m[ m22 ] + m[ m33 ] * rhs.m[ m32 ] ,
		m[ m30 ] * rhs.m[ m03 ] + m[ m31 ] * rhs.m[ m13 ] + m[ m32 ] * rhs.m[ m23 ] + m[ m33 ] * rhs.m[ m33 ] };

	return *this;
}

std::ostream & ML::MATH::Matrix::operator<<( std::ostream & os , const matrix & rhs )
{
	os << rhs.row[ 0 ] << ", "
		<< rhs.row[ 1 ] << ", "
		<< rhs.row[ 2 ] << ", "
		<< rhs.row[ 3 ];
	return os;
}

float ML::MATH::Matrix::Determinant( const matrix & rhs )
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

matrix ML::MATH::Matrix::Inverse( const matrix & rhs )
{
	matrix inv( {
		rhs.m[ m11 ] * rhs.m[ m22 ] * rhs.m[ m33 ] + rhs.m[ m12 ] * rhs.m[ m23 ] * rhs.m[ m31 ] + rhs.m[ m13 ] * rhs.m[ m21 ] * rhs.m[ m32 ] - rhs.m[ m11 ] * rhs.m[ m23 ] * rhs.m[ m32 ] - rhs.m[ m12 ] * rhs.m[ m21 ] * rhs.m[ m33 ] - rhs.m[ m13 ] * rhs.m[ m22 ] * rhs.m[ m31 ],
		rhs.m[ m01 ] * rhs.m[ m23 ] * rhs.m[ m32 ] + rhs.m[ m02 ] * rhs.m[ m21 ] * rhs.m[ m33 ] + rhs.m[ m03 ] * rhs.m[ m22 ] * rhs.m[ m31 ] - rhs.m[ m01 ] * rhs.m[ m22 ] * rhs.m[ m33 ] - rhs.m[ m02 ] * rhs.m[ m23 ] * rhs.m[ m31 ] - rhs.m[ m03 ] * rhs.m[ m21 ] * rhs.m[ m32 ],
		rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m33 ] + rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m31 ] + rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m32 ] - rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m32 ] - rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m33 ] - rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m31 ],
		rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m22 ] + rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m23 ] + rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m21 ] - rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m23 ] - rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m21 ] - rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m22 ] } ,
{
	rhs.m[ m10 ] * rhs.m[ m23 ] * rhs.m[ m32 ] + rhs.m[ m12 ] * rhs.m[ m20 ] * rhs.m[ m33 ] + rhs.m[ m13 ] * rhs.m[ m22 ] * rhs.m[ m30 ] - rhs.m[ m10 ] * rhs.m[ m22 ] * rhs.m[ m33 ] - rhs.m[ m12 ] * rhs.m[ m23 ] * rhs.m[ m30 ] - rhs.m[ m13 ] * rhs.m[ m20 ] * rhs.m[ m32 ],
	rhs.m[ m00 ] * rhs.m[ m22 ] * rhs.m[ m33 ] + rhs.m[ m02 ] * rhs.m[ m23 ] * rhs.m[ m30 ] + rhs.m[ m03 ] * rhs.m[ m20 ] * rhs.m[ m32 ] - rhs.m[ m00 ] * rhs.m[ m23 ] * rhs.m[ m32 ] - rhs.m[ m02 ] * rhs.m[ m20 ] * rhs.m[ m33 ] - rhs.m[ m03 ] * rhs.m[ m22 ] * rhs.m[ m30 ],
	rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m32 ] + rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m33 ] + rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m30 ] - rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m33 ] - rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m30 ] - rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m32 ],
	rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m23 ] + rhs.m[ m02 ] * rhs.m[ m13 ] * rhs.m[ m20 ] + rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m22 ] - rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m22 ] - rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m23 ] - rhs.m[ m03 ] * rhs.m[ m12 ] * rhs.m[ m20 ] } ,
{
	rhs.m[ m10 ] * rhs.m[ m21 ] * rhs.m[ m33 ] + rhs.m[ m11 ] * rhs.m[ m23 ] * rhs.m[ m30 ] + rhs.m[ m13 ] * rhs.m[ m20 ] * rhs.m[ m31 ] - rhs.m[ m10 ] * rhs.m[ m23 ] * rhs.m[ m31 ] - rhs.m[ m11 ] * rhs.m[ m20 ] * rhs.m[ m33 ] - rhs.m[ m13 ] * rhs.m[ m21 ] * rhs.m[ m30 ],
	rhs.m[ m00 ] * rhs.m[ m23 ] * rhs.m[ m31 ] + rhs.m[ m01 ] * rhs.m[ m20 ] * rhs.m[ m33 ] + rhs.m[ m03 ] * rhs.m[ m21 ] * rhs.m[ m30 ] - rhs.m[ m00 ] * rhs.m[ m21 ] * rhs.m[ m33 ] - rhs.m[ m01 ] * rhs.m[ m23 ] * rhs.m[ m30 ] - rhs.m[ m03 ] * rhs.m[ m20 ] * rhs.m[ m31 ],
	rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m33 ] + rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m30 ] + rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m31 ] - rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m31 ] - rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m33 ] - rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m30 ],
	rhs.m[ m00 ] * rhs.m[ m13 ] * rhs.m[ m21 ] + rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m23 ] + rhs.m[ m03 ] * rhs.m[ m11 ] * rhs.m[ m20 ] - rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m23 ] - rhs.m[ m01 ] * rhs.m[ m13 ] * rhs.m[ m20 ] - rhs.m[ m03 ] * rhs.m[ m10 ] * rhs.m[ m21 ] } ,
		{
			rhs.m[ m10 ] * rhs.m[ m22 ] * rhs.m[ m31 ] + rhs.m[ m11 ] * rhs.m[ m20 ] * rhs.m[ m32 ] + rhs.m[ m12 ] * rhs.m[ m21 ] * rhs.m[ m30 ] - rhs.m[ m10 ] * rhs.m[ m21 ] * rhs.m[ m32 ] - rhs.m[ m11 ] * rhs.m[ m22 ] * rhs.m[ m30 ] - rhs.m[ m12 ] * rhs.m[ m20 ] * rhs.m[ m31 ],
			rhs.m[ m00 ] * rhs.m[ m21 ] * rhs.m[ m32 ] + rhs.m[ m01 ] * rhs.m[ m22 ] * rhs.m[ m30 ] + rhs.m[ m02 ] * rhs.m[ m20 ] * rhs.m[ m31 ] - rhs.m[ m00 ] * rhs.m[ m22 ] * rhs.m[ m31 ] - rhs.m[ m01 ] * rhs.m[ m20 ] * rhs.m[ m32 ] - rhs.m[ m02 ] * rhs.m[ m21 ] * rhs.m[ m30 ],
			rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m31 ] + rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m32 ] + rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m30 ] - rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m32 ] - rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m30 ] - rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m31 ],
			rhs.m[ m00 ] * rhs.m[ m11 ] * rhs.m[ m22 ] + rhs.m[ m01 ] * rhs.m[ m12 ] * rhs.m[ m20 ] + rhs.m[ m02 ] * rhs.m[ m10 ] * rhs.m[ m21 ] - rhs.m[ m00 ] * rhs.m[ m12 ] * rhs.m[ m21 ] - rhs.m[ m01 ] * rhs.m[ m10 ] * rhs.m[ m22 ] - rhs.m[ m02 ] * rhs.m[ m11 ] * rhs.m[ m20 ] } );

	float det = vector( rhs.m[ 0 ] , rhs.m[ 1 ] , rhs.m[ 2 ] , rhs.m[ 3 ] ) * vector( inv.m[ 0 ] , inv.m[ 4 ] , inv.m[ 8 ] , inv.m[ 12 ] );

	if( det == 0.0f )
	{
		return rhs;
	}

	return inv * ( 1.0f / det );
}

matrix ML::MATH::Matrix::Scale( const vector& rhs )
{
	return matrix(
		{ rhs.x, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, rhs.y, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, rhs.z, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::Scale( const float& x , const float& y , const float& z )
{
	return matrix(
		{ x, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, y, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, z, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::ScaleX( const float& rhs )
{
	return matrix(
		{ rhs, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::ScaleY( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, rhs, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::ScaleZ( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, rhs, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::Transpose( const matrix & rhs )
{
	return matrix(
		{ rhs.m[ m00 ], rhs.m[ m10 ], rhs.m[ m20 ], rhs.m[ m30 ] } ,
		{ rhs.m[ m01 ], rhs.m[ m11 ], rhs.m[ m21 ], rhs.m[ m31 ] } ,
		{ rhs.m[ m02 ], rhs.m[ m12 ], rhs.m[ m22 ], rhs.m[ m32 ] } ,
		{ rhs.m[ m03 ], rhs.m[ m13 ], rhs.m[ m23 ], rhs.m[ m33 ] } );
}

vector ML::MATH::Matrix::MatrixVector( const matrix & lhs , const vector & rhs )
{
	return vector(
		rhs * lhs[ 0 ] ,
		rhs * lhs[ 1 ] ,
		rhs * lhs[ 2 ] ,
		rhs * lhs[ 3 ] );
}

vector ML::MATH::Matrix::VectorMatrix( const vector & lhs , const matrix & rhs )
{
	vector temp_row[ 4 ] = {
		{ rhs.m[ 0 ], rhs.m[ 4 ], rhs.m[ 8 ], rhs.m[ 12 ]  },
	{ rhs.m[ 1 ], rhs.m[ 5 ], rhs.m[ 9 ], rhs.m[ 13 ]  },
	{ rhs.m[ 2 ], rhs.m[ 6 ], rhs.m[ 10 ], rhs.m[ 14 ]  },
	{ rhs.m[ 3 ], rhs.m[ 7 ], rhs.m[ 11 ], rhs.m[ 15 ]  } };

	return vector(
		lhs * temp_row[ 0 ] ,
		lhs * temp_row[ 1 ] ,
		lhs * temp_row[ 2 ] ,
		lhs * temp_row[ 3 ]
	);
}

//-------------------------------------------------------------------------------------------- LH System
matrix ML::MATH::Matrix::Translate( const vector& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ rhs.x, rhs.y, rhs.z, 1.0f } );
}

matrix ML::MATH::Matrix::Translate( const float& x , const float& y , const float& z )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ x, y, z, 1.0f } );
}

matrix ML::MATH::Matrix::TranslateX( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ rhs, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::TranslateY( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, rhs, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::TranslateZ( const float& rhs )
{
	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, rhs, 1.0f } );
}

matrix ML::MATH::Matrix::Rotate( const vector& rhs )
{
	float cosX = cosf( rhs.x );
	float cosY = cosf( rhs.y );
	float cosZ = cosf( rhs.z );

	float sinX = sinf( rhs.x );
	float sinY = sinf( rhs.y );
	float sinZ = sinf( rhs.z );

	return matrix(
		{ cosY * cosZ, cosY * sinZ, -sinY, 0.0f } ,
		{ -sinZ * cosX + cosZ * sinY * sinX, cosZ * cosX + sinZ * sinY * sinX, cosY * sinX, 0.0f } ,
		{ sinZ * sinX + cosZ * sinY * cosX, -cosZ * sinX + sinZ * sinY * cosX, cosY * cosX, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::Rotate( const float& x , const float& y , const float& z )
{
	float cosX = cosf( x );
	float cosY = cosf( y );
	float cosZ = cosf( z );

	float sinX = sinf( x );
	float sinY = sinf( y );
	float sinZ = sinf( z );

	return matrix(
		{ cosY * cosZ, cosY * sinZ, -sinY, 0.0f } ,
		{ -sinZ * cosX + cosZ * sinY * sinX, cosZ * cosX + sinZ * sinY * sinX, cosY * sinX, 0.0f } ,
		{ sinZ * sinX + cosZ * sinY * cosX, -cosZ * sinX + sinZ * sinY * cosX, cosY * cosX, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::RotateX( const float& rhs )
{
	float sinRHS = sinf( rhs );
	float cosRHS = cosf( rhs );

	return matrix(
		{ 1.0f, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, cosRHS, sinRHS, 0.0f } ,
		{ 0.0f, -sinRHS, cosRHS, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::RotateY( const float& rhs )
{
	float sinRHS = sinf( rhs );
	float cosRHS = cosf( rhs );

	return matrix(
		{ cosRHS, 0.0f, -sinRHS, 0.0f } ,
		{ 0.0f, 1.0f, 0.0f, 0.0f } ,
		{ sinRHS, 0.0f, cosRHS, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::RotateZ( const float& rhs )
{
	float sinRHS = sinf( rhs );
	float cosRHS = cosf( rhs );

	return matrix(
		{ cosRHS, sinRHS, 0.0f, 0.0f } ,
		{ -sinRHS, cosRHS, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f, 0.0f } ,
		{ 0.0f, 0.0f, 0.0f, 1.0f } );
}

matrix ML::MATH::Matrix::Projection( const float& t_fov , const float& t_aspect_ratio , const float& t_near , const float& t_far )
{
	float yScale = 1.0f / tanf( 0.5f * t_fov );
	float xScale = yScale / t_aspect_ratio;

	float deltaZ = 1.0f / ( t_far - t_near );

	return matrix(
		{ xScale, 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, yScale, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, t_far * deltaZ, 1.0f } ,
		{ 0.0f, 0.0f, -( t_near * t_far ) * deltaZ, 0.0f } );
}

matrix ML::MATH::Matrix::Orthographic( const float& width , const float& height , const float& t_near , const float& t_far )
{
	return matrix(
		{ 2.0f / width , 0.0f, 0.0f, 0.0f } ,
		{ 0.0f, 2.0f / height, 0.0f, 0.0f } ,
		{ 0.0f, 0.0f, 1.0f / ( t_far - t_near ), 0.0f } ,
		{ 0, 0, t_near / ( t_near - t_far ), 1.0f } );
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