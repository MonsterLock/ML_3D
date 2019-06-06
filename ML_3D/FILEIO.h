#pragma once

class FILEIO
{
public:
	FILEIO();
	~FILEIO();
	// Directory Functions
	DWORD CreateNewDir( LPCWSTR lpDir );
	DWORD LoadDir( LPCWSTR lpDir );
	DWORD SaveDir( LPCWSTR lpDir );
	DWORD RemoveDir( LPCWSTR lpDir );
	DWORD SetCurrentDir( LPCWSTR lpDir );
	DWORD GetCurrentDir( LPWSTR lpDir );
	DWORD ListDirContents( LPCWSTR lpDir );
	DWORD MoveDir( LPWSTR lpDir, LPWSTR lpDirTar, LPPROGRESS_ROUTINE progressProc, LPVOID copyData, DWORD dwFlags );
	DWORD WatchDir( LPWSTR lpDir );
	DWORD RefreshDir( LPWSTR lpDir );
	DWORD RefreshTree( LPWSTR lpDrive );

	// File Functions
	DWORD CreateNewFile();
	DWORD OpenFile();
	DWORD SaveFile();
	DWORD SaveAsFile();
	DWORD SaveAllFiles();
	DWORD ReadFromFile();
	DWORD WriteToFile();
};