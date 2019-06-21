#include "Global.h"
#include "RenderEngine.h"

RenderEngine::RenderEngine( ) noexcept
	:
	mIsDirectX( true ),
	mIsFullScreen( true ),
	mIsVsyncEnabled( true ),
	mCamera( nullptr ),
	mModel( nullptr ),
	mShader( nullptr ),
	mLight( nullptr )
{}

void RenderEngine::Initialize( HWND targetWindow )
{
	mGraphics = std::shared_ptr<GraphicsD3D>( new GraphicsD3D( ) );
	mGraphics->Initialize( targetWindow );

	mCamera = std::shared_ptr<Camera>( new Camera( ) );
	mCamera->SetPosition( 0.0f, 0.0f, -5.0f );

	mModel = std::shared_ptr<Model>( new Model( ) );
	mModel->Initialize( mGraphics->GetDevice( ), mGraphics->GetContext( ), const_cast< char* >( "C:../cube.txt" ), const_cast<char*>("C:../stone01.tga" ));

	mShader = std::shared_ptr<Shader>( new Shader( ) );
	mShader->Initialize( mGraphics->GetDevice( ), targetWindow );

	mLight = std::shared_ptr<Light>( new Light( ) );
	mLight->SetAmbientColor( 0.15f, 0.15f, 0.15f, 1.0f );
	mLight->SetDiffuseColor( 0.98f, 0.83f, 0.83f, 1.0f );
	mLight->SetDirection( 0.5f, 0.0f, 0.5f );
	mLight->SetSpecularColor( 1.0f, 1.0f, 1.0f, 1.0f );
	mLight->SetSpecularPower( 32.0f );
}

void RenderEngine::Terminate()
{
	mModel->Shutdown( );
}

void RenderEngine::Frame( )
{
	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += XM_PI * 0.002f;
	if( rotation > 360.0f )
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	Render( rotation );
}

void RenderEngine::Render( float rotation )
{
	XMMATRIX
		worldMatrix,
		viewMatrix,
		projectionMatrix;

	// Clear the buffers to begin the scene.
	mGraphics->Clear( );

	// Generate the view matrix based on the camera's position.
	mCamera->Render( );

	// Get the world, view, and projection matrices from the camera and d3d objects.
	mGraphics->GetWorldMatrix( worldMatrix );
	mCamera->GetViewMatrix( viewMatrix );
	mGraphics->GetProjectionMatrix( projectionMatrix );

	worldMatrix = XMMatrixRotationY( rotation );
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	mModel->Render( mGraphics->GetContext( ) );

	// Render the model using the shader.
	mShader->Render( mGraphics->GetContext( ), mModel->GetIndexCount( ), worldMatrix, viewMatrix, projectionMatrix,
					 mModel->GetTexture( ), mLight->GetDirection(), mLight->GetAmbientColor( ), mLight->GetDiffuseColor(),
					 mCamera->GetPosition( ), mLight->GetSpecularColor( ), mLight->GetSpecularPower( ) );

	// Present the rendered scene to the screen.
	mGraphics->Present( );
}
