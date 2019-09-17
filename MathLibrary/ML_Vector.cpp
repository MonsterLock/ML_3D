#include "ML_Vector.h"

namespace ml3d
{
	namespace MATH
	{
		ml3d::MATH::vector::vector( ) noexcept
			: x( 0.0f ) , y( 0.0f ) , z( 0.0f ) , w( 0.0f )
		{
		}

		vector::vector( const float& x , const float& y ) noexcept
			: x( x ) , y( y ) , z( 0.0f ) , w( 0.0f )
		{
		}

		vector::vector( const float& x , const float& y , const float& z ) noexcept
			: x( x ) , y( y ) , z( z ) , w( 0.0f )
		{
		}

		vector::vector( const float& x , const float& y , const float& z , const float& w ) noexcept
			: x( x ) , y( y ) , z( z ) , w( w )
		{
		}

		vector::vector( const vector& rhs ) noexcept
			: x( rhs.x ) , y( rhs.y ) , z( rhs.z ) , w( rhs.w )
		{
		}

		vector& vector::operator=( const vector& rhs )
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->w = rhs.w;
			return *this;
		}

		vector vector::operator+( const vector& rhs ) const
		{
			return vector(
				this->x + rhs.x ,
				this->y + rhs.y ,
				this->z + rhs.z ,
				this->w + rhs.w );
		}

		vector& vector::operator+=( const vector& rhs )
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			this->w += rhs.w;
			return *this;
		}

		vector vector::operator-( ) const
		{
			return vector(
				-this->x ,
				-this->y ,
				-this->z ,
				-this->w );
		}

		vector vector::operator-( const vector& rhs ) const
		{
			return vector(
				this->x - rhs.x ,
				this->y - rhs.y ,
				this->z - rhs.z ,
				this->w - rhs.w );
		}

		vector& vector::operator-=( const vector& rhs )
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			this->w -= rhs.w;
			return *this;
		}

		vector vector::operator*( const float& rhs ) const
		{
			return vector(
				this->x * rhs ,
				this->y * rhs ,
				this->z * rhs ,
				this->w * rhs );
		}

		vector& vector::operator*=( const float& rhs )
		{
			this->x *= rhs;
			this->y *= rhs;
			this->z *= rhs;
			this->w *= rhs;
			return *this;
		}

		vector vector::operator/( const float& rhs ) const
		{
			float inverse = 1.0f / rhs;
			return vector(
				this->x * inverse ,
				this->y * inverse ,
				this->z * inverse ,
				this->w * inverse );
		}

		vector& vector::operator/=( const float& rhs )
		{
			float inverse = 1.0f / rhs;
			this->x *= inverse;
			this->y *= inverse;
			this->z *= inverse;
			this->w *= inverse;
			return *this;
		}

		float vector::operator*( const vector& rhs ) const
		{
			return
				this->x * rhs.x +
				this->y * rhs.y +
				this->z * rhs.z +
				this->w * rhs.w;
		}

		bool vector::operator==( const vector& rhs )
		{
			return
				IsAboutEqual( this->x , rhs.x ) &&
				IsAboutEqual( this->y , rhs.y ) &&
				IsAboutEqual( this->z , rhs.z ) &&
				IsAboutEqual( this->w , rhs.w );
		}

		bool vector::operator!=( const vector& rhs )
		{
			return
				!( IsAboutEqual( this->x , rhs.x ) &&
				   IsAboutEqual( this->y , rhs.y ) &&
				   IsAboutEqual( this->z , rhs.z ) &&
				   IsAboutEqual( this->w , rhs.w ) );
		}

		float vector::operator[]( const unsigned int index )
		{
			return e[ index ];
		}

		const float vector::operator[]( const unsigned int index ) const
		{
			return e[ index ];
		}

		float vector::AngleBetween( const vector & lhs , const vector & rhs )
		{

			float lengthLHS = lhs.Length( );
			float lengthRHS = rhs.Length( );

			if( IsAboutZero( lengthLHS ) || IsAboutZero( lengthRHS ) )
			{
				return 0.0f;
			}

			return acos( lhs * rhs / ( lengthLHS * lengthRHS ) );
		}

		vector vector::Average( const vector& lhs , const vector& rhs )
		{
			return vector(
				Avg( lhs.x , rhs.x ) ,
				Avg( lhs.y , rhs.y ) ,
				Avg( lhs.z , rhs.z ) ,
				Avg( lhs.w , rhs.w ) );
		}

		float vector::Component( const vector& lhs , const vector& rhs )
		{
			return lhs * Normalize( rhs );
		}

		vector vector::Cross( const vector& lhs , const vector& rhs )
		{
			return vector(
				lhs.y * rhs.z - rhs.y * lhs.z ,
				rhs.x * lhs.z - lhs.x * rhs.z ,
				lhs.x * rhs.y - rhs.x * lhs.y ,
				1.0f );
		}

		float vector::LengthSq( ) const
		{
			return
				Square( this->x ) +
				Square( this->y ) +
				Square( this->z ) +
				Square( this->w );
		}

		float vector::Length( ) const
		{
			return sqrt(
				Square( this->x ) +
				Square( this->y ) +
				Square( this->z ) +
				Square( this->w ) );
		}

		vector vector::LerpVector( const vector& lhs , const vector& rhs , const float t )
		{
			return vector(
				Lerp( lhs.x , rhs.x , t ) ,
				Lerp( lhs.y , rhs.y , t ) ,
				Lerp( lhs.z , rhs.z , t ) ,
				Lerp( lhs.w , rhs.w , t ) );
		}

		vector vector::Min( const vector& lhs , const vector& rhs )
		{
			return vector( Lesser( lhs.x , rhs.x ) , Lesser( lhs.y , rhs.y ) , Lesser( lhs.z , rhs.z ) , Lesser( lhs.w , rhs.w ) );
		}

		vector vector::Max( const vector& lhs , const vector& rhs )
		{
			return vector( Greater( lhs.x , rhs.x ) , Greater( lhs.y , rhs.y ) , Greater( lhs.z , rhs.z ) , Greater( lhs.w , rhs.w ) );
		}

		void vector::Normalize( )
		{
			if( IsAboutZero( LengthSq( ) ) )
			{
				return;
			}

			float length = 1.0f / Length( );
			*this = vector(
				this->x * length ,
				this->y * length ,
				this->z * length ,
				this->w * length );
		}

		vector vector::Normalize( const vector& rhs )
		{
			if( IsAboutZero( rhs.LengthSq( ) ) )
			{
				return rhs;
			}

			float length = 1.0f / rhs.Length( );
			return vector(
				rhs.x * length ,
				rhs.y * length ,
				rhs.z * length ,
				rhs.w * length );
		}

		vector vector::Projection( const vector& lhs , const vector& rhs )
		{
			return Normalize( rhs ) * Component( lhs , rhs );
		}

		vector vector::Reflection( const vector& lhs , const vector& rhs )
		{
			return ( IsAboutZero( rhs.Length( ) ) ) ?
				-lhs : ( Projection( lhs , rhs ) * 2 ) - lhs;
		}
	} // end namespace MATH
} // namespace ml3d
