#pragma once

#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0601
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
#pragma comment(lib, "winmm.lib")

// DX
#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3DCompiler.lib")

// OpenGL
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */

#include <wrl/client.h>
#include <windowsx.h>
#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string.h>
#include <tchar.h>
#include <strsafe.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <CommCtrl.h>
#include <shobjidl.h>
#include <timeapi.h>
#include <filesystem>
#include <random>
#include <vector>
#include <array>

// Memory Leak
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Resource
#include "resource.h"

// FBX
#include <fbxsdk.h>

using namespace DirectX;

// User
#include "ErrorHandler.h"
#include "BitManipulation.h"
#include "TranslateWinMsgs.h"
#include "StepTimer.h"
#include "Structures.h"

// Temp Settings
#define ISWMMSGSHOW 1

#define GETARRAYSIZE( var ) sizeof( var ) / sizeof( var[0] )
#define BINOUT(var,type) bout.write( reinterpret_cast<char*>( &var ), sizeof( type ) )
#define BININ(var, type) bin.read( reinterpret_cast< char* >( &var ), sizeof( type ) )
#define TABINSERT(num) std::setw(num * 4) << ""


static constexpr float g_degreeInRadian = 0.0174532925f;
static constexpr float g_EPSILON = 0.00001f;
static constexpr UINT g_maxFPS = 60u;