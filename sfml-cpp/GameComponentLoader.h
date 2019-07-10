#pragma once
#include "GameComponent.h"
#include <map>
#include <functional>

namespace GameComponentLoader
{
	GameComponent* CreateNew(std::string className);
	std::map<std::string, std::function<GameComponent*()>> &get_map();

	class FunctionMapper {
	public:
		FunctionMapper(const char *name, std::function<GameComponent*()> func)
		{
			get_map().insert(std::make_pair(name, func));
		}
	};

	template<typename T, const char* NAME>
	class BaseComponent {
	protected:
		static FunctionMapper m;
		BaseComponent()
		{
			(void)m;
		}
	};

	template<typename T, const char* NAME>
	FunctionMapper BaseComponent<T, NAME>::m = FunctionMapper(NAME, T::CreateNew);
}

#define DECLARE_LOADABLE(ClassName) \
namespace GameComponentLoader \
{ \
	static const char _ ## ClassName ## Str[] = #ClassName; \
	static GameComponent* _ ## ClassName ## _Create() \
	{ \
		return nullptr; \
	} \
  \
	class _ ## ClassName ##  : public BaseComponent<_ ## ClassName ## , _ ## ClassName ## Str> \
	{ \
	public: \
		_ ## ClassName ## () : BaseComponent() {} \
 \
		static GameComponent* CreateNew() \
		{ \
			return new ClassName ## (); \
		} \
	}; \
} \


