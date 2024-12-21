#include "component.h"

#include <algorithm>

std::pair<int, int> zgui::BaseContainer::dimension()
{
	int max_h = 0, max_w = 0;
	for (auto element : childs)
	{
		auto [e_w, e_h] = element->dimension();
		if (max_w < e_w) max_w = e_w;
		max_h += e_h;
	}

	w = max_w + (style->margin_x * 2);
	h = max_h + (style->margin_y * (childs.size() + 1));

	return { w, h };
}

std::pair<int, int> zgui::VerticalContainer::dimension()
{
	int max_h = 0, max_w = 0;
	for (auto element : childs)
	{
		auto [e_w, e_h] = element->dimension();
		if (e_w > max_w) max_w = e_w;
		max_h += e_h;
	}

	w = max_w + (style->margin_x * 2);
	h = max_h + (style->margin_y * (childs.size() + 1));

	return { w, h };
}

std::pair<int, int> zgui::HorizontalContainer::dimension()
{
	int max_h = 0, max_w = 0;
	for (auto element : childs)
	{
		auto [e_w, e_h] = element->dimension();
		if (e_h > max_h) max_h = e_h;
		max_w += e_w;
	}

	w = max_w + (style->margin_x * (childs.size() + 1));
	h = max_h + (style->margin_y * 2);

	return { w, h };
}

std::pair<int, int> zgui::Label::dimension()
{
	auto [t_w, t_h] = MeasureTextEx(style->font, text.c_str(), size, 1);
	w = t_w;
	h = t_h - 3;/*(t_h - 3) + (style->margin_y * 2);*/

	return { w, h };
}

std::pair<int, int> zgui::Button::dimension()
{
	auto [t_w, t_h] = MeasureTextEx(style->font, text.c_str(), 10 /* default font size */, 1);
	w = t_w + 2; //standard button padding, needs to be added to style
	h = t_h + 2;

	return { w, h };
}

std::pair<int, int> zgui::Slider::dimension()
{
	auto [t_w, t_h] = MeasureTextEx(style->font, text.c_str(), 12, 1);
	w = style->slider_px;
	h = t_h;

	return { w, h };
}

std::pair<int, int> zgui::CheckBox::dimension()
{
	w = style->checkbox_px;
	h = style->checkbox_px;

	return { w, h };
}
