#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "SpaceshIT!";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 144;
	this->contextSettings.antialiasingLevel = 0;
	for (auto i : sf::VideoMode::getFullscreenModes())
		this->videoModes.push_back(i);
}

void GraphicsSettings::saveToFile(const std::string path)
{
	// Open config(.ini) file
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameRateLimit;
		ofs << this->verticalSync;
		ofs << this->contextSettings.antialiasingLevel;
	}
	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	// Read config(.ini) file
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	ifs.close();
}