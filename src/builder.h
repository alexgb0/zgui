#pragma once

#include "zgui.h"
#include "component.h"

#include <string_view>

namespace zgui
{
	struct Builder
	{
		Builder* add_window(const std::string_view name, const std::string_view title);
		Builder* add_hcontainer(const std::string_view name, const std::string_view parent = "");
		Builder* add_vcontainer(const std::string_view name, const std::string_view parent = "");

		Builder* add_label(const std::string_view name, const std::string_view text, Color color, int size = 12);
		Builder* add_button(const std::string_view name, const std::string_view text, ElementCallback callback);
		Builder* add_slider(const std::string_view name, float min, float max, float* value);
		Builder* add_checkbox(const std::string_view name, bool* value);

		Builder* clear_container_cursor();
		Builder* compile();

		bool compiled = false;

		std::deque<Window*> windows;
		Window* current_window;
		BaseContainer* current_container = nullptr;
		Style* style;
	};


}