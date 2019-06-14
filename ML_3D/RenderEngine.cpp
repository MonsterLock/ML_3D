#include "Global.h"
#include "RenderEngine.h"

RenderEngine::RenderEngine() noexcept
	:
	mIsDirectX( true ),
	mIsFullScreen( true ),
	mIsVsyncEnabled( true )

{}

RenderEngine::RenderEngine( const RenderEngine & ) noexcept
{}

RenderEngine::~RenderEngine()
{}

void RenderEngine::Initialize( HWND targetWindow )
{
	mGraphics = mIsDirectX ?
		std::shared_ptr<GraphicsAPI>( new GraphicsD3D() ) : std::shared_ptr<GraphicsAPI>( new GraphicsOpenGL() );
	mGraphics->Initialize( targetWindow );
}

void RenderEngine::Terminate()
{}

void RenderEngine::Frame()
{}

void RenderEngine::Render()
{ mGraphics->Render(); }
