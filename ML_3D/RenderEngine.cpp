#include "Global.h"
#include "RenderEngine.h"

RenderEngine::RenderEngine( ) noexcept
	:
	mIsDirectX( true ),
	mIsFullScreen( true ),
	mIsVsyncEnabled( true ),
	mCamera( nullptr ),
	mText( nullptr )
{ }

void RenderEngine::Initialize( HWND targetWindow )
{
	mGraphics = std::shared_ptr<GraphicsD3D>( new GraphicsD3D( ) );
	mGraphics->Initialize( targetWindow );

	mCamera = std::shared_ptr<Camera>( new Camera( ) );
	mCamera->SetPosition( 0.0f, 0.0f, -1.0f );
	mCamera->Render( );
	XMMATRIX baseViewMatrix;
	mCamera->GetViewMatrix( baseViewMatrix );

	// Create the text object.
	mText = std::shared_ptr<Text>( new Text( ) );

	// Initialize the text object.
	RECT rc;
	GetClientRect( targetWindow, &rc );
	mText->Initialize( mGraphics->GetDevice( ), mGraphics->GetContext( ), targetWindow, rc.right - rc.left, rc.bottom - rc.top, baseViewMatrix );
}

void RenderEngine::Terminate( )
{
	mText->Shutdown( );
}

void RenderEngine::Frame( )
{
	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	//rotation += XM_PI * 0.002f;
	//if( rotation > 360.0f )
	//{
	//	rotation -= 360.0f;
	//}

	// Render the graphics scene.
	Render( rotation );
}

void RenderEngine::Render( float rotation )
{
	XMMATRIX
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		orthoMatrix;

	// Clear the buffers to begin the scene.
	mGraphics->Clear( );

	// Generate the view matrix based on the camera's position.
	mCamera->Render( );

	// Get the world, view, and projection matrices from the camera and d3d objects.
	mGraphics->GetWorldMatrix( worldMatrix );
	mCamera->GetViewMatrix( viewMatrix );
	mGraphics->GetProjectionMatrix( projectionMatrix );
	mGraphics->GetOrthoMatrix( orthoMatrix );

	// Turn off the Z buffer to begin all 2D rendering.
	mGraphics->TurnZBufferOff( );

	// Turn on the alpha blending before rendering the text.
	mGraphics->TurnOnAlphaBlending( );

	// Render the text strings.
	mText->Render( mGraphics->GetContext( ), worldMatrix, orthoMatrix );

	// Turn off alpha blending after rendering the text.
	mGraphics->TurnOffAlphaBlending( );

	// Turn the Z buffer back on now that all 2D rendering has completed.
	mGraphics->TurnZBufferOn( );

	// Present the rendered scene to the screen.
	mGraphics->Present( );
}
