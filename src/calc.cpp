#include "component.h"

void zgui::Window::calc_children()
{
	int next_x = x + style->margin_x;
	int next_y = y + style->margin_y;

	for (auto* component : childs)
	{
		component->x = next_x;
		component->y = next_y;

		BaseContainer* container = dynamic_cast<BaseContainer*>(component);
		if (container != nullptr)
		{
			auto [w, h] = container->dimension();
			container->calc_children();

			next_y += h + style->margin_y;
			continue;
		}

		auto [w, h] = component->dimension();
		next_y += h + style->margin_y;
	}
}

void zgui::VerticalContainer::calc_children()
{
	int next_x = x + style->margin_x;
	int next_y = y + style->margin_y;

	for (auto* component : childs)
	{
		component->x = next_x;
		component->y = next_y;

		BaseContainer* container = dynamic_cast<BaseContainer*>(component);
		if (container != nullptr)
		{
			auto [w, h] = container->dimension();
			container->calc_children();

			next_y += h + style->margin_y;
			continue;
		}

		auto [w, h] = component->dimension();
		next_y += h + style->margin_y;
	}
}

void zgui::HorizontalContainer::calc_children()
{
	int next_x = x + style->margin_x;
	int next_y = y + style->margin_y;

	for (auto* component : childs)
	{
		component->x = next_x;
		component->y = next_y;

		BaseContainer* container = dynamic_cast<BaseContainer*>(component);
		if (container != nullptr)
		{
			auto [w, h] = container->dimension();
			container->calc_children();

			next_x += w + style->margin_x;
			continue;
		}

		auto [w, h] = component->dimension();
		next_x += w + style->margin_x;
	}
}
