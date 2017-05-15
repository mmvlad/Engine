#include "App.h"
#include <Windows.h>
#include "Logger.h"
#include <glm.hpp>
#include "GLWrap.h"
#include "GlUtils.h"
#include "System.h"
#include "GlMaterial.h"


#pragma comment (lib, "opengl32.lib")

HDC				* App::_hdc				= nullptr;
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
	InitManagers();

	//auto c = Color::FromHexRGB("c41770");

	//Mesh * m = new Mesh();
	//m->AddVertex(glm::vec3(0.0f, 0.5f, 0.0f));
	//m->AddVertex(glm::vec3(0.5f, -0.5f, 0.0f));
	//m->AddVertex(glm::vec3(-0.5f, -0.5f, 0.0f));

	//m->AddColor(Color::FromBytes(255).ToVector());
	//m->AddColor(Color::FromBytes(0, 255).ToVector());
	//m->AddColor(Color::FromBytes(0, 0, 255).ToVector());

	//testRenderer = new GlMeshRenderer(*m, *(App::_materialManager->_defaultMaterial));
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


App::~App()
{
}





#include <experimental/filesystem>


int App::Start()
{
	InitInternal();

	System::OpenGlInfo();

	System::LoadConfig();

	_sceneManager->LoadScene("MainScene");

	/*std::string path = std::experimental::filesystem::current_path().string();
	Log::Info("Current path: " + path);*/

	//Log::Info(string_format("Device context passed to App [%p]", (void*)_hdc));

	//Resize(500, 500);

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

		_renderer->Render();
	}

	return 0;
}


