#include "stdafx.h"
#include "AudioSystem.h"

AudioSystem::AudioSystem()
	: buffer(15), volume(1.0f)
{
	//시스템 생성
	System_Create(&system);

	// 시스템 리소스 및 사운드, 채널 생성 초기화
	system->init(buffer, FMOD_INIT_NORMAL, NULL);
	sound = new Sound*[buffer];
	channel = new Channel*[buffer];

	memset(sound, NULL, sizeof(Sound*) * buffer);
	memset(channel, NULL, sizeof(Channel*) * buffer);

}

AudioSystem::~AudioSystem()
{
	if (channel != NULL) {
		for (UINT i = 0; i < buffer; i++) {
			if (channel[i]) channel[i]->stop();
		}
	}
	if (sound != NULL) {
		for (UINT i = 0; i < buffer; i++) {
			if (sound[i]) sound[i]->release();
		}
	}
	SAFE_DELETE_ARRAY(channel);
	SAFE_DELETE_ARRAY(sound);

	if (system != NULL) {
		system->release();
		system->close();
	}

	sounds.clear();
}

void AudioSystem::AddSound(string name, string soundFile, bool bLoop)
{
	if (bLoop == true) {
		system->createStream(
			soundFile.c_str(),
			FMOD_LOOP_NORMAL,
			NULL,
			&sound[sounds.size()]
		);
	}
	else {
		system->createStream(
			soundFile.c_str(),
			FMOD_DEFAULT,
			NULL,
			&sound[sounds.size()]
		);
	}

	sounds[name] = &sound[sounds.size()];

}

void AudioSystem::Play(string name, float volume)
{
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			// 비어있는 채널, 순서대로 넣는다
			system->playSound(FMOD_CHANNEL_FREE, * iter->second, false, & channel[count]);

			channel[count]->setVolume(volume);
		}
	}
}

void AudioSystem::Stop(string name)
{
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			channel[count]->stop();
			break;
		}
	}
}

void AudioSystem::Pause(string name)
{
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			channel[count]->setPaused(true);
			break;
		}
	}
}

void AudioSystem::Resume(string name)
{
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool AudioSystem::Playing(string name)
{
	bool bPlay = false;
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			channel[count]->isPlaying(&bPlay);
			break;
		}
	}

	return bPlay;
}

bool AudioSystem::Paused(string name)
{
	bool bPaused = false;
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			channel[count]->getPaused(&bPaused);
			break;
		}
	}

	return bPaused;
}

void AudioSystem::Update()
{
	system->update();
}

void AudioSystem::Volume(string name, float volume)
{
	int count = 0;

	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++) {
		if (name == iter->first) {
			channel[count]->setVolume(volume);
			break;
		}
	}
}
