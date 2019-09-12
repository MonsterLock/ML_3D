#pragma once
#include "Editor.h"
#include "Game.h"

class App
{
	Game* mGame;
	Editor* mEditor;

public:
	App( ) noexcept;
	void Initialize( UINT );
	void Update( );
	void Shutdown( );
};