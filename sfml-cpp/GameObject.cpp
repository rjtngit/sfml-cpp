#include "GameObject.h"
#include "TransformComponent.h"

GameObject::GameObject(int x, int y)
{
	TransformComponent* comp = AddComponent<TransformComponent>(x, y);
}

void GameObject::InitFromFile(std::string path)
{

}
