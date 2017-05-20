#include "App.h"
#include <Windows.h>
#include "Logger.h"
#include <glm.hpp>
#include "GLWrap.h"
#include "System.h"
#include "LuaBinding.h"
#include "Camera.h"
#include "Scene.h"
//
//void Msg(const char* msg)
//{
//	MessageBoxA(NULL, msg, "Info", NULL);
//}


#pragma comment (lib, "opengl32.lib")

HWND			  App::_hwnd;
HDC				  App::_hdc				= nullptr;
SceneManager	* App::_sceneManager	= nullptr;
GlRender		* App::_renderer		= nullptr;
BaseMeshManager * App::_meshManager		= nullptr;





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

void App::InitInternal()
{
	_hdc = GetDC(_hwnd);

	InitManagers();

	LuaBinding::Init();
}

void App::InitManagers()
{
	_sceneManager	= new SceneManager();
	_renderer		= new GlRender();
	_meshManager	= new BaseMeshManager();

	//Msg("Managers created");

	//std::stringstream ss;
	//ss << "HDC address: " << _hdc;

	//Msg(ss.str().c_str());

	_renderer->Init(_hdc, _sceneManager);

	

	//Msg("Managers inited");

	_sceneManager->Init(_meshManager);
	_meshManager->Init(_renderer);

	

	_sceneManager->LoadSceneList();
}

void App::Render()
{
	//TODO(vlad): remove debug testing
	_sceneManager->LoadScene("MainScene");

	//execute scripts
	Scene * scene = _sceneManager->ActiveScene();
	Camera camera = scene->DefaultCamera();

	// Draw all objects from scene manager
	for (auto& gameObject : scene->GetObjects())
	{
		LuaBinding::ExecuteScripts(gameObject);
	}

	_renderer->Render();

}


App::~App()
{
}







int App::Start()
{
	InitInternal();

	//Msg("Internal init ok");

	//_renderer->Resize(500, 500);

	System::OpenGlInfo();

	//Msg("Opengl info retreived");

	System::LoadConfig();

	//Msg("Config loaded");

	_sceneManager->LoadScene("MainScene");

	/*
	Log::Info("Current path: " + path);*/

	//Log::Info(string_format("Device context passed to App [%p]", (void*)_hdc));

	

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

		//break;
	}

	return 0;
}


