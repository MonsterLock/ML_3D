#pragma once

// Windows SDK
#define _WIN32_WINNT_WIN10	0x0A00 // Windows 10
#include <SDKDDKVer.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

// Windows API
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// DX
#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

// OpenGL
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */
//#include <glad/glad.h>

#include <wrl/client.h>
#include <windowsx.h>
#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string.h>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include <iomanip>
#include <CommCtrl.h>
#include <shobjidl.h>
#include <timeapi.h>

// Resource
#include "resource.h"

// FBX
#include <fbxsdk.h>

// Link library dependencies
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

// User
#include "ReportMessage.h"
#include "WindowMessenger.h"
#include "TranslateWinMsgs.h"
#include "StepTimer.h"

// Temp Settings
#define ISWMMSGSHOW 0

// Safely release a COM object.
template <typename T>
inline void SafeRelease( T &ptr )
{
	if( ptr )
	{
		ptr->Release();
		ptr = nullptr;
	}
}