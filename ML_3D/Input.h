#pragma once

enum UserInputs
{
	isPrimaryDown,
	isPrimaryUp,
	isPrimaryDblEnabled,
	isPrimaryDblUsed,

	isMiddleDown,
	isMiddleUp,
	isMiddleDblEnabled,
	isMiddleDblUsed,

	isSecondaryDown,
	isSecondaryUp,
	isSecondaryDblEnabled,
	isSecondaryDblUsed,

	isPrimaryOptionalDown,
	isPrimaryOptionalUp,
	isPrimaryOptionalEnabled,
	isPrimaryOptionalused,

	isSecondaryOptionalDown,
	isSecondaryOptionalUp,
	isSecondaryOptionalEnabled,
	isSecondaryOptionalUsed
};

class Input
{
public:
	Input();
	~Input();
};

