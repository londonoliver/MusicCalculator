//
//  DraggableLabel.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/3/17.
//
//

#include "DraggableLabel.hpp"
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

DraggableLabel::DraggableLabel()
{
}

DraggableLabel::~DraggableLabel()
{
}

void DraggableLabel::mouseDown(const juce::MouseEvent &event)
{
    enabled = false;
    mousePoint.setY(event.y);
}

void DraggableLabel::mouseDrag(const juce::MouseEvent &event)
{
    const float multiplier = 0.0;
    int delta = mousePoint.getY() - event.y;
    int absDelta = abs(delta);
    if(!enabled && absDelta < 5.0) return;
    if(!enabled)
    {
        enabled = true;
        mousePoint.setY(event.y);
        return;
    }
    bool ctrlDown = event.mods.isCtrlDown();
    //if(ctrlDown) absDelta = absDelta * .1;
    if(absDelta < 50.0) absDelta = absDelta * .1;
    if(multiplier > 0.0) absDelta = (int)(absDelta * multiplier);
    if(absDelta == 0.0) return;
    double value = getTextValue().getValue();
    for (int i = 0; i < absDelta; i++)
    {
        if(ctrlDown)
        {
            if(delta < 0.0) value -= 0.01;
            else value += 0.01;
        }
        else
        {
            if(delta < 0.0) value -= 1.0;
            else value += 1.0;
        }
        value = valid(value);
        stringstream ss;
        ss << fixed << setprecision(2) << value;
        setText(ss.str(), dontSendNotification);
    }
    mousePoint.setY(event.y);
}

double DraggableLabel::valid(double d)
{
    if (d > 999.0) return 999.0;
    else if (d < 0.0) return 0.0;
    else return d;
}
