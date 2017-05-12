#pragma once

#include "Config.h"



#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
		TypeName(const TypeName&);         \
		void operator=(const TypeName&);

#define INTRFC struct __declspec(novtable)

#define APP_MANAGER(TypeName) \
		TypeName(); \
		DISALLOW_COPY_AND_ASSIGN(TypeName) \
		friend class App;