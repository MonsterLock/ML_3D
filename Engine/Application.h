#pragma once
#include "Core/ML_Window.h"

namespace ml3d
{
	class Application
	{
		std::shared_ptr<CORE::WindowMain> m_window;

	public:
		Application( ) noexcept : m_window( nullptr ) { }

		void Initialize( )
		{
			m_window = std::shared_ptr<CORE::WindowMain>( new CORE::WindowMain );
			m_window->Create();

		}

		void Update( )
		{
			MSG msg = { 0 };
			ZeroMemory( &msg, sizeof( MSG ) );
			PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

			while( msg.message != WM_QUIT )
			{
				if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else
				{

				}
			}
		}

		void Shutdown( );
	};
}