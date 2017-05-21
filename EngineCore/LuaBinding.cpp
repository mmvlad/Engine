#include "LuaBinding.h"
#include "FileUtils.h"
#include "Config.h"
#include "Logger.h"
#include "System.h"

std::unordered_map<std::string, sel::State*> LuaBinding::_states;


LuaBinding::LuaBinding()
{
}


LuaBinding::~LuaBinding()
{
}

void LuaBinding::Init()
{
	ReloadScripts();
}

void logger(std::string str)
{
	std::string res = "Lua: " + std::string(str);
	Log::Info(res);
}

//TODO(vlad): Load scripts when we load objects, bind scripts to objects
void LuaBinding::ReloadScripts()
{
	for(auto& state: _states)
	{
		delete state.second;
	}

	_states.clear();

	auto dir		= FileUtils::CombinePath(System::GetProjectDataDir(), SCRIPTS_DIR);
	auto searchDir	= FileUtils::CombinePath(dir, "*");
	auto files		= FileUtils::GetFilesInDir(searchDir);

	for (auto& file : files)
	{
		auto scriptFilePath = FileUtils::CombinePath(dir, file);
		//scriptFilePath = FileUtils::CombinePath(dirPath, scriptFilePath);

		sel::State * state = new sel::State(true);
		state->Load(scriptFilePath);

		_states[file] = state;

		//auto str = FileUtils::StringFromFile(scriptFilePath);
		//Log::Info("Sript found: [" + scriptFilePath + "], content: [" + str + "]");
	}
	////_state("x = 43");
	//Log::Info("Foo val: " + std::to_string((int)_state["foo"]));
	//_state["inc_foo"]();
	//Log::Info("Foo val: " + std::to_string((int)_state["foo"]));
}

void LuaBinding::ExecuteScripts(GameObject* gameObject)
{
	std::vector<std::string> names = gameObject->GetScriptList();

	for(auto & scriptName: names)
	{
		if (_states.find(scriptName) == _states.end())
		{
			Log::Error("Script [" + scriptName + "] of object [" + gameObject->GetName() + "] not found");
			continue;
		}

		sel::State& state = *_states[scriptName];

		auto pos = gameObject->Position();

		state["log"] = &logger;
		state["update"]();

		double posY = state["posY"];
		double posX = state["posX"];
		double posZ = state["posZ"];

		pos.x = posX;
		pos.y = posY;
		pos.z = posZ;

		gameObject->SetPosition(pos);
	}
}
