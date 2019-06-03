#include "MainWindow.h"
#include "Renderer.h"
#include "FILEIO.h"
#include <fbxsdk.h>
#include <string>
#include <shobjidl.h>
//#include <glad/glad.h>
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define IDR_ACCEL1 151
#if 1
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
	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	RECT rc;
	GetClientRect( win.RenderWnd(), &rc );
	renderer->Inititalize( win.RenderWnd(), rc.right - rc.left, rc.bottom - rc.top );

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
			renderer->Render();

	}
	renderer->Terminate();

	return static_cast< int >( msg.wParam );
}
#endif
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
#if 0
void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );

// Settings.
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex shader in shader language GLSL.
const char* vertexShaderSource = "#version 330 core\n"
// The position variable has attribute position 0.
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

// Fragment shader in shader language GLSL.
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow )
{

	// Initialize GLFW.
	glfwInit();

	// Configure GLFW.
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	// Create a window object to hold all the windowing data.
	GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "R.A. BICKELL", NULL, NULL );
	if( !window )
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	// Tell GLFW to make the context of our window the main context on the current thread.
	glfwMakeContextCurrent( window );

	// Tell GLFW we want to call the framebuffer_size_callback
	// function every time the window is resized.
	glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

	// GLAD manages function pointers for OpenGL so we initialize it before calling OpenGL functions.
	if( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD!\n";
		return -1;
	}

	// Rendering a single triangle.
	//////////// Vertex Input
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//////////// Vertex Shader
	unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );

	// Attach the shader source code to the shader object and compile the shader.
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );

	// Check to make sure the compilation was successful.
	int success;
	char infoLog[512];
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//////////// Fragment Shader.
	// A fragment in OpenGl is all the data required for OpenGl to render a single pixel.
	unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	// Attach the shader source code to the shader object and compile the shader.
	glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
	glCompileShader( fragmentShader );

	// Check to make sure the compilation was successful.
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
		std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//////////// Shader Program.
	// A shader program object is the final linked version of multiple shaders combined.
	unsigned int shaderProgram = glCreateProgram();

	// Attach the previously compile shaders to the program.
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	// Activate the newly created program object that was the result of the linking.
	glUseProgram( shaderProgram );

	// Check to make sure the compilation was successful.
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
	if( !success )
	{
		glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete any shader objects we no longer need.
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	// We sent the input vertex data to the GPU and instructed the GPU how it should process
	// the vertex data within a vertex and fragment shader.

	// Manage the memory via so called vertex buffer objects (VBO) that can
	// store a large number of vertices in the GPU's memory.
	unsigned int VBO;

	// Generate a unique ID corresponding to that vertex buffer object, so we can generate one with a buffer ID.
	glGenBuffers( 1, &VBO );

	// Allows us to bind several buffers at once as long as they have a different buffer type.
	glBindBuffer( GL_ARRAY_BUFFER, VBO );

	// Make a call to the glBufferData function that copies the previously defined vertex data into
	// the buffer's memory. It specifically targeted to copy user-defined data into the currently
	// bound buffer.
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	//////////// Vertex Array Object.
	// Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs.
	// If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.
	unsigned int VAO;

	// Generate a unique ID corresponding to that vertex array object.
	glGenVertexArrays( 1, &VAO );

	// Bind VAO first, then bind and set vertex buffer(s), and then configure
	// vertex attribute(s).
	glBindVertexArray( VAO );

	//////////// Linking Vertex Attributes.
	// We tell openGl how it should interpret the vertex data (per vertex attribute).
	// Position attribute.
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* )0 );
	glEnableVertexAttribArray( 0 );
	// Color attribute.
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
	glEnableVertexAttribArray( 1 );

	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
	// attribute's bound vertex buffer object so afterwards we can safely unbind.
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
	// but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways
	// so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray( 0 );

	while( !glfwWindowShouldClose( window ) )
	{
		// Input.
		processInput( window );

		// Rendering.
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// Draw our first triangle.
		glUseProgram( shaderProgram );

		// Update shader uniform.
		float timeValue = static_cast< float >( glfwGetTime() );
		float greenValue = sin( timeValue ) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation( shaderProgram, "ourColor" );
		glUniform4f( vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f );

		// Seeing as we only have a single VAO there's no need to bind it every time,
		// but we'll do so to keep things a bit more organized.
		glBindVertexArray( VAO );

		// Draw the object.
		glDrawArrays( GL_TRIANGLES, 0, 3 );

		// Swaps the buffers.
		glfwSwapBuffers( window );

		// Poll IO events.
		glfwPollEvents();
	}

	// Optional: deallocate all resources once they've outlived their purpose:
	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );

	// GLFW: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// Process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly.
void processInput( GLFWwindow* window )
{

	if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}
}
// Register a callback function that gets called if window is resized.
void framebuffer_size_callback( GLFWwindow* window, int width, int height )
{

	// Tell OpenGL the size of the rendering window.
	// (-1 to 1, -1 to 1, width, height)
	glViewport( 0, 0, width, height );
}
#endif