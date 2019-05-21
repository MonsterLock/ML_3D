#include "Engine.h"
#include "FILEIO.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <fbxsdk.h>
#include <string>
#include <shobjidl.h>

const COMDLG_FILTERSPEC c_rgSaveTypes[ ] =
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

	//CreateDirectory( L"TestFileIO", nullptr );
	//MessageBox( nullptr, std::to_wstring( GetLastError() ).c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION );
	//RemoveDirectory( L"TestFileIO" );
	//MessageBox( nullptr, std::to_wstring( GetLastError() ).c_str(), L"ERROR", MB_OK | MB_ICONEXCLAMATION );
	Engine eng;
	return eng.Run();
}
