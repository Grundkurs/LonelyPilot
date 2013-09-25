#include "AudioManager.h"
#include "RandomGenerator.h"

AudioData::AudioData(int soundID)
	:
	mSoundID(soundID)
	{

	}

int AudioData::GetSoundID() const
	{
	return mSoundID;
	}

sf::SoundBuffer * AudioData::GetRandomBuffer()
	{
	if ( mAudioBuffers.empty() )
		return nullptr;
	if ( mAudioBuffers.size() < 2 )
		return &mAudioBuffers.front();

	return &mAudioBuffers.at( Random::Between(0, mAudioBuffers.size() - 1) );
	}

bool AudioData::AddAudioBuffer(string file)
	{
	mAudioBuffers.emplace_back();
	sf::SoundBuffer & buffer = mAudioBuffers.back();
	if ( !buffer.loadFromFile( file ) )
		{
		mAudioBuffers.pop_back();
		return false;
		}
	else
		{
		return true;
		}
	}

// ctor
AudioManager::AudioManager()
	:
	mSoundBuffers(),
	mSounds(),
	mMusic()
	{
	mMusic.setRelativeToListener(true);
	mMusic.setPosition(0.0f,0.0f,0.0f);
	}

// listener
void AudioManager::SetListenerPosition(float x, float y, float z)
	{
	sf::Listener::setPosition(x, y, z);
	}

void AudioManager::SetListenerDirection(float x, float y, float z)
	{
	sf::Listener::setDirection(x, y, z);
	}

void AudioManager::SetListenerGlobalVolume(float volume)
	{
	sf::Listener::setGlobalVolume(volume);
	}

// sounds
ManagedSoundWeak AudioManager::PlaySound(int soundID, const sf::Vector3f &pos, float volume, float pitch)
	{
	// find sound with id
	sf::SoundBuffer * pBuffer = nullptr;
	for ( AudioData & pIndex : mSoundBuffers )
		{
		if ( pIndex.GetSoundID() == soundID )
			{
			pBuffer = pIndex.GetRandomBuffer();
			break;
			}
		}

	if ( !pBuffer )
		{
		// Log Warning not found or no associated buffers.
		return std::weak_ptr<sf::Sound>();
		}

	ManagedSound managedSound( new sf::Sound() );
	managedSound->setPosition( pos );
	managedSound->setBuffer( *pBuffer );
	managedSound->setVolume( volume );
	managedSound->setPitch( pitch );

	mSounds.push_back(managedSound);

	return ManagedSoundWeak(managedSound);
	}

void AudioManager::UnloadBuffersAndSounds()
	{
	mSounds.clear();
	mSoundBuffers.clear();
	}

// music
bool AudioManager::LoadAndPlayMusic(const string & file)
	{
	if ( !mMusic.openFromFile(file) )
		{
		// Log warning
		return false;
		}

	StartMusic();
	return true;
	}

void AudioManager::SetMusicVolume(float volume)
	{
	mMusic.setVolume(volume);
	}

void AudioManager::StartMusic()
	{
	mMusic.setLoop(true);
	mMusic.play();
	}

void AudioManager::StopMusic()
	{
	mMusic.stop();
	}
