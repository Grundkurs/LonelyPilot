#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML\Audio.hpp>
#include <string>


class SoundManager{
	
	sf::Music _song; 
	std::string _currentSong; 

public:
	SoundManager();
	~SoundManager();


	void Init();
	bool _isPlaying;

	void PlaySong(const std::string& song);

};


#endif //SOUNDMANAGER_H