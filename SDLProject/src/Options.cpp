#include <fstream>

#include "tinyxml.h"

#include "Engine.hpp"
#include "Options.hpp"

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
		if (e->Value() == std::string("setting")) {
			savedScale = std::stod(e->Attribute("scale"));
			savedVolume = std::stoi(e->Attribute("volume"));
		}
	}
	std::cout << "Settings loaded\n";
}

void Options::saveSettings()
{
	std::string str = "saves/settings.set";
	std::ofstream f(str);
	if (f.is_open()) {
		f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		f << "<settings>\n";
		f << "  <setting scale = \"" << savedScale << "\" volume=\"" << savedVolume << "\" />\n";
		f << "</settings>\n";
		f.close();
		std::cout << "settings saved\n";
	}
}
