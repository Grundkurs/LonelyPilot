#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <memory>
#include <vector>
#include <string>
using std::string;
using std::vector;

#include "SFML/Audio.hpp"

//template<sf::Sound> using ManagedSound = std::shared_ptr<sf::Sound>;
//template<sf::Sound> using ManagedSoundWeak = std::weak_ptr<sf::Sound>;

typedef std::shared_ptr<sf::Sound> ManagedSound;
typedef std::weak_ptr<sf::Sound> ManagedSoundWeak;

class AudioData
{
public:
	AudioData( int soundID );
	int GetSoundID() const;
	sf::SoundBuffer * GetRandomBuffer();

	bool AddAudioBuffer(string file);

private:
	vector<sf::SoundBuffer> mAudioBuffers;
	int mSoundID;
};

class AudioManager
{
public:
	AudioManager();

	// Music code
	bool LoadAndPlayMusic( const string & file );
	void SetMusicVolume( float volume );
	void StartMusic();
	void StopMusic();

	// Listener code
	void SetListenerPosition( float x, float y, float z );
	void SetListenerDirection( float x, float y, float z );
	void SetListenerGlobalVolume(float volume);

	ManagedSoundWeak PlaySound( int soundID, const sf::Vector3f & pos, float volume = 100.0f, float pitch = 1.0f);
	void UnloadBuffersAndSounds();

	// need to call this each frame to remove finished sounds
	void Update();

private:
	// sounds
	vector<AudioData> mSoundBuffers;
	vector<ManagedSound> mSounds;

	// music
	sf::Music mMusic;
};

#endif // AUDIOMANAGER_H
