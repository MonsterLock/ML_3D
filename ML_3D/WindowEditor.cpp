#include "Global.h"
#include "WindowEditor.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


constexpr static float
tabRatio = 0.03f,
verticalRatio = 0.8f,
leftHorizontalRatio = 0.85f,
rightHorizontalRatio = 0.33f;

LRESULT WindowEditor::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CLOSE:
			{
				/* TODO:
				- Save window configurations
				- Check for any unsaved work
				- Clean resources */
				if( MainMenu() )
					DestroyMenu( MainMenu() );
				DestroyWindow( FrameWnd() );
				UnregisterClass(
					FrameName(),
					GetModuleHandle( nullptr )
				);
			}
			return 0;
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
			}
			break;
		case WM_CREATE:
			{
				// Create windows.
				mAnimation.RegSubWnd( 0, nullptr );
				mAnimation.CreateSubWnd( ClientWnd(), 0 );

				mConsole.RegSubWnd( 0, nullptr );
				mConsole.CreateSubWnd( ClientWnd(), 0 );

				mGame.RegSubWnd( 0, nullptr );
				mGame.CreateSubWnd( ClientWnd(), 0 );

				mHierarchy.RegSubWnd( 0, nullptr );
				mHierarchy.CreateSubWnd( ClientWnd(), 0 );

				mLighting.RegSubWnd( 0, nullptr );
				mLighting.CreateSubWnd( ClientWnd(), 0 );

				mProfiler.RegSubWnd( 0, nullptr );
				mProfiler.CreateSubWnd( ClientWnd(), 0 );

				mProject.RegSubWnd( 0, nullptr );
				mProject.CreateSubWnd( ClientWnd(), 0 );

				mProperties.RegSubWnd( 0, nullptr );
				mProperties.CreateSubWnd( ClientWnd(), 0 );

				mScene.RegSubWnd( CS_OWNDC, nullptr );
				mScene.CreateSubWnd( ClientWnd(), 0 );

				// Create toolbar.
				mToolbar.Create( FrameWnd(), nullptr, 0, reinterpret_cast< HMENU >( RID_MAIN_TB ) );

				TBADDBITMAP tbab; // Toolbar images
				tbab.hInst = HINST_COMMCTRL;
				tbab.nID = IDB_STD_SMALL_COLOR;
				SendMessage( mToolbar.Wnd(), TB_ADDBITMAP, 0, reinterpret_cast< LPARAM >( &tbab ) );

				TBBUTTON tbb[3]; // Toolbar buttons
				ZeroMemory( tbb, sizeof( tbb ) );
				Toolbar::SetToolButton( tbb, 0, ID_FILE_NEW, STD_FILENEW, BTNS_BUTTON, TBSTATE_ENABLED );
				Toolbar::SetToolButton( tbb, 1, ID_FILE_OPEN, STD_FILEOPEN, BTNS_BUTTON, TBSTATE_ENABLED );
				Toolbar::SetToolButton( tbb, 2, ID_FILE_SAVEAS, STD_FILESAVE, BTNS_BUTTON, TBSTATE_ENABLED );
				SendMessage( mToolbar.Wnd(), TB_ADDBUTTONS, sizeof( tbb ) / sizeof( TBBUTTON ), reinterpret_cast< LPARAM >( &tbb ) );

				// Create statusbar.
				mStatusbar.Create( FrameWnd(), nullptr, 0, reinterpret_cast< HMENU >( RID_MAIN_STATUS ) );
				mStatusbar.SetText( 0, L"Welcome." );

				// Create tabs controls.
				TCITEM tab;
				tab.mask = TCIF_TEXT;

				mTabs[ViewTab].Create( FrameWnd(), L"mTabs", 0, nullptr );
				mTabs[ViewTab].AddTab( Scene, tab, L"Scene" );
				mTabs[ViewTab].AddTab( Game, tab, L"Game" );
				mTabs[ViewTab].AddTab( Anim, tab, L"Animation" );

				mTabs[InfoTab].Create( FrameWnd(), L"TABINFO", TCS_BOTTOM, nullptr );
				mTabs[InfoTab].AddTab( Proj, tab, L"Project" );
				mTabs[InfoTab].AddTab( Console, tab, L"Console" );
				mTabs[InfoTab].AddTab( Prof, tab, L"Profiler" );

				mTabs[PropTab].Create( FrameWnd(), L"TABPROPERTIES", TCS_BOTTOM, nullptr );
				mTabs[PropTab].AddTab( Prop, tab, L"Properties" );
				mTabs[PropTab].AddTab( Light, tab, L"Lighting" );

				// Create font.
				HDC hdc;
				long lfHeight;
				hdc = GetDC( nullptr );
				lfHeight = -MulDiv( 12, GetDeviceCaps( hdc, LOGPIXELSY ), 72 );
				ReleaseDC( nullptr, hdc );

				mHFONT = CreateFont( lfHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, const_cast< LPCWSTR >( L"Consolas" ) );

				EnumChildWindows( FrameWnd(), reinterpret_cast< WNDENUMPROC >( SetFont ), reinterpret_cast< LPARAM >( mHFONT ) );

				// Set and show current windows.
				mCurrentTab[ViewTab] = Scene;
				ShowWindow( WindowIndex( mCurrentTab[ViewTab] ), SW_SHOW );

				mCurrentTab[InfoTab] = Proj;
				ShowWindow( WindowIndex( mCurrentTab[InfoTab] ), SW_SHOW );

				mCurrentTab[PropTab] = Prop;
				ShowWindow( WindowIndex( mCurrentTab[PropTab] ), SW_SHOW );

				ShowWindow( WindowIndex( Hier ), SW_SHOW );
			}
			break;
		case WM_SIZE:
			{
				CallSize();
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( FrameWnd(), &ps );
				EndPaint( FrameWnd(), &ps );
			}
			break;
		case WM_NOTIFY:
			{
				if( reinterpret_cast< LPNMHDR >( lParam )->code == TCN_SELCHANGE )
				{
					HWND selectedTabControl = reinterpret_cast< LPNMHDR >( lParam )->hwndFrom;

					int
						i = 0,
						tabIndex = TabCtrl_GetCurSel( selectedTabControl );

					for( ; i < 3; ++i )
					{
						if( mTabs[i].Wnd() == selectedTabControl )
						{
							tabIndex = i * NumTabControls + tabIndex;
							break;
						}
					}

					HWND
						currentWnd = WindowIndex( mCurrentTab[i] ),
						selectedWnd = WindowIndex( tabIndex );

					if( currentWnd != selectedWnd )
					{
						ShowWindow( currentWnd, SW_HIDE );
						mCurrentTab[i] = tabIndex;
						CallSize();
						ShowWindow( selectedWnd, SW_SHOW );
					}
				}
			}
			break;
		case WM_COMMAND:
			{
				if( !GlobalCommands( uMsg, wParam, lParam ) )
				{
					if( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
						return DefFrameProc( FrameWnd(), ClientWnd(), WM_COMMAND, wParam, lParam );
					else
					{
						HWND hChild = reinterpret_cast< HWND >( SendMessage( ClientWnd(), WM_MDIGETACTIVE, 0, 0 ) );
						if( hChild )
							SendMessage( hChild, WM_COMMAND, wParam, lParam );
					}
				}
			}
			break;
		default:
			return DefFrameProc( FrameWnd(), ClientWnd(), uMsg, wParam, lParam );
	}
	return 0;
}

BOOL WindowEditor::GlobalCommands( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( LOWORD( wParam ) )
	{
		case ID_FILE_NEW: {}break;
		case ID_FILE_OPEN: {}break;
		case ID_FILE_STARTUP: {}break;
		case ID_FILE_SAVE: {}break;
		case ID_FILE_SAVEAS: {}break;
		case ID_FILE_SAVEALL: {}break;
		case ID_FILE_BUILDPROPERTIES: {} break;
		case ID_FILE_BUILDANDRUN: {} break;
		case ID_FILE_EXIT: { SendMessage( FrameWnd(), WM_CLOSE, 0, 0 ); } break;
		case ID_GOTO_FILE: {} break;
		case ID_GOTO_OBJECT: {} break;
		case ID_GOTO_LASTEDIT: {} break;
		case ID_EDIT_FIND: {} break;
		case ID_EDIT_FINDREPLACE: {} break;
		case ID_NEXT_FILE: {} break;
		case ID_NEXT_OBJECT: {} break;
		case ID_PREVIOUS_FILE: {} break;
		case ID_PREVIOUS_OBJECT: {} break;
		case ID_EDIT_UNDO: {} break;
		case ID_EDIT_REDO: {} break;
		case ID_Menu: {} break;
		case ID_EDIT_COPY: {} break;
		case ID_EDIT_PASTE: {} break;
		case ID_EDIT_DELETE: {} break;
		case ID_EDIT_SELECTALL: {} break;
		case ID_EDIT_SELECTIONGROUP: {} break;
		case ID_VIEW_TOOLBAR:
			{
				if( IsWindowVisible( mToolbar.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_TOOLBAR, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( mToolbar.Wnd(), SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_TOOLBAR, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( mToolbar.Wnd(), SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_VIEWPANEL:
			{
				TogglePanel( ViewTab );
			} break;
		case ID_VIEW_CATEGORYPANEL:
			{
				if( IsWindowVisible( mHierarchy.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_CATEGORYPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( WindowIndex( Hier ), SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_CATEGORYPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( WindowIndex( Hier ), SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_PROPERTIESPANEL:
			{
				TogglePanel( PropTab );
			} break;
		case ID_VIEW_SYSTEMPANEL:
			{
				TogglePanel( InfoTab );
			} break;
		case ID_VIEW_WIREFRAME: {} break;
		case ID_VIEW_ORTHOGRAPHIC: {} break;
		case ID_VIEW_PERSPECTIVE: {} break;
		case ID_PROJECT_ADDNEW: {} break;
		case ID_PROJECT_ADDEXISTING: {} break;
		case ID_SHOWALL_WINDOWS: {} break;
		case ID_SHOWALL_VIEWS: {} break;
		case ID_SHOWALL_FILES: {} break;
		case ID_SHOWALL_OBJECTS: {} break;
		case ID_PROJECT_PROPERTIES: {} break;
		case ID_TOOLS_CREATEELEMENT: {} break;
		case ID_TOOLS_CREATESUB: {} break;
		case ID_3DELEMENT_CUBE: {} break;
		case ID_3DELEMENT_SPHERE: {} break;
		case ID_3DELEMENT_CAPSULE: {} break;
		case ID_3DELEMENT_CYLINDER: {} break;
		case ID_3DELEMENT_PLANE: {} break;
		case ID_3DELEMENT_QUAD: {} break;
		case ID_3DELEMENT_TERRAIN: {} break;
		case ID_2DELEMENT_SPRITE: {} break;
		case ID_2DELEMENT_SPRITEMASK: {} break;
		case ID_2DELEMENT_TILEMAP: {} break;
		case ID_EFFECTS_PARTICLESYSTEM: {} break;
		case ID_EFFECTS_TRAIL: {} break;
		case ID_EFFECTS_LINE: {} break;
		case ID_LIGHT_DIRECTIONAL: {} break;
		case ID_LIGHT_POINT: {} break;
		case ID_LIGHT_SPOT: {} break;
		case ID_LIGHT_AREA: {} break;
		case ID_LIGHT_REFLECTIONPROBE: {} break;
		case ID_TOOLS_AUDIO: {} break;
		case ID_TOOLS_VIDEO: {} break;
		case ID_TOOLS_UI: {} break;
		case ID_TOOLS_CAMERA: {} break;
		case ID_TOOLS_SCRIPT: {} break;
		case ID_TOOLS_SHADER: {} break;
		case ID_TOOLS_SCENE: {} break;
		case ID_TOOLS_MAKE: {} break;
		case ID_TOOLS_CLEARSET: {} break;
		case ID_TOOLS_SETASFIRSTELEMENT: {} break;
		case ID_TOOLS_SETASSECONDELEMENT: {} break;
		case ID_TOOLS_MOVETOELEMENT: {} break;
		case ID_TOOLS_MOVETOORIGIN: {} break;
		case ID_TOOLS_SETGAMEVIEW: {} break;
		case ID_TOOLS_TOGGLEACTIVE: {} break;
		case ID_HELP_ABOUT:
			{
				DialogBox( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDD_HELP_ABOUT_PAGE ), FrameWnd(), reinterpret_cast< DLGPROC >( AboutDlg ) );
			} break;
		case ID_HELP_VIEWHELP: {} break;
		case ID_HELP_REPORTABUG: {} break;

		default: return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK WindowEditor::SetFont( HWND hwnd, LPARAM font )
{
	SendMessage( hwnd, WM_SETFONT, font, true );
	return true;
}

HWND WindowEditor::WindowIndex( int index )
{
	switch( index )
	{
		case Scene: { return mScene.Wnd(); } break;
		case Game: { return mGame.Wnd(); }break;
		case Anim: { return mAnimation.Wnd(); }break;

		case Proj: { return mProject.Wnd(); } break;
		case Console: { return mConsole.Wnd(); }break;
		case Prof: { return mProfiler.Wnd(); }break;

		case Prop: { return mProperties.Wnd(); } break;
		case Light: { return mLighting.Wnd(); }break;

		case Hier: { return mHierarchy.Wnd(); } break;

		default: return nullptr;
	}
}

// TODO: Clean this
void WindowEditor::CallSize()
{
	HWND
		hClient,
		hTool,
		hStatus;

	RECT
		rcClient,
		rcTool,
		rcStatus;

	int
		iClientHeight,
		iToolHeight,
		iStatusHeight;

	// Size toolbar window.
	hTool = mToolbar.Wnd();
	SendMessage( hTool, TB_AUTOSIZE, 0, 0 );

	if( IsWindowVisible( hTool ) )
	{
		GetWindowRect( hTool, &rcTool );
		iToolHeight = rcTool.bottom - rcTool.top;
	}
	else iToolHeight = 0;

	// Size status bar window.
	hStatus = mStatusbar.Wnd();
	SendMessage( hStatus, WM_SIZE, 0, 0 );

	GetWindowRect( hStatus, &rcStatus );
	iStatusHeight = rcStatus.bottom - rcStatus.top;

	// Calculate remaining height and size edit
	GetClientRect( FrameWnd(), &rcClient );
	iClientHeight = rcClient.bottom - iToolHeight - iStatusHeight;

	hClient = GetDlgItem( FrameWnd(), RID_MAIN_CLIENT );
	SetWindowPos( hClient, nullptr, 0, iToolHeight, rcClient.right, iClientHeight, SWP_NOZORDER );

	// Calculate sub-windows
	GetClientRect( hClient, &rcClient );

	int
		tabHeight = static_cast< int >( rcClient.bottom * tabRatio ),
		verticalDivide = verticalDivide = static_cast< int >( rcClient.right * verticalRatio ),
		rightWidth = rcClient.right - verticalDivide,
		leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio ),
		rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio );

	unsigned int clientState = 0x0;

	if( IsWindowVisible( mTabs[ViewTab].Wnd() ) ) { clientState = 0xF; }
	if( IsWindowVisible( mTabs[InfoTab].Wnd() ) ) { clientState = ( clientState | 0xF0 ); }
	if( IsWindowVisible( mHierarchy.Wnd() ) ) { clientState = ( clientState | 0xF00 ); }
	if( IsWindowVisible( mTabs[PropTab].Wnd() ) ) { clientState = ( clientState | 0xF000 ); }

	if( !clientState ) return;

	switch( clientState & 0xFF )
	{
		case 0x0F: { leftHorizontalDivide = rcClient.bottom; } break;
		case 0xF0: { leftHorizontalDivide = 0; }break;
		case 0xFF: { leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio ); }break;
		default: { clientState = ( clientState | 0xF0000 ); } break;
	}
	switch( ( clientState & 0xFF00 ) >> 8 )
	{
		case 0x0F: { rightHorizontalDivide = rcClient.bottom; }break;
		case 0xF0: { rightHorizontalDivide = 0; }break;
		case 0xFF: { rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio ); }break;
		default: { clientState = ( clientState | 0xF00000 ); } break;
	}
	switch( ( clientState & 0xFF0000 ) >> 16 )
	{
		case 0x00: { verticalDivide = static_cast< int >( rcClient.right * verticalRatio ); }break;
		case 0x0F: { verticalDivide = 0; }break;
		case 0xF0: { verticalDivide = rcClient.right; }break;
	}
	rightWidth = rcClient.right - verticalDivide;

	// Top-Left Panel
	SetWindowPos( mTabs[ViewTab].Wnd(), HWND_TOP, 0, iToolHeight, verticalDivide, tabHeight, SWP_NOOWNERZORDER );
	SetWindowPos( WindowIndex( mCurrentTab[ViewTab] ), nullptr, 0, tabHeight, verticalDivide, leftHorizontalDivide - tabHeight, SWP_NOZORDER );

	// Bot-Left Panel
	SetWindowPos( mTabs[InfoTab].Wnd(), HWND_TOP, 0, rcClient.bottom - tabHeight + iToolHeight, verticalDivide, tabHeight, SWP_NOOWNERZORDER );
	SetWindowPos( WindowIndex( mCurrentTab[InfoTab] ), nullptr, 0, leftHorizontalDivide, verticalDivide, rcClient.bottom - leftHorizontalDivide - tabHeight, SWP_NOZORDER );

	// Top-Right Panel
	SetWindowPos( WindowIndex( Hier ), nullptr, verticalDivide, 0, rightWidth, rightHorizontalDivide, SWP_NOZORDER );

	// Bot-Right Panel
	SetWindowPos( mTabs[PropTab].Wnd(), HWND_TOP, verticalDivide, rcClient.bottom - tabHeight + iToolHeight, rightWidth, tabHeight, SWP_NOOWNERZORDER );
	SetWindowPos( WindowIndex( mCurrentTab[PropTab] ), nullptr, verticalDivide, rightHorizontalDivide, rightWidth, rcClient.bottom - rightHorizontalDivide - tabHeight, SWP_NOZORDER );
}

void WindowEditor::TogglePanel( int index )
{
	if( IsWindowVisible( mTabs[index].Wnd() ) )
	{
		CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_UNCHECKED );
		ShowWindow( mTabs[index].Wnd(), SW_HIDE );
		ShowWindow( WindowIndex( mCurrentTab[index] ), SW_HIDE );
	}
	else
	{
		CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_CHECKED );
		ShowWindow( mTabs[index].Wnd(), SW_SHOW );
		ShowWindow( WindowIndex( mCurrentTab[index] ), SW_SHOW );
	}
	CallSize();
}

BOOL CALLBACK WindowEditor::AboutDlg( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					EndDialog( hwnd, IDOK );
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

WindowEditor::WindowEditor() noexcept : mHFONT(nullptr){}
