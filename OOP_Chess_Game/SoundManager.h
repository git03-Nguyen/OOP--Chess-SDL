#pragma once

class SoundManager {
private:
	int themeMusicVolume;
	int eventMusicVolume;
public:
	SoundManager();
	~SoundManager();

	void setThemeMusicVolume(int themeMusicVolume);
	void setEventMusicVolume(int eventMusicVolume);

	int getThemeMusicVolume() const;
	int getEventMusicVolume() const;
	void playThemeMusic() const;
	void playEndMusic() const;
	void playPieceMoveMusic() const;
	void playCapturingMusic() const;
};
