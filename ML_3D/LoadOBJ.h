#pragma once
#include <iostream>
#include <fstream>

class LoadOBJ
{
	typedef struct
	{
		float x, y, z;
	}VertexType;

	typedef struct
	{
		int
			v1, v2, v3,
			t1, t2, t3,
			n1, n2, n3;
	}FaceType;

public:
	LoadOBJ( );
	void GetModelFilename( char* );
	void ReadFileCounts( char*, int&, int&, int&, int& );
	void LoadDataStructures( char*, int, int, int, int );
};

