#include "AudioHandler.h"
#include "AudioSource.h"
#include "../../Rendering/3D/GameObject.h"
#include"../../imgui-master/imgui.h"



AudioSource::AudioSource(std::string name_, bool shouldLoop_, bool is3d_, bool stream_)
{
    channelId = -1;
    fileName = name_;
    AudioHandler::GetInstance()->LoadSound(name_, shouldLoop_, is3d_, stream_);
}

AudioSource::~AudioSource()
{
}

void AudioSource::SetGuiEnabled(const bool enabled)
{
    guiEnabled = enabled;
}

bool AudioSource::GuiEnabled()
{
    return false;
}

void AudioSource::UpdateGUI(const float deltaTime)
{
    if (!guiEnabled) { return; }

    if (ImGui::Button("Play Sound")) {
        Play();
    }
}

bool AudioSource::OnCreate(GameObject* gameObject)
{
    this->gameObject = gameObject;
    return false;
}

void AudioSource::Update(const float deltaTime_)
{
}

void AudioSource::Play()
{
    channelId = AudioHandler::GetInstance()->PlaySound(fileName, gameObject->GetPosition());
}

bool AudioSource::IsPlaying()
{
    return AudioHandler::GetInstance()->ChannelIsPlayingSound(channelId);
}
