#include "SceneWindow.h"

LRESULT SceneWindow::HandleSubWndMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CREATE:
			{
				return 0;
			}
			break;
		default:
			{
				return DefMDIChildProc( Wnd(), uMsg, wParam, lParam );
			}
	}
	return 0;
}
