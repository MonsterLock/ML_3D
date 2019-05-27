#include "MainWindow.h"
#include "FILEIO.h"
#include <fbxsdk.h>
#include <string>
#include <shobjidl.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
	{L"Word Document (*.doc)",       L"*.doc"},
	{L"Text Document (*.txt)",       L"*.txt"},
	{L"All Documents (*.*)",         L"*.*"}
};

// Indices of file types
#define INDEX_WORDDOC 1
#define INDEX_TEXTDOC 2

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//	_CrtSetBreakAlloc();

	InitCommonControls();

	MainWindow win;

	if( !win.Create() )
	{
		MessageBox( nullptr, L"Creating GUI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
		return 0;
	}

	MSG msg = {};

	while( msg.message != WM_QUIT )
	{
		if(	PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) &&
			!TranslateMDISysAccel( win.ClientWnd(), &msg ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
	return static_cast< int >( msg.wParam );
}

//CreateDirectory( L"TestFileIO", nullptr );
//MessageBox( nullptr, std::to_wstring( GetLastError() ).c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION );
//RemoveDirectory( L"TestFileIO" );
//MessageBox( nullptr, std::to_wstring( GetLastError() ).c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION );