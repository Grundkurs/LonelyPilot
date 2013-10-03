#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include <memory>
#include "Option.h"

class Game;
class OptionState : public IState
{

public:
                                        OptionState(Game* pGame);
                                        ~OptionState();
    const   State                       GetStateInput();
            void						Update(const sf::Time& deltaFrame);
            void						Render();
private:


            Game*                       mpGame;
    const	State                       mState;
            std::shared_ptr<Option>		sPtr_NewGame;
            std::shared_ptr<Option>		sPtr_Options;
            std::shared_ptr<Option>		sPtr_Exit;

            Option*						mpCurrentOption;
};

#endif // OPTIONSTATE_H
