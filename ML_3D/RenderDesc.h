#pragma once
#include "Global.h"

namespace RenderDesc
{
	enum RasterStates
	{
		raster_default,
		raster_wiremode,
		raster_num,
	};

	enum BlendStates
	{
		blend_default,
		blend_simple,
		blend_texture,
		blend_particle,
		blend_num,
	};

	enum buffers
	{
		buffer_Object,
		buffer_Frame,
		buffer_App,
		buffer_num,
	};

	enum CS_Buffers
	{
		CS_num,
	};

	enum DS_Buffers
	{
		DS_num,
	};

	enum GS_Buffers
	{
		GS_num,
	};

	enum HS_Buffers
	{
		HS_num,
	};

	enum PS_Buffers
	{
		PS_num,
	};

	enum VS_Buffers
	{
		VS_num,
	};
}