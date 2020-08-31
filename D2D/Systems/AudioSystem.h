#pragma once
using namespace FMOD;

class AudioSystem {
public:
	AudioSystem();
	~AudioSystem();

	// 외부에서 음원을 추가 (이름, 사운드 파일 경로, 루프)
	void AddSound(string name, string soundFile, bool bLoop = false);
	void Play(string name, float volume = 1.0f);
	void Stop(string name);
	void Pause(string name);
	void Resume(string name);

	bool Playing(string name);
	bool Paused(string name);
	
	void Update();

	void Volume(string name, float volume);
	float Volume() { return volume; }

private:
	System* system;
	Sound** sound;	// 음원
	Channel** channel;	// 채널

	UINT buffer;	// 동시에 재생되는 갯수

	// 이름 , 미디
	map<string, Sound**> sounds;
	map<string, Sound**>::iterator iter;

	float volume;
};