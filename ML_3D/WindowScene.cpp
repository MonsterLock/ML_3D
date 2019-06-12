#include "Global.h"
#include "WindowScene.h"

LRESULT WindowScene::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{


	switch( uMsg )
	{
		case WM_CREATE:
			{
				return 0;
			}
		default:
			{
				return DefMDIChildProc( Wnd(), uMsg, wParam, lParam );
			}
	}
	return 0;
}
