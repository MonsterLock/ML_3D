#include "Global.h"
#include "WindowMain.h"

WindowMain::WindowMain( ) noexcept
	:
	m_input( nullptr )
{ }

LRESULT WindowMain::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CREATE:
		{
			m_input = std::shared_ptr<Input>( new Input( ) );
			m_input->Initialize( nullptr );
		}
		break;
		case WM_CLOSE:
		{
			DestroyWindow( mHwnd );
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
			HDC hdc = BeginPaint( mHwnd, &ps );
			EndPaint( mHwnd, &ps );
		}
		break;
		case WM_INPUT:
		{
			m_input->Update( uMsg, wParam, lParam );
		}
		return 0;
		default:
			return DefWindowProc( mHwnd, uMsg, wParam, lParam );
	}
	return TRUE;
}
