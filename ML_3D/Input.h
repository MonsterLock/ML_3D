#pragma once

class Input
{
	bool mKeys[256];

public:
	Input() noexcept;
	Input( const Input& ) noexcept;
	~Input();
	void Initialize();

	void KeyDown( UINT );
	void KeyUp( UINT );
	bool IsKeyDown( UINT );
};

