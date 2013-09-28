#include "AudioManager.h"
#include "RandomGenerator.h"

#include "StringUtilities.h"

AudioBufferGroup::AudioBufferGroup(int audioGroupID)
	:
	mAudioGroupID(audioGroupID)
	{

	}

int AudioBufferGroup::GetAudioGroupID() const
	{
	return mAudioGroupID;
	}

sf::SoundBuffer * AudioBufferGroup::GetRandomBuffer()
	{
	if ( mAudioBuffers.empty() )
		return nullptr;
	if ( mAudioBuffers.size() < 2 )
		return &mAudioBuffers.front();

	return &mAudioBuffers.at( Random::Between(0, mAudioBuffers.size() - 1) );
	}

bool AudioBufferGroup::AddAudioBuffer(string file)
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

void AudioBufferGroup::ClearBuffers()
	{
	mAudioBuffers.clear();
	}

// ActiveSound

ActiveSound::ActiveSound(sf::SoundBuffer & soundBuffer, bool deleteAfterDone)
	:
	mDeleteNow(false),
	mDeleteAfterDone( deleteAfterDone ),
	mSound(soundBuffer)
	{

	}

void ActiveSound::Play()
	{
	mSound.play();
	}

void ActiveSound::SetVolume(const float volume)
	{
	mSound.setVolume(volume);
	}

void ActiveSound::SetPitch(const float pitch)
	{
	mSound.setPitch(pitch);
	}

void ActiveSound::SetMaxVolumeDistance(const float dist)
	{
	mSound.setMinDistance( dist );
	}

void ActiveSound::SetAttenuation( const float atten )
	{
	mSound.setAttenuation( atten );
	}

void ActiveSound::SetLooping( const bool loop )
	{
	mSound.setLoop(loop);
	}

void ActiveSound::SetPosition(sf::Vector3f pos)
	{
	mSound.setPosition(pos);
	}

void ActiveSound::SetRelativeToListener(bool relative)
	{
	mSound.setRelativeToListener(relative);
	}

float ActiveSound::GetVolume() const
	{
	return mSound.getVolume();
	}

float ActiveSound::GetPitch() const
	{
	return mSound.getPitch();
	}

bool ActiveSound::GetDone() const
	{
	return mSound.getStatus() == sf::SoundSource::Stopped ? true : false;
	}

sf::Vector3f ActiveSound::GetPosition() const
	{
	return mSound.getPosition();
	}

void ActiveSound::SetDeleteNow(bool deleteNow)
	{
	mDeleteNow = deleteNow;
	}

void ActiveSound::SetDeleteAfterDone(bool deleteAfterDone)
	{
	mDeleteAfterDone = deleteAfterDone;
	}

bool ActiveSound::GetDeleteNow() const
	{
	return mDeleteNow;
	}

bool ActiveSound::GetDeleteAfterDone() const
	{
	return mDeleteAfterDone;
	}

sf::Sound * ActiveSound::GetSoundPtr()
	{
	return &mSound;
	}

const sf::SoundBuffer * ActiveSound::GetSoundBufferPtr()
	{
	return mSound.getBuffer();
	}

// AudioManager
AudioManager::AudioManager()
	:
	mSoundBuffers(),
	mSounds(),
	mMusic()
	{
	mMusic.setRelativeToListener(true);
	mMusic.setPosition(0.0f,0.0f,0.0f);
	SetListenerDirection( 0.0f, -1.0f, 0.0f );
	LoadEnums();
	string file("../Resources/Audio/lasershot.wav");
	LoadAudioBuffer(AudioGroups::AUDIO_LASER, ToPlatformPath(file) );
	file = "../Resources/Audio/laserHigh.ogg";
	LoadAudioBuffer(AudioGroups::AUDIO_LASER, ToPlatformPath(file) );
	file = "../Resources/Audio/laserMed.ogg";
	LoadAudioBuffer(AudioGroups::AUDIO_LASER, ToPlatformPath(file) );
	file = "../Resources/Audio/laserLow.ogg";
	LoadAudioBuffer(AudioGroups::AUDIO_LASER, ToPlatformPath(file) );
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
ManagedSoundWeak AudioManager::PlaySound(int audioGroupID, const sf::Vector3f &pos, float volume, float pitch, float maxVolumeDist, float attenuation)
	{
	// find sound with id
	sf::SoundBuffer * pBuffer = nullptr;
	for ( AudioBufferGroup & pIndex : mSoundBuffers )
		{
		if ( pIndex.GetAudioGroupID() == audioGroupID )
			{
			pBuffer = pIndex.GetRandomBuffer();
			break;
			}
		}

	if ( !pBuffer )
		{
		// Log Warning not found or no associated buffers.
		return ManagedSoundWeak();
		}

	ManagedSound managedSound( new ActiveSound(*pBuffer) );
	managedSound->SetRelativeToListener(false);
	// TODO: make this a parameter, and attenuation too
	managedSound->SetMaxVolumeDistance(maxVolumeDist);
	managedSound->SetAttenuation( attenuation );
	managedSound->SetPosition( pos );
	//managedSound->SetBuffer( *pBuffer );
	managedSound->SetVolume( volume );
	managedSound->SetPitch( pitch );
	managedSound->Play();

	mSounds.push_back(managedSound);

	return ManagedSoundWeak(managedSound);
	}

ManagedSoundWeak AudioManager::PlaySound(int soundID, const sf::Vector3f &pos, float maxVolumeDist, float attenuation)
	{
	return PlaySound(soundID, pos, 100.0f, 1.0f, maxVolumeDist, attenuation);
	}

ManagedSoundWeak AudioManager::PlaySound(int soundID, const sf::Vector3f &pos)
	{
	return PlaySound(soundID, pos, 100.0f, 1.0f, 1.0f, 1.0f);
	}

void AudioManager::UnloadBuffersAndSounds()
	{
	mSounds.clear();

	for ( unsigned int i = 0; i < mSoundBuffers.size(); ++i )
		{
		mSoundBuffers[i].ClearBuffers();
		}
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

void AudioManager::Update()
	{
	// code for removing sounds that are done.
	for ( unsigned int i = 0; i < mSounds.size();  )
		{

		if ( mSounds.at(i)->GetDeleteNow() )
			{
			mSounds.erase( mSounds.begin() + i );
			continue;
			}

		if ( mSounds.at(i)->GetDeleteAfterDone() && mSounds.at(i)->GetDone() )
			{
			mSounds.erase( mSounds.begin() + i );
			continue;
			}

		++i;
		}
	}

void AudioManager::LoadEnums()
	{
	for ( unsigned int i = AudioGroups::AUDIO_START + 1; i < AudioGroups::AUDIO_END; ++i )
		{
		mSoundBuffers.emplace_back(i);
		}
	}

bool AudioManager::LoadAudioBuffer(int audioGroupID, const string &file)
	{
	AudioBufferGroup * pData = nullptr;
	for ( unsigned int i = 0; i < mSoundBuffers.size(); ++i )
		{
		if ( mSoundBuffers[i].GetAudioGroupID() == audioGroupID )
			{
			pData = &mSoundBuffers[i];
			break;
			}
		}

	if ( pData )
		{
		return pData->AddAudioBuffer(file);
		}
	else
		{
		return false;
		}
	}
