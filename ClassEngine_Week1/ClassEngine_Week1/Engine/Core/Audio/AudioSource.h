#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "../../Rendering/3D/Component.h"

class AudioSource : public Component
{
public:

	AudioSource(std::string name_, bool shouldLoop_, bool is3d_, bool stream_, bool playOnCreate_ = false);
	virtual ~AudioSource();

	// Inherited via Component
	virtual void SetGuiEnabled(const bool enabled) override;
	virtual bool GuiEnabled() override;
	virtual void UpdateGUI(const float deltaTime) override;
	virtual bool OnCreate(GameObject* gameObject) override;
	virtual void Update(const float deltaTime_) override;

	void Play();
	bool IsPlaying();

private:
	
	bool guiEnabled = true;
	bool playOnCreate = false;

	std::string fileName;
	int channelId;
};

#endif // !AUDIOSOURCE_H



