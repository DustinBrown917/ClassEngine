#include "AudioHandler.h"

std::unique_ptr<AudioHandler> AudioHandler::instance = nullptr;
std::map<std::string, FMOD::Sound*> AudioHandler::sounds = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channels = std::map<int, FMOD::Channel*>();

AudioHandler* AudioHandler::GetInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new AudioHandler());
	}
	return instance.get();
}

bool AudioHandler::OnCreate(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forward_, glm::vec3 up_)
{
	if (FMOD::System_Create(&system) != FMOD_RESULT::FMOD_OK) {
		Debug::Error("Failed to create FMOD System", "AudioHandler.cpp", __LINE__);
		return false;
	}
	
	int driverNum = 0;
	if (system->getNumDrivers(&driverNum) != FMOD_RESULT::FMOD_OK || driverNum == 0) {
		Debug::Error("No audio drivers found", "AudioHandler.cpp", __LINE__);
		return false;
	}

	if (system->init(10, FMOD_INIT_NORMAL, nullptr) != FMOD_RESULT::FMOD_OK) {
		Debug::Error("FMOD Initialization failed", "AudioHandler.cpp", __LINE__);
		return false;
	}

	if (system->set3DListenerAttributes(0, &glmToFMOD(position_), &glmToFMOD(velocity_), &glmToFMOD(forward_), &glmToFMOD(up_)) != FMOD_RESULT::FMOD_OK) {
		Debug::Error("Failed to set 3D listener attributes", "AudioHandler.cpp", __LINE__);
		return false;
	}

	return true;
}

void AudioHandler::OnDestroy()
{
	if (sounds.size() > 0) {
		for (auto sound : sounds) {
			sound.second->release();
			sound.second = nullptr;
		}
		sounds.clear();
	}

	if (channels.size() > 0) {
		for (auto channel : channels) {
			channel.second->stop();
			channel.second = nullptr;
		}
		channels.clear();
	}

	system->release();
	system = nullptr;
}

void AudioHandler::Update(const float deltaTime)
{
	system->update();
}

AudioHandler::AudioHandler() : system(nullptr)
{
}

AudioHandler::~AudioHandler()
{
	OnDestroy();
}

FMOD_VECTOR AudioHandler::glmToFMOD(glm::vec3 vec_)
{
	FMOD_VECTOR v = FMOD_VECTOR();
	v.x = vec_.x * -1;
	v.y = vec_.y;
	v.z = vec_.z;
	return v;
}

void AudioHandler::LoadSound(std::string name_, bool shouldLoop_, bool is3d_, bool stream_)
{
	if (GetSound(name_) != nullptr) { return; }

	FMOD_MODE mode = FMOD_MODE();
	mode = FMOD_DEFAULT;

	if (shouldLoop_) {
		mode |= FMOD_LOOP_NORMAL;
	}
	else {
		mode |= FMOD_LOOP_OFF;
	}

	if (is3d_) {
		mode |= FMOD_3D;
	}
	else {
		mode |= FMOD_2D;
	}

	if (stream_) {
		mode |= FMOD_CREATESTREAM;
	}
	else {
		mode |= FMOD_CREATECOMPRESSEDSAMPLE;
	}

	FMOD::Sound* s = nullptr;

	if (system->createSound(("Resources/Audio/" + name_).c_str(), mode, nullptr, &s) != FMOD_OK) {
		Debug::Error("Failed to load sound: " + name_, "AudioHandler.cpp", __LINE__);
		return;
	}

	sounds[name_] = s;
}

FMOD::Sound* AudioHandler::GetSound(std::string str_)
{
	if (sounds.find(str_) != sounds.end()) {
		return sounds[str_];
	}
	return nullptr;
}

int AudioHandler::PlaySound(std::string name_, glm::vec3 position_, glm::vec3 velocity, float volume)
{
	int channelId = -1;

	FMOD::Sound* s = GetSound(name_);

	if (s == nullptr) {
		LoadSound(name_, false, true, false);

		s = s = GetSound(name_);

		if (s == nullptr) {
			Debug::Error("Could not play sound: " + name_, "AudioHandler.cpp", __LINE__);
			return -1;
		}
	}

	FMOD::Channel* c = nullptr;
	FMOD_MODE mode = FMOD_MODE();
	s->getMode(&mode);

	system->playSound(GetSound(name_), nullptr, true, &c);

	if (mode & FMOD_2D == FMOD_2D) {
		if (c->set3DAttributes(&glmToFMOD(position_), &glmToFMOD(velocity)) != FMOD_OK) {
			Debug::Error("Could not set 3d attributes on sound: " + name_, "AudioHandler.cpp", __LINE__);
			return -1;
		}
	}

	if (c->setVolume(volume) != FMOD_OK) {
		Debug::Error("Could not set volume on sound: " + name_, "AudioHandler.cpp", __LINE__);
		return -1;
	}

	c->setPaused(false);

	channelId = channelCount;
	channelCount++;

	channels[channelId] = c;

	return channelId;
}

void AudioHandler::UpdateChannelPhysics(int channelId_, glm::vec3 position_, glm::vec3 velocity_)
{
	FMOD::Channel* channel = nullptr;
	if (channels.find(channelId_) != channels.end()) {
		channel = channels[channelId_];
	}

	if (channel == nullptr) {
		Debug::Error("Channel not found: " + channelId_, "AudioHandler.cpp", __LINE__);
		return;
	}

	channel->set3DAttributes(&glmToFMOD(position_), &glmToFMOD(velocity_));

}

bool AudioHandler::ChannelIsPlayingSound(int channelId_)
{
	FMOD::Channel* channel = GetChannel(channelId_);

	if (channel == nullptr) {
		Debug::Error("Channel not found: " + channelId_, "AudioHandler.cpp", __LINE__);
		return false;
	}

	bool isPlaying = false;
	channel->isPlaying(&isPlaying);

	return isPlaying;
}

void AudioHandler::SetChannelPause(int channelId_, bool paused_)
{
	FMOD::Channel* channel = GetChannel(channelId_);

	if (channel == nullptr) {
		Debug::Error("Channel not found: " + channelId_, "AudioHandler.cpp", __LINE__);
		return;
	}

	channel->setPaused(paused_);
}

FMOD::Channel* AudioHandler::GetChannel(int channelId_)
{
	FMOD::Channel* channel = nullptr;
	if (channels.find(channelId_) != channels.end()) {
		channel = channels[channelId_];
	}

	return channel;
}




