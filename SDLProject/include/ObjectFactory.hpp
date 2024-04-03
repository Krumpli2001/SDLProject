#pragma once

#include <functional>
#include <map>

#include "GameObject.hpp"

class ObjectFactory
{
private:
	ObjectFactory() {};
	static ObjectFactory* ObjectFaclory_Instance;

	//bevesz egy props-ot es csinal belole game object-et, amit meg egy mappa belerak a tipusaval
	std::map<std::string, std::function<GameObject* (Properties* props)>> ObjectFactory_TypeRegistry;

public:

	//gameObj létrehozása
	GameObject* CreateObject(std::string type, Properties* props);

	//adott gameObj regisztrálása (inicializálásban)
	void RegiseterType(std::string className, std::function<GameObject* (Properties* props)> type);

	static inline ObjectFactory* GetInstance(bool del = false)
	{
		if (del) {
			if (ObjectFaclory_Instance) {
				delete ObjectFaclory_Instance;
			}
			ObjectFaclory_Instance = nullptr;
			return nullptr;
		}
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

	//regisztrálás
	Registrar(std::string className)
	{
		//https://stackoverflow.com/questions/20353210/what-is-the-purpose-of-stdfunction-and-how-do-i-use-it
		//ezt att kene irni hogy erthetobb legyen + sajat szavakkal (btw jo igy is)
		ObjectFactory::GetInstance()->RegiseterType(className, [](Properties* props)->GameObject* { return new Type(props); });
	}
};