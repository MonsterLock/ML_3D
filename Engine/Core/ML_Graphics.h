#pragma once
#include <string>
#include <vector>

namespace ml3d
{
	namespace GFX
	{
		struct input_desc
		{
			std::vector<std::string> semantic_name;
			std::vector<uint8_t> format;

			void Add( const std::string& t_semantic_name , uint8_t t_format )
			{
				semantic_name.push_back( t_semantic_name );
				format.push_back( t_format );
			}
		};

		struct vertices
		{
			float* data;
			uint32_t size;
		};

		struct indices
		{
			uint32_t* data;
			uint32_t size;
		};

		struct texture_desc
		{
			std::string file;
			uint8_t dimension;
		};

		struct view_data
		{
			enum
			{
				VIEW = 0,
				PROJECTION,
				VIEW_PROJECTION
			};
		};

		class Graphics
		{
			struct impl;
			impl* m_graphics;

		public:
			Graphics( void* , unsigned int , unsigned int ) noexcept;

			void BeginFrame( );
			void EndFrame( );

			void UpdateView( const float*, unsigned int );

			void EnableDepth( bool );
			void SetFillMode( unsigned int );

			void SetRenderer( unsigned int );

			void CreateInputLayout( const input_desc* );

			bool LoadModel( const input_desc* , const float* );
			bool LoadModel( const input_desc* , const float* );

			bool LoadTexture( const texture_desc* );


		};
	}
}