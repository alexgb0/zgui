#pragma once

#include "zgui.h"

namespace zgui
{
	struct Window : BaseContainer
	{
		bool minimized;
		std::string title;

		void draw_topbar();

		void calc_children() override;
		void draw() override;
		std::pair<int, int> dimension() override;
	};

	struct VerticalContainer : BaseContainer
	{
		void calc_children() override;
		void draw() override;
		std::pair<int, int> dimension() override;
	};

	struct HorizontalContainer : BaseContainer
	{
		void calc_children() override;
		void draw() override;
		std::pair<int, int> dimension() override;
	};

	struct Label : BaseComponent
	{
		std::string text;
		int size;

		void draw() override;
		std::pair<int, int> dimension() override;
	};

	struct Button : BaseComponent
	{
		std::string text;

		void draw() override;
		std::pair<int, int> dimension() override;
	};

	struct Slider : BaseComponent
	{
		std::string text;
		float min, max;
		float* value;
		int bar_x;

		void draw() override;
		std::pair<int, int> dimension() override;
	};

	struct CheckBox : BaseComponent
	{
		bool* value;

		void draw() override;
		std::pair<int, int> dimension() override;
	};
}