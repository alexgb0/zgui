#pragma once

#include <deque>
#include <stack>
#include <iostream>
#include <utility>
#include <functional>
#include <raylib.h>

namespace zgui
{

	struct Style
	{
		~Style() { UnloadFont(font); }

		float margin_x = 10;
		float margin_y = 5;
		
		float slider_px = 50;
		float checkbox_px = 12;

		std::string font_path = "C:\\Users\\user\\source\\repos\\zgui\\res\\ProggyClean.ttf";
		Font font;

		const Color gray = { 170, 170, 170, 255 };
		const Color cyan = { 0, 170, 170, 255 };
		const Color magenta = { 170, 0, 170, 255 };
		const Color gold = { 170, 170, 0, 255 };
		const Color black = { 0, 0, 0, 255 };
		const Color white = { 255, 255, 255, 255 };
	};

	struct BaseComponent;
	struct Builder;
	using ElementCallback = std::function<void(BaseComponent*, Builder*)>;

	struct BaseComponent
	{
		int x, y, w, h;
		std::string name;
		Color color;
		Style* style;
		
		bool clickable = false;
		ElementCallback callback;


		virtual void draw() {};
		virtual std::pair<int, int> dimension() { return { w, h }; }
	};

	struct BaseContainer : BaseComponent
	{
		~BaseContainer() { for (auto* ptr : childs) delete ptr; }


		virtual std::pair<int, int> dimension();
		virtual void calc_children() {}


		std::deque<BaseComponent*> childs;
	};

	inline double interpolate_values(double start_1, double end_1, double start_2, const double end_2, double value) {
		return std::lerp(start_2, end_2, (value - start_1) / (end_1 - start_1));
	}
}