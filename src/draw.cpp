#include "component.h"

#include <string>

void zgui::Window::draw_topbar()
{
	DrawRectangleLines(x, y - 14, w, 15, style->white);
	DrawTextEx(style->font, title.c_str(), {(float)x + style->margin_x, (float)y - 12}, 12, 0, style->white);
}

void zgui::Window::draw()
{
	draw_topbar();
	DrawRectangleLines(x, y, w, h, style->white);

	for (auto element : childs)
	{
		element->draw();
	}
}

void zgui::VerticalContainer::draw()
{
	DrawRectangleLines(x, y, w, h, style->white);

	for (auto element : childs)
	{
		element->draw();
	}
}

void zgui::HorizontalContainer::draw()
{
	DrawRectangleLines(x, y, w, h, style->white);

	for (auto element : childs)
	{
		element->draw();
	}
}

void zgui::Label::draw()
{
	//DrawRectangleLines(x, y, w, h, GOLD);
	DrawTextEx(style->font, text.c_str(), {(float)x, (float)y}, size, 1, color);
}

void zgui::Button::draw()
{
	DrawRectangleLines(x, y, w, h, color);
	DrawTextEx(style->font, text.c_str(), { (float)x + 2, (float)y + 2 }, 9, 1, color);
}

void zgui::Slider::draw()
{
	int val = interpolate_values(min, max, x, x + w, *value) - x;
	DrawRectangle(x, y, val, h, style->magenta);
	if (bar_x > min)
		DrawTextEx(style->font, std::to_string((int)*value).c_str(), { (float)x + 10, (float)y + 1 }, 12, 1, style->white);
	DrawRectangleLines(x, y, w, h, color);
}

void zgui::CheckBox::draw()
{
	DrawRectangleLines(x, y, w, h, style->white);
	
	if (*this->value)
		DrawRectangle(x + 2, y + 2, w - 4, h - 4, color);
}