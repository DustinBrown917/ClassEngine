#include "SettingsManager.h"

SettingsManager::Settings SettingsManager::settings = SettingsManager::Settings();
std::string SettingsManager::outputName = "";

void SettingsManager::Init()
{
	outputName = "EngineSettings.json";
}

void SettingsManager::SaveSettings()
{
	std::ofstream out(outputName);
	out << settings.windowSettings.ToJson();
	out.close();
}

void SettingsManager::LoadSettings()
{
	std::ifstream file(outputName);
	std::string json = "";
	std::string line = "";
	while (std::getline(file, line)) {
		json += line;
	}

	file.close();
	settings.windowSettings = WindowSettings::FromJson(json);
}

void SettingsManager::SetWindowSettings(WindowSettings settings_)
{
	settings.windowSettings = settings_;
}

WindowSettings SettingsManager::GetWindowSettings()
{
	return settings.windowSettings;
}
