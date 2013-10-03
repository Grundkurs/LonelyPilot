#ifndef ISTATE_H
#define ISTATE_H
#include "SFML/Graphics.hpp"

class Game;

enum class State
    {
        Menu,
        Game,
        Options

    };


class IState
{
protected:


public:

        virtual             ~IState();
const	virtual	State		GetStateInput() = 0;

        virtual void        Update(const sf::Time& deltaFrame) = 0;
        virtual void        Render() = 0;
};

#endif //ISTATE_H

