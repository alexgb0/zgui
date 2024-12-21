#pragma once

#include "zgui.h"
#include "builder.h"

namespace zgui
{
	struct Context
	{
		
	};

	Context* init();
	void draw(Builder* layout);
	void update(Builder* layout);
	Builder* build_gui(Style* style);
}