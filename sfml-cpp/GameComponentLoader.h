#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>

class GameComponent;

// Based on these Stack Overflow posts:
// https://stackoverflow.com/questions/34858341/c-compile-time-list-of-subclasses-of-a-class
// https://stackoverflow.com/questions/9209052/static-field-initialization-in-template-class-in-c/9209352#9209352

namespace GameComponentLoader
{
	std::shared_ptr<GameComponent> CreateNew(std::string className);
	std::unordered_map<std::string, std::function<GameComponent*()>> &get_map();

	class ClassMapping 
	{
	public:
		ClassMapping(const char *name, std::function<GameComponent*()> func)
		{
			get_map().insert(std::make_pair(name, func));
		}
	};

	template<const char* NAME, typename T>
	class ClassConstructor 
	{
	protected:
		static ClassMapping m;
		ClassConstructor()
		{
			// Tell the compiler not to optimize m away
			(void)m;
		}
	};

	// Must be defined here because it is a templated variable 
	// https://stackoverflow.com/questions/1553854/template-static-variable
	template<const char* NAME, typename T>
	ClassMapping ClassConstructor<NAME, T>::m = ClassMapping(NAME, T::CreateNew);
}

// =========================== MAGIC MACROS ==================== //

// LOADABLE_CLASS
// Use this macro at the beginning of a GameComponent's class definition so it can be created with GameComponentLoader::CreateNew().
#define LOADABLE_CLASS(ClassType) \
private: \
static constexpr const char _ClassName[] = # ClassType; \
class _Constructor : public GameComponentLoader::ClassConstructor<_ClassName, _Constructor> \
{ \
public: \
	_Constructor() : ClassConstructor() {} \
	static ClassType ## * CreateNew() \
	{ \
		return new ClassType ## (); \
	} \
}; \
LOADABLE_CLASS_VARMAP(ClassType, String, std::string) \
LOADABLE_CLASS_VARMAP(ClassType, Int, int) \
LOADABLE_CLASS_VARMAP(ClassType, Float, float) \


// ------------------------------------------------------------- //

// LOADABLE_CLASS_VARMAP
// Helper macro to specify variable types when mapping variable names to setter functions.
#define LOADABLE_CLASS_VARMAP(ClassType, MapPostfix, ParamType) \
static std::unordered_map<std::string, std::function<void(ClassType *, ParamType)>>& _VarSetterMap_ ## MapPostfix ##() \
{ \
	static std::unordered_map<std::string, std::function<void(ClassType *, ParamType)>> map; \
	return map; \
} \
void _Set ## MapPostfix ## (std::string varName, ParamType value) override \
{ \
	auto it = _VarSetterMap_ ## MapPostfix ## ().find(varName); \
	if (it != _VarSetterMap_ ## MapPostfix ## ().end()) \
	{ \
		it->second(this, value); \
	} \
	else \
	{ \
		std::cout << #ClassType << "::_Set" << # MapPostfix << ": " << varName << " not found. Did you mark it with LOADABLE_VAR?" << std::endl; \
	} \
} \

// ------------------------------------------------------------- //

// LOADABLE_CLASS_VARMAP_VIRTUAL
// Helper macro for the base class so that we can set variables by name without knowing the outer class type.
#define LOADABLE_CLASS_VARMAP_VIRTUAL(MapPostfix, ParamType) \
public: \
virtual void _Set ## MapPostfix ## (std::string varName, ParamType value) {}; \
private: \

// ------------------------------------------------------------- //

// LOADABLE_CLASS_BASE
// Macro to call from the base GameComponent class.
#define LOADABLE_CLASS_BASE() \
LOADABLE_CLASS_VARMAP_VIRTUAL(String, std::string) \
LOADABLE_CLASS_VARMAP_VIRTUAL(Int, int) \
LOADABLE_CLASS_VARMAP_VIRTUAL(Float, float) \


// ------------------------------------------------------------- //

// LOADABLE_VAR
// Macro to map a member variable name to a setter function. Use this in a GameComponent's class definition for each variable you want to expose to be loaded from external data.
#define LOADABLE_VAR(VarName, MapPostfix, ParamType) \
private: \
	void _VarSetter_ ## VarName ## (ParamType value) \
	{ \
		VarName = value; \
	} \
	class _VarMapper_ ## VarName \
	{ \
	public: \
		_VarMapper_ ## VarName ## () \
		{ \
			if (_VarSetterMap_ ## MapPostfix ## ().find(#VarName) == _VarSetterMap_ ## MapPostfix ## ().end()) \
			{ \
				_VarSetterMap_ ## MapPostfix ## ().insert(std::make_pair(#VarName, &_VarSetter_## VarName ##)); \
			} \
		} \
	}; \
	_VarMapper_ ## VarName _varMapper_ ## VarName; \
public: \

// ------------------------------------------------------------- //

// LOADABLE_STRING
// Shortcut for strings
#define LOADABLE_STRING(VarName) LOADABLE_VAR(VarName, String, std::string) 

// ------------------------------------------------------------- //

// LOADABLE_INT
// Shortcut for integers
#define LOADABLE_INT(VarName) LOADABLE_VAR(VarName, Int, int) 

// ------------------------------------------------------------- //

// LOADABLE_FLOAT
// Shortcut for floats
#define LOADABLE_FLOAT(VarName) LOADABLE_VAR(VarName, Float, float) 

// ------------------------------------------------------------- //