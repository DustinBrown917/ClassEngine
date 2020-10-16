#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <string>
#include <map>
#include <memory>
#include <fmod.hpp>
#include <glm/glm.hpp>
#include "../Debug.h"
#include "AudioSource.h"

class AudioHandler
{
public:
	AudioHandler(const AudioHandler&) = delete; //Disable copy constructor lvalue
	AudioHandler(AudioHandler&&) = delete; //Disable move constructor lvalue
	AudioHandler& operator = (const AudioHandler&) = delete; //Disable copy constructor rvalue
	AudioHandler& operator = (AudioHandler&&) = delete; //Disable move constructor rvalue

	static AudioHandler* GetInstance();

	bool OnCreate(glm::vec3 position_ = glm::vec3(0) , glm::vec3 velocity_ = glm::vec3(0), glm::vec3 forward_ = glm::vec3(0, 0, -1), glm::vec3 up_ = glm::vec3(0, 1, 0));
	void OnDestroy();
	void Update(const float deltaTime);

private:
	//Constructor/Destructor is made private for singletons
	AudioHandler();
	~AudioHandler();

	static std::unique_ptr<AudioHandler> instance;
	friend std::default_delete<AudioHandler>;
	friend AudioSource;

	FMOD::System* system;

	static std::map<std::string, FMOD::Sound*> sounds;
	static std::map<int, FMOD::Channel*> channels;
	int channelCount = 0;

	FMOD_VECTOR glmToFMOD(glm::vec3 vec_);
	void LoadSound(std::string name_, bool shouldLoop_, bool is3d_, bool stream_);
	FMOD::Sound* GetSound(std::string str_);
	int PlaySound( std::string name_, glm::vec3 position_, glm::vec3 velocity = glm::vec3(0), float volume = 1.0f);
	void UpdateChannelPhysics(int channelId_, glm::vec3 position_, glm::vec3 velocity_ = glm::vec3(0));
	bool ChannelIsPlayingSound(int channelId_);
	void SetChannelPause(int channelId_, bool paused_);
	FMOD::Channel* GetChannel(int channelId_);
};

#endif // !AUDIOHANDLER_H



