#pragma once

#ifdef ENGINE_CORE_EXPORTS  
#define ENGINECORE_API __declspec(dllexport)   
#else  
#define ENGINECORE_API __declspec(dllimport)   
#endif  