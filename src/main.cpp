#include "zgui.h"
#include "gui.h"
#include "builder.h"

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 480, "zgui demo");

	auto style = zgui::Style{};
	style.font = LoadFont(style.font_path.c_str());
	SetTextureFilter(style.font.texture, TEXTURE_FILTER_BILINEAR);

	bool dummy = false;
	auto layout = zgui::build_gui(&style)
		->add_window("window0", "test window")
		->add_hcontainer("Margin x")
		->add_label("", "Margin x:", style.white)
		->add_slider("slider01", 1, 100, &style.margin_x)
		->add_label("", "Margin y:", style.white)
		->add_slider("slider01", 1, 100, &style.margin_y)
		->clear_container_cursor()
		->add_hcontainer("controls")
		->add_label("", "Slider width:", style.white)
		->add_slider("slider01", 1, 100, &style.slider_px)
		->add_label("", "Checkbox size:", style.white)
		->add_slider("slider01", 1, 100, &style.checkbox_px)
		->clear_container_cursor()
		->add_hcontainer("checkbox test")
		->add_label("", "Dummy checkbox: ", style.white)
		->add_checkbox("", &dummy)
		->clear_container_cursor()
		->add_hcontainer("compile")
		->add_label("", "Compile layout", style.white)
		->add_button("button01", "compile", [](zgui::BaseComponent* comp, zgui::Builder* builder) {
			builder->compile();
		})
		->compile();


	while (!WindowShouldClose())
	{
		zgui::update(layout);

		BeginDrawing();
		ClearBackground(BLACK);

		zgui::draw(layout);
		EndDrawing();
	}

	delete layout;
	CloseWindow();

	return 0;
}
