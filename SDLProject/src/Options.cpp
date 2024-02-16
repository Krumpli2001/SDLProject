#include "tinyxml.h"

#include "Options.hpp"
#include "Engine.hpp"

void Options::readSettings(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cout << "Failed to load settings from " << source << "\n";
		return;
	}
	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == "setting") {
			savedScale = std::stod(e->Attribute("scale"));
			savedVolume = std::stoi(e->Attribute("volume"));
		}
	}
	std::cout << "Settings loaded\n";
}

void Options::saveSettings()
{
}
