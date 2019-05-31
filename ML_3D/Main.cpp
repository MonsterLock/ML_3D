#include "MainWindow.h"
#include "D3DRenderer.h"
#include "FILEIO.h"
#include <fbxsdk.h>
#include <string>
#include <shobjidl.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define IDR_ACCEL1 151

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//	_CrtSetBreakAlloc();

	InitCommonControls();
	std::unique_ptr<D3DRenderer> render = std::make_unique<D3DRenderer>();

	MainWindow win;
	if( !win.Create() )
	{
		MessageBox( nullptr, L"Creating GUI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
		return 0;
	}
	RECT rc;
	GetClientRect( win.RenderWnd(), &rc );
	render->Inititalize( win.RenderWnd(), rc.right - rc.left, rc.bottom - rc.top );

	bool isMsgObtained;
	MSG msg = {};
	msg.message = WM_NULL;
	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	HACCEL hAccel = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDR_ACCEL1 ) );

	while( msg.message != WM_QUIT )
	{
		isMsgObtained = PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE )
			&& !TranslateMDISysAccel( win.ClientWnd(), &msg )
			&& !TranslateAccelerator( win.FrameWnd(), hAccel, &msg );

		if( isMsgObtained )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			render->Render();

		}
		//else
		//{
		//	// Update the scene.
		//	renderer->Update();

		//	// Render frames during idle time (when no messages are waiting).
		//	renderer->Render();

		//	// Present the frame to the screen.
		//	deviceResources->Present();
		//}
	}
	return static_cast< int >( msg.wParam );
}

// #define _L(x)  __L(x)
// #define __L(x)  L##x
 //#define RES_STATUS
//
// const COMDLG_FILTERSPEC c_rgSaveTypes[] =
// {
// 	{L"Word Document (*.doc)",       L"*.doc"},
// 	{L"Text Document (*.txt)",       L"*.txt"},
// 	{L"All Documents (*.*)",         L"*.*"}
// };
//
// // Indices of file types
// #define INDEX_WORDDOC 1
// #define INDEX_TEXTDOC 2
//
//CreateDirectory( L"TestFileIO", nullptr );
//MessageBox( nullptr, std::to_wstring( GetLastError() ).c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION );
//RemoveDirectory( L"TestFileIO" );
//MessageBox( nullptr, std::to_wstring( GetLastError() ).c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION );