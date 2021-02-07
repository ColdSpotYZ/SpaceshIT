/*
Team member: Jason Chua
Group: CookieZ
studentID: S10195450H
*/
#pragma once
class GraphicsSettings
{
public:
	GraphicsSettings();

	// Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	Vector<sf::VideoMode> videoModes;

	// Functions
	void saveToFile(const std::string path);

	void loadFromFile(const std::string path);
};