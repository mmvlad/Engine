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
bool			  App::_reloadrRequired = false;




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


void App::ReloadScene()
{
	_sceneManager->LoadScene("MainScene");
	Log::Info("Scene reloaded");
}

App::App()
{

}

void App::Init(HWND hwnd)
{
	_hwnd = hwnd;

	InitInternal();
}



void App::InitInternal()
{
	_hdc = GetDC(_hwnd);

	InitManagers();

	// Loads lua scripts
	LuaBinding::Init();

	System::OpenGlInfo();

	System::LoadConfig();

	//TODO(vlad): move thid away from here
	ReloadScene();
}

void App::InitManagers()
{
	_sceneManager	= new SceneManager();
	_renderer		= new GlRender();
	_meshManager	= new BaseMeshManager();

	_renderer->Init(_hdc, _sceneManager);
	_sceneManager->Init(_meshManager);
	_meshManager->Init(_renderer);

	_sceneManager->LoadSceneList();
}

void App::Render()
{
	_renderer->Render();
}

void App::ExecuteLogic()
{
	// Execute scripts
	Scene * scene = _sceneManager->ActiveScene();
	Camera camera = scene->DefaultCamera();

	// Draw all objects from scene manager
	for (auto& gameObject : scene->GetObjects())
	{
		LuaBinding::ExecuteScripts(gameObject);
	}
}


App::~App()
{
	ReleaseDC(_hwnd, _hdc);
}


int App::Start()
{
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = false;

	game_state current_state;
	game_state previous_state;

	Log::Info("Game loop started");

	while (!quit_game) {

		if (_reloadrRequired)
		{
			_reloadrRequired = false;

			ReloadScene();
		}

		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		quit_game = handle_events();

		// update game logic as lag permits
		while (lag >= timestep) {
			lag -= timestep;

			previous_state = current_state;
			update(&current_state); // update at a fixed rate each time

			ExecuteLogic();
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


