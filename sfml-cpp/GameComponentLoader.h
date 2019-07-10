#pragma once
#include "GameComponent.h"
#include <map>
#include <functional>

namespace GameComponentLoader
{
	GameComponent* CreateNew(std::string className);
	std::map<std::string, std::function<GameComponent*()>> &get_map();

	class StaticFunctionMap {
	public:
		StaticFunctionMap(const char *name, std::function<GameComponent*()> func)
		{
			get_map().insert(std::make_pair(name, func));
		}
	};

	template<typename T, const char* NAME>
	class BaseFunctionMapper {
	protected:
		static StaticFunctionMap m;
		BaseFunctionMapper()
		{
			(void)m;
		}
	};

	template<typename T, const char* NAME>
	StaticFunctionMap BaseFunctionMapper<T, NAME>::m = StaticFunctionMap(NAME, T::CreateNew);
}

#define DECLARE_LOADABLE(ClassName) \
namespace GameComponentLoader \
{ \
	static const char ClassName ## Str[] = #ClassName; \
  \
	class ClassName ## FunctionMapper : public BaseFunctionMapper<ClassName ## FunctionMapper, ClassName ## Str> \
	{ \
	public: \
		ClassName ## FunctionMapper () : BaseFunctionMapper() {} \
 \
		static GameComponent* CreateNew() \
		{ \
			return new ClassName ## (); \
		} \
	}; \
} \


