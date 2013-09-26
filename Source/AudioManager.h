#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <memory>
#include <vector>
#include <string>
using std::string;
using std::vector;

#include "SFML/Audio.hpp"

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

class ActiveSound
{
public:
	ActiveSound( sf::SoundBuffer & soundBuffer, bool deleteAfterDone = true );

	void SetVolume( const float volume );
	void SetPitch( const float pitch );

	void SetPosition( sf::Vector3f pos );
	void SetRelativeToListener( bool relative = true );

	float GetVolume() const;
	float GetPitch() const;

	sf::Vector3f GetPosition() const;
	bool GetRelativeToListener() const;

	void SetDeleteNow( bool deleteNow = true );
	void SetDeleteAfterDone( bool deleteAfterDone = true );

	bool GetDeleteNow() const;
	bool GetDeleteAfterDone() const;

	sf::Sound * GetSoundPtr();
	const sf::SoundBuffer * GetSoundBufferPtr();

private:
	bool mDeleteNow;
	bool mDeleteAfterDone;
	sf::Sound mSound;
};

typedef std::shared_ptr<ActiveSound> ManagedSound;
typedef std::weak_ptr<ActiveSound> ManagedSoundWeak;

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
