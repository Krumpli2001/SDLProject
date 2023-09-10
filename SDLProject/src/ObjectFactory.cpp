#include "ObjectFactory.hpp"

ObjectFactory* ObjectFactory::ObjectFaclory_Instance = nullptr;

GameObject* ObjectFactory::CreateObject(std::string type, Properties* props)
{
	GameObject* object = nullptr;
	auto it = ObjectFactory_TypeRegistry.find(type);
	if (it != ObjectFactory_TypeRegistry.end()) { object = it->second(props); }
	return object;
}

void ObjectFactory::RegiseterType(std::string className, std::function<GameObject* (Properties* props)> type)
{
	ObjectFactory_TypeRegistry[className] = type;
}