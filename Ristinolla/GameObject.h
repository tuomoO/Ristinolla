#pragma once

#include "RenderComponent.h"
#include "TransformComponent.h"
#include <typeinfo>

#include <list>
#include <unordered_map>
#include <utility>

class GameObject
{
public:
	GameObject();
    ~GameObject();

	void add(Component* component);
	template<typename T> T* getComponent();

private:
	using ComponentMap = std::unordered_map < const std::type_info*, Component* > ;
	using CompIt = ComponentMap::iterator;
	ComponentMap mComponents;
};

template<typename T>
T* GameObject::getComponent()
{
	CompIt i = mComponents.find(&typeid(T));
	if (i == mComponents.end())
		return nullptr;
	else
		return static_cast<T*>((*i).second);
}

