#pragma once
#include "Global.h"

namespace ml3d
{
	struct Vertex_Type
	{
		XMFLOAT3 pos;
		XMFLOAT2 tex;
		XMFLOAT3 nrm;
		XMFLOAT3 tan;
		XMFLOAT3 btn;
	};

	struct Vert_Data
	{
		enum
		{
			Pos,
			Col,
			Tx1,
			Tx2,
			Nrm,
			Tng,
			Btn,
			Skn,
			Num
		};
	};


}