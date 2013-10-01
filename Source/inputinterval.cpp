#include "InputInterval.h"
#include <iostream>

InputInterval::InputInterval()
    :	mOffSet(.005f),
        mTimeStamp(0.f),
        mTimeTrigger(0.f)
    {
    Reset();
    }


InputInterval::~InputInterval()
{
}


void InputInterval::Reset()
    {
    mTimeTrigger = mTimeStamp + mOffSet;
    }

void InputInterval::Update(const sf::Time& deltaFrame)
    {
    mTimeStamp += deltaFrame.asSeconds();
    }

bool InputInterval::CanPressButton()
    {
    return mTimeStamp > mTimeTrigger ? true : false;
    }
