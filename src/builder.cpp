#include "builder.h"

#include <algorithm>
#include <exception>
#include <cassert>
#include <cmath>

zgui::Builder* zgui::Builder::add_window(const std::string_view name, const std::string_view title)
{
	auto window = new Window;
	window->name = name;
	window->title = title;
	window->style = style;
	window->color = style->white;
	window->x = 10;
	window->y = 10;
	windows.emplace_back(window);

	current_window = window;

	return this;
}

zgui::Builder* zgui::Builder::add_hcontainer(const std::string_view name, const std::string_view parent)
{
	auto hcontainer = new HorizontalContainer;
	hcontainer->name = name;
	hcontainer->style = style;

	if (current_container == nullptr)
	{
		current_window->childs.emplace_back(hcontainer);
		current_container = hcontainer;


		return this;
	}

	if (!parent.empty())
	{
		const auto p = std::find_if(current_window->childs.begin(), current_window->childs.end(), [&](BaseComponent* container) {
			return container->name == parent;
		});

		if (p == current_window->childs.end())
			throw std::exception("error");
		
		dynamic_cast<BaseContainer*>(*p)->childs.emplace_back(hcontainer);
		current_container = hcontainer;
	}


	return this;
}

zgui::Builder* zgui::Builder::add_vcontainer(const std::string_view name, const std::string_view parent)
{
	auto vcontainer = new VerticalContainer;
	vcontainer->name = name;
	vcontainer->style = style;

	if (current_container == nullptr)
	{
		current_window->childs.emplace_back(vcontainer);
		current_container = vcontainer;

		return this;
	}

	if (!parent.empty())
	{
		const auto p = std::find_if(current_window->childs.begin(), current_window->childs.end(), [&](BaseComponent* container) {
			return container->name == parent;
			});

		if (p == current_window->childs.end())
			throw std::exception("error");

		auto bcontainer = dynamic_cast<BaseContainer*>(*p);
		assert(bcontainer != nullptr);
		bcontainer->childs.emplace_back(vcontainer);
		current_container = vcontainer;
	}

	return this;
}

zgui::Builder* zgui::Builder::add_label(const std::string_view name, const std::string_view text, Color color, int size)
{
	auto label = new Label;
	label->name = name;
	label->text = text;
	label->size = size;
	label->color = color;
	label->style = style;

	assert(current_container != nullptr);
	current_container->childs.emplace_back(label);

	return this;
}

zgui::Builder* zgui::Builder::add_button(const std::string_view name, const std::string_view text, ElementCallback callback)
{
	auto button = new Button;
	button->name = name;
	button->text = text;
	button->color = style->white;
	button->style = style;
	button->callback = callback;
	button->clickable = true;

	assert(current_container != nullptr);
	current_container->childs.emplace_back(button);

	return this;
}

// TODO: move this somewhere else
void slider_onclick(zgui::BaseComponent* component, zgui::Builder* builder)
{
	zgui::Slider* slider = dynamic_cast<zgui::Slider*>(component);
	auto [x, y] = GetMousePosition();
	slider->bar_x = x - slider->x;

	*slider->value = zgui::interpolate_values(slider->x, slider->x + slider->w, slider->min, slider->max, x);
}

zgui::Builder* zgui::Builder::add_slider(const std::string_view name, float min, float max, float* value)
{
	auto slider = new Slider;
	slider->name = name;
	slider->color = style->white;
	slider->style = style;
	slider->min = min;
	slider->max = max;
	slider->bar_x = *value;
	slider->value = value;
	slider->clickable = true;
	slider->callback = slider_onclick;

	assert(current_container != nullptr);
	current_container->childs.emplace_back(slider);

	return this;
}

zgui::Builder* zgui::Builder::add_checkbox(const std::string_view name, bool* value)
{
	auto checkbox = new CheckBox;
	checkbox->name = name;
	checkbox->color = style->magenta;
	checkbox->style = style;
	checkbox->value = value;
	checkbox->clickable = true;
	checkbox->callback = [](BaseComponent* component, Builder* builder) {
		CheckBox* checkbox = dynamic_cast<CheckBox*>(component);
		*checkbox->value = !*checkbox->value;
	};

	assert(current_container != nullptr);
	current_container->childs.emplace_back(checkbox);

	return this;
}

zgui::Builder* zgui::Builder::clear_container_cursor()
{
	current_container = nullptr;
	return this;
}

zgui::Builder* zgui::Builder::compile()
{
	for (auto* window : windows)
	{
		window->calc_children();
		window->dimension();
	}

	return this;
}
