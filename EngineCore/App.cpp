#include "App.h"
#include <Windows.h>
#include "Logger.h"
#include <glm.hpp>
#include "GLWrap.h"
#include "GlUtils.h"
#include "System.h"

#pragma comment (lib, "opengl32.lib")

HDC* App::_hdc = NULL;

void
OpenGLRectangle(glm::vec2 MinP, glm::vec2 MaxP, glm::vec4 Color)
{
	glBegin(GL_TRIANGLES);

	glColor4f(Color.r, Color.g, Color.b, Color.a);

	// NOTE(casey): Lower triangle
	//glTexCoord2f(0.0f, 0.0f);
	glVertex2f(MinP.x, MinP.y);

	//glTexCoord2f(1.0f, 0.0f);
	glVertex2f(MaxP.x, MinP.y);

	//glTexCoord2f(1.0f, 1.0f);
	glVertex2f(MaxP.x, MaxP.y);

	// NOTE(casey): Upper triangle
	//glTexCoord2f(0.0f, 0.0f);
	glVertex2f(MinP.x, MinP.y);

	//glTexCoord2f(1.0f, 1.0f);
	glVertex2f(MaxP.x, MaxP.y);

	//glTexCoord2f(0.0f, 1.0f);
	glVertex2f(MinP.x, MaxP.y);

	glEnd();
}

/*
* The MIT License (MIT)
*
* Copyright (c) 2016 Mario Badr
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <chrono>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

struct game_state {
	// this contains the state of your game, such as positions and velocities
};

bool handle_events() {
	// poll for events

	POINT p;
	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y
		//cout << "X: " << p.x << ", Y: " << p.y << endl;
	}


	MSG			msg;
	HWND		hwnd;
	WPARAM		wparam;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		hwnd = msg.hwnd;
		wparam = msg.wParam;

		// go from sceen coords to local window coords
		ScreenToClient(hwnd, &p);

		switch (msg.message)
		{
		case WM_KEYDOWN:
			
			break;

		case WM_KEYUP:
			
			break;

		case WM_QUIT:
			return true;
			break;

			// mouse coords are stored in object p
		case WM_LBUTTONDOWN:
			
			break;
		case WM_LBUTTONUP:
			
			break;

		case WM_RBUTTONDOWN:
			
			break;
		case WM_RBUTTONUP:
			
			break;

		case WM_MBUTTONDOWN:
			
			break;
		case WM_MBUTTONUP:
			
			break;

			//////////////////////////////////////////////////
		default:
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return false; // true if the user wants to quit the game
}

void update(game_state *) {
	// update game logic here
}


game_state interpolate(game_state const & current, game_state const & previous, float alpha) {
	game_state interpolated_state;

	// interpolate between previous and current by alpha here

	return interpolated_state;
}

App::App()
{

}

void App::Render()
{
	Color b = Color::FromHexRGB("20fb82");
	GLWrap::SetClearColor(b);

	GLWrap::ClearBuffer(ClearBufferType::COLOR_BUFFER);

	//OpenGLRectangle(glm::vec2(-0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1, 1, 1, 1));

	OpenGLRectangle(glm::vec2(0, 0), glm::vec2(199.0f, 199.0f), glm::vec4(1, 1, 1, 1));

	GLWrap::Flush();

	SwapBuffers(*_hdc);
}


App::~App()
{
}








int App::Start()
{
	System::OpenGlInfo();

	//Log::Info(string_format("Device context passed to App [%p]", (void*)_hdc));

	Resize(500, 500);

	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = false;

	game_state current_state;
	game_state previous_state;

	Log::Info("Game loop started");

	while (!quit_game) {
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		quit_game = handle_events();

		// update game logic as lag permits
		while (lag >= timestep) {
			lag -= timestep;

			previous_state = current_state;
			update(&current_state); // update at a fixed rate each time
		}

		// calculate how close or far we are from the next timestep
		auto alpha = (float)lag.count() / timestep.count();
		auto interpolated_state = interpolate(current_state, previous_state, alpha);

		//render(interpolated_state);

		Render();
	}

	return 0;
}


