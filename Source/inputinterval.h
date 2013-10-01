#ifndef INPUTINTERVAL_H
#define INPUTINTERVAL_H
#include "SFML/Graphics.hpp"
class InputInterval
{
public:
    InputInterval();
    ~InputInterval();

    void Reset();
    void Update(const sf::Time& deltaFrame);
    bool CanPressButton();


private:
    float mTimeStamp;
    float mTimeTrigger;
    float mOffSet;
};

#endif // INPUTINTERVAL_H
