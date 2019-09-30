#pragma once
#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0601
#include <SDKDDKVer.h>
#define NOMINMAX
#define NOMCX
#define NOSERVICE
#define NOHELP
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ML_Error.h"

namespace ml3d
{
	namespace CORE
	{
		template <class DERIVED_TYPE>
		class WindowBase
		{
		protected:
			HWND m_hwnd;

		public:
			WindowBase() : m_hwnd( nullptr ) {}
			virtual PCWSTR ClassName() const { return L"Main"; }
			virtual PCWSTR WindowText() const { return L"ML3D"; };
			virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
			HWND hwnd() const { return m_hwnd; }

			static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
			{
				DERIVED_TYPE *pThis = nullptr;

				if( uMsg == WM_NCCREATE )
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >(
						( reinterpret_cast< CREATESTRUCT* >( lParam ) )->lpCreateParams );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, ( LONG_PTR )pThis );

					pThis->m_hwnd = hwnd;

					if( !pThis->m_hwnd )
					{
						LogFile("ErrorLog.txt", GetError( "Object missing." , __FILE__ , __LINE__ ) );
					}
				}
				else
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
				}

				if( pThis )
				{
					return pThis->HandleMessage( uMsg, wParam, lParam );
				}
				else
				{
					return DefWindowProc( hwnd, uMsg, wParam, lParam );
				}
			}

			virtual void Create()
			{
				// Register the main window class.
				WNDCLASSEX wc = { 0 };
				wc.cbSize = sizeof( WNDCLASSEX );
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				wc.lpfnWndProc = WndProc;
				wc.lpszClassName = ClassName();
				//wc.lpszMenuName = MAKEINTRESOURCE( IDR_MAIN_MENU );
				wc.hInstance = GetModuleHandle( nullptr );
				wc.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_ACTIVEBORDER );
				wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
				//wc.hIcon = static_cast< HICON >(
				//	LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
				//wc.hIconSm = static_cast< HICON >(
				//	LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

				if( !RegisterClassEx( &wc ) )
				{
					LogFile("ErrorLog.txt", GetError( "Object missing." , __FILE__ , __LINE__ ) );
				}

				// Create the frame window.
				m_hwnd = CreateWindowEx(
					WS_EX_APPWINDOW,												// Optional window styles.
					ClassName(),													// Window class
					WindowText(),													// Window text
					WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,				// Window style
					CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		// Size and position
					nullptr,														// Parent window
					nullptr,														// Menu
					GetModuleHandle( nullptr ),										// Instance handle
					this );															// Additional application data

				if( !m_hwnd )
				{
					LogFile("ErrorLog.txt", GetError( "Object missing." , __FILE__ , __LINE__ ) );
				}

				ShowWindow( m_hwnd, SW_SHOWNORMAL | SW_MAXIMIZE );
			}
		};

		class WindowMain : public WindowBase<WindowMain>
		{
		public:
			WindowMain( ) noexcept
			{ }

			LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
			{
				switch( uMsg )
				{
					case WM_CLOSE:
					{
						DestroyWindow( m_hwnd );
						UnregisterClass(
							ClassName( ),
							GetModuleHandle( nullptr )
						);
					}
					return 0;
					case WM_DESTROY:
					{
						PostQuitMessage( 0 );
					}
					break;
					case WM_PAINT:
					{
						PAINTSTRUCT ps;
						HDC hdc = BeginPaint( m_hwnd, &ps );
						EndPaint( m_hwnd, &ps );
					}
					break;
					//case WM_INPUT:
					//{
					//	//m_input->Update( uMsg, wParam, lParam );
					//}
					//return 0;
					default:
						return DefWindowProc( m_hwnd, uMsg, wParam, lParam );
				}
				return TRUE;
			}
		};
	} // namespace graphics
} // namespace ml3d