#pragma once
#include "GameComponent.h"
#include <map>
#include <functional>
#include <string>


class PlayerComponent : public GameComponent
{
//	DECLARE_LOADABLE(PlayerComponent);
	/*
private: 
	class _Loader : BaseComponentLoader 
	{
	public:
		static void Setup()
		{
			static bool added = false;
			if (!added)
			{
				added = true;
				BaseComponentLoader::LoaderFuncs.insert(std::make_pair("PlayerComponent", &PlayerComponent::_Loader::CreateNew));
			}
		}
		static PlayerComponent* CreateNew()
		{
			return new PlayerComponent();
		}
	};
	*/

		
public:
	void Update(float deltaTime) override {};

};