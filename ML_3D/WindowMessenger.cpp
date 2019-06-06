#include "Global.h"
#include "WindowMessenger.h"

LRESULT WindowMessenger::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( Wnd(), uMsg, wParam, lParam );
}
