#pragma once

#include <map>
//#include <memory>
#include <functional>

#include "GameObject.hpp"

class ObjectFactory
{
private:
	ObjectFactory() {};
	static ObjectFactory* ObjectFaclory_Instance;
	std::map < std::string, std::function < GameObject* (Properties* props) > > ObjectFactory_TypeRegistry;

public:
	GameObject* CreateObject(std::string type, Properties* props);
	void RegiseterType(std::string className, std::function < GameObject* (Properties* props) > type);
	inline static ObjectFactory* GetInstance()
	{
		if (ObjectFaclory_Instance == nullptr)
		{
			ObjectFaclory_Instance = new ObjectFactory();
		}
		return ObjectFaclory_Instance;
	}
};

template < class Type >
class Registrar
{
public:
	Registrar(std::string className)
	{
		ObjectFactory::GetInstance()->RegiseterType(className, [](Properties* props)->GameObject* {return new Type(props); });
	}
};

