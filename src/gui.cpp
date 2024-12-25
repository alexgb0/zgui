#include "gui.h"

#include <cassert>

zgui::Context* zgui::init()
{
    return new Context;
}

void zgui::draw(Builder* layout)
{
    for (auto window : layout->windows)
        window->draw();
}

void _update(std::deque<zgui::BaseComponent*> container, zgui::Builder* layout)
{
    for (auto element : container)
    {
        zgui::BaseContainer* container = dynamic_cast<zgui::BaseContainer*>(element);

        if (container != nullptr)
            _update(container->childs, layout);

        if (!element->clickable) continue;

        if (CheckCollisionPointRec(GetMousePosition(), { (float)element->x, (float)element->y, (float)element->w, (float)element->h }))
        {
            element->color = layout->style->cyan;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                element->callback(element, layout);
        }
        else
            element->color = layout->style->white;
    }
}

void update_window(zgui::Window* win, zgui::Builder* layout)
{
    if (CheckCollisionPointRec(GetMousePosition(), { (float)win->x, (float)win->y-15, (float)win->w, 15.f }))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            for (auto e : win->childs)
                e->visible = false;

            auto [x, y] = GetMouseDelta();
            win->x += x;
            win->y += y;
            win->color = layout->style->gold;
        }
        else
        {
            layout->compile();
            for (auto e : win->childs)
                e->visible = true;
            win->color = layout->style->magenta;
        }
    }
    else
        win->color = layout->style->white;
}


void zgui::update(Builder* layout)
{
    for (auto window : layout->windows)
    {
        update_window(window, layout);
        _update(window->childs, layout);
    }
}

zgui::Builder* zgui::build_gui(Style* style)
{
    auto builder = new Builder;
    builder->style = style;
    return builder;
}
