#include "FILEIO.h"
#include <strsafe.h>

FILEIO::FILEIO()
{}

FILEIO::~FILEIO()
{}

DWORD FILEIO::CreateNewDir( LPCWSTR lpDir )
{
	if( CreateDirectory( lpDir, nullptr ) )
	{
		return 0;
	}
	return GetLastError();
}

DWORD FILEIO::LoadDir( LPCWSTR lpDir )
{
	return 0;
}

DWORD FILEIO::SaveDir( LPCWSTR lpDir )
{
	return 0;
}

DWORD FILEIO::RemoveDir( LPCWSTR lpDir )
{
	if( RemoveDirectory( lpDir ) )
	{
		return 0;
	}
	return GetLastError();
}

DWORD FILEIO::SetCurrentDir( LPCWSTR lpDir )
{
	if( SetCurrentDirectory( lpDir ) )
	{
		return 0;
	}
	return GetLastError();
}

DWORD FILEIO::GetCurrentDir( LPWSTR lpDir )
{
	if( GetCurrentDirectory( MAX_PATH, lpDir ) )
	{
		return 0;
	}
	return GetLastError();
}

DWORD FILEIO::ListDirContents( LPCWSTR lpDir )
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER fileSize;
	WCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.
	StringCchLength( lpDir, MAX_PATH, &length_of_arg );

	if( length_of_arg > ( MAX_PATH - 3 ) )
	{
		// Dir path is too long
	}

	// Prepare string for use with FindFile functions. First, copy the
	// string to a buffer, then append '/*' to the directory name.
	StringCchCopy( szDir, MAX_PATH, lpDir );
	StringCchCat( szDir, MAX_PATH, L"\\*" );

	// Find the first file in the directory.
	hFind = FindFirstFile( szDir, &ffd );

	if( INVALID_HANDLE_VALUE == hFind )
	{
		// First file not found.
		return dwError;
	}

	// List all the files in the directory with some info about them.
	do
	{
		if( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{

		}
		else
		{
			fileSize.LowPart = ffd.nFileSizeLow;
			fileSize.HighPart = ffd.nFileSizeHigh;

		}
	}
	while( FindNextFile( hFind, &ffd ) != 0 );

	dwError = GetLastError();
	if( dwError != ERROR_NO_MORE_FILES )
	{
		// We never reached all the files.
	}

	FindClose( hFind );
	return dwError;
}

DWORD FILEIO::MoveDir( LPWSTR lpDir, LPWSTR lpDirTar, LPPROGRESS_ROUTINE progressProc, LPVOID copyData, DWORD dwFlags )
{
	if( MoveFileWithProgress( lpDir, lpDirTar, progressProc, copyData, dwFlags ) )
	{
		return 0;
	}
	return GetLastError();
}

DWORD FILEIO::WatchDir( LPWSTR lpDir )
{
	DWORD dwWaitStatus;
	HANDLE dwChangeHandles[2];
	TCHAR lpDrive[4];
	TCHAR lpFile[_MAX_FNAME];
	TCHAR lpExt[_MAX_EXT];

	_tsplitpath_s( lpDir, lpDrive, 4, NULL, 0, lpFile, _MAX_FNAME, lpExt, _MAX_EXT );

	lpDrive[2] = ( TCHAR )'\\';
	lpDrive[3] = ( TCHAR )'\0';

	// Watch the directory for file creation and deletion.

	dwChangeHandles[0] = FindFirstChangeNotification(
		lpDir,                         // directory to watch
		FALSE,                         // do not watch subtree
		FILE_NOTIFY_CHANGE_FILE_NAME ); // watch file name changes

	if( dwChangeHandles[0] == INVALID_HANDLE_VALUE )
	{
		printf( "\n ERROR: FindFirstChangeNotification function failed.\n" );
		ExitProcess( GetLastError() );
	}

	// Watch the subtree for directory creation and deletion.

	dwChangeHandles[1] = FindFirstChangeNotification(
		lpDrive,                       // directory to watch
		TRUE,                          // watch the subtree
		FILE_NOTIFY_CHANGE_DIR_NAME );  // watch dir name changes

	if( dwChangeHandles[1] == INVALID_HANDLE_VALUE )
	{
		printf( "\n ERROR: FindFirstChangeNotification function failed.\n" );
		ExitProcess( GetLastError() );
	}


	// Make a final validation check on our handles.

	if( ( dwChangeHandles[0] == NULL ) || ( dwChangeHandles[1] == NULL ) )
	{
		printf( "\n ERROR: Unexpected NULL from FindFirstChangeNotification.\n" );
		ExitProcess( GetLastError() );
	}

	// Change notification is set. Now wait on both notification
	// handles and refresh accordingly.

	while( TRUE )
	{
		// Wait for notification.

		printf( "\nWaiting for notification...\n" );

		dwWaitStatus = WaitForMultipleObjects( 2, dwChangeHandles,
											   FALSE, INFINITE );

		switch( dwWaitStatus )
		{
			case WAIT_OBJECT_0:

				// A file was created, renamed, or deleted in the directory.
				// Refresh this directory and restart the notification.

				RefreshDir( lpDir );
				if( FindNextChangeNotification( dwChangeHandles[0] ) == FALSE )
				{
					printf( "\n ERROR: FindNextChangeNotification function failed.\n" );
					ExitProcess( GetLastError() );
				}
				break;

			case WAIT_OBJECT_0 + 1:

				// A directory was created, renamed, or deleted.
				// Refresh the tree and restart the notification.

				RefreshTree( lpDrive );
				if( FindNextChangeNotification( dwChangeHandles[1] ) == FALSE )
				{
					printf( "\n ERROR: FindNextChangeNotification function failed.\n" );
					ExitProcess( GetLastError() );
				}
				break;

			case WAIT_TIMEOUT:

				// A timeout occurred, this would happen if some value other
				// than INFINITE is used in the Wait call and no changes occur.
				// In a single-threaded environment you might not want an
				// INFINITE wait.

				printf( "\nNo changes in the timeout period.\n" );
				break;

			default:
				printf( "\n ERROR: Unhandled dwWaitStatus.\n" );
				ExitProcess( GetLastError() );
				break;
		}
	}
}

DWORD FILEIO::RefreshDir( LPWSTR lpDir )
{
	return 0;
}

DWORD FILEIO::RefreshTree( LPWSTR lpDrive )
{
	return 0;
}
