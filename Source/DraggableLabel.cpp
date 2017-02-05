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
    setColour(ColourIds::backgroundWhenEditingColourId, Colours::lightblue.withAlpha((float)0.1));
    setFont(Font("Roboto", 50, Font::plain));
    setJustificationType(Justification::centred);
}

DraggableLabel::~DraggableLabel()
{
}

void DraggableLabel::mouseEnter(const juce::MouseEvent &event)
{
    setColour(ColourIds::backgroundColourId, Colours::lightblue.withAlpha((float)0.1));
}

void DraggableLabel::mouseExit(const juce::MouseEvent &event)
{
    setColour(ColourIds::backgroundColourId, Colours::white);
}

void DraggableLabel::mouseDown(const juce::MouseEvent &event)
{
    bool ctrlDown = event.mods.isCtrlDown();
    if (ctrlDown)
    {
        double value = getTextValue().getValue();
        value = floor(value);
        setText(format(value), sendNotification);
    }
        
    enabled = false;
    mousePoint.setY(event.y);
}

void DraggableLabel::mouseDrag(const juce::MouseEvent &event)
{
    const float multiplier = 0.0;
    int delta = mousePoint.getY() - event.y;
    int absDelta = abs(delta);
    if(!enabled && absDelta < 5.0) return;
    if (!enabled)
    {
        enabled = true;
        mousePoint.setY(event.y);
        return;
    }
    bool ctrlDown = event.mods.isCtrlDown();
    //if(ctrlDown) absDelta = absDelta * .1;
    //if(absDelta < 50.0) absDelta *= 0.1;
    //else if (absDelta > 100) absDelta *= 2;
    double x = 0.125;
    for (int i = 10; i < 100; i+=10 )
    {
        if (absDelta < i)
        {
            absDelta *= x;
            break;
        }
        else
        {
            x *= 1.5;
        }
    }
    if(multiplier > 0.0) absDelta = (int)(absDelta * multiplier);
    if(absDelta == 0.0) return;
    double value = getTextValue().getValue();
    for (int i = 0; i < absDelta; i++)
    {
        if (ctrlDown)
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
        setText(format(value), sendNotification);
    }
    mousePoint.setY(event.y);
}

double DraggableLabel::valid(double d)
{
    if (d > 990.0) return 990.0;
    else if (d < 5.0) return 5.0;
    else return d;
}

String DraggableLabel::format(double d)
{
    stringstream ss;
    ss << fixed << setprecision(2) << d;
    return ss.str();
}
