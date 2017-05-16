#pragma once
#include "selene.h"
#include <unordered_map>
#include "GameObject.h"

class LuaBinding
{
private:
	LuaBinding();
	~LuaBinding();

public:
	static void Init();
	static void ReloadScripts();
	static void ExecuteScripts(GameObject* gameObject);

private:
	static std::unordered_map<std::string, sel::State*> _states;

};

