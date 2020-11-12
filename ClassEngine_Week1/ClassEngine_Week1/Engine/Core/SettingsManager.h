
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include "../nlohmann/json.hpp"


struct WindowSettings {

	static WindowSettings FromJson(std::string str) {
		WindowSettings ws = WindowSettings();
		std::cout << str << std::endl;
		nlohmann::json j = nlohmann::json::parse(str);
		j.at("name").get_to(ws.name);
		j.at("width").get_to(ws.width);
		j.at("height").get_to(ws.height);
		return ws;
	}

	std::string name;
	int width, height;

	std::string ToJson() {
		nlohmann::json j = { {"name", name}, {"width", width}, {"height", height} };
		return j.dump();
	}


};

class SettingsManager
{
public:
	SettingsManager() = delete;
	SettingsManager(const SettingsManager&) = delete; //Disable copy constructor lvalue
	SettingsManager(SettingsManager&&) = delete; //Disable move constructor lvalue
	SettingsManager& operator = (const SettingsManager&) = delete; //Disable copy constructor rvalue
	SettingsManager& operator = (SettingsManager&&) = delete; //Disable move constructor rvalue

	static void Init();
	static void SaveSettings();
	static void LoadSettings();

	static void SetWindowSettings(WindowSettings settings);
	static WindowSettings GetWindowSettings();

private:
	class Settings {
	public:
		WindowSettings windowSettings;
	};

	static Settings settings;
	static std::string outputName;
};
#endif // !SETTINGSMANAGER_H


