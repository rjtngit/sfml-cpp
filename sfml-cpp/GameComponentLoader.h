#pragma once
#include "GameComponent.h"
#include <map>
#include <functional>
#include <string>

// Based on these Stack Overflow posts:
// https://stackoverflow.com/questions/34858341/c-compile-time-list-of-subclasses-of-a-class
// https://stackoverflow.com/questions/9209052/static-field-initialization-in-template-class-in-c/9209352#9209352


class GameComponent;

namespace GameComponentLoader
{
	GameComponent* CreateNew(std::string className);
	std::map<std::string, std::function<GameComponent*()>> &get_map();

	class StaticFunctionMap 
	{
	public:
		StaticFunctionMap(std::function<GameComponent*()> func, const char *name)
		{
			get_map().insert(std::make_pair(name, func));
		}
	};

	template<typename T, const char* NAME>
	class BaseFunctionMapper 
	{
	protected:
		static StaticFunctionMap m;
		BaseFunctionMapper()
		{
			// Tell the compiler not to optimize m away
			(void)m;
		}
	};

	// Must be defined here because it is a templated variable 
	// https://stackoverflow.com/questions/1553854/template-static-variable
	template<typename T, const char* NAME>
	StaticFunctionMap BaseFunctionMapper<T, NAME>::m = StaticFunctionMap(T::CreateNew, NAME);
}


#define DECLARE_LOADABLE(ClassType) \
static constexpr char _ClassName[] = # ClassType; \
class _FunctionMapper : public GameComponentLoader::BaseFunctionMapper<_FunctionMapper, _ClassName> \
{ \
public: \
	_FunctionMapper() : BaseFunctionMapper() {} \
	static ClassType ## * CreateNew() \
	{ \
		return new ClassType ## (); \
	} \
}; \
