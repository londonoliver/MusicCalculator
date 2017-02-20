//
//  Spinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/15/17.
//
//

#include "Spinner.h"
#include <math.h>
#include <iostream>

using namespace std;

Spinner::Spinner (SpinnerType type, int min, int max)
{
    this->type = type;
    this->min = min;
    this->max = max;
    
    setFont (Font ("Roboto", 50, Font::plain));
    
    setJustificationType (Justification::right);
    
    setBorderSize (BorderSize<int> (0));
    
    setEditable (false);
}

void Spinner::setRange (int min, int max)
{
    this->min = min;
    this->max = max;
}

void Spinner::setText (int val)
{
    value = inRange (val);
    
    if (type == SpinnerType::NUMBER)
        Label::setText (String (value), sendNotification);
    else if (type == SpinnerType::NOTE)
    {
        Label::setText (getNote (value), sendNotification);
    }
    else
        Label::setText (".", sendNotification);
}

int Spinner::inRange (int val)
{
    if (val > max) return max;
    else if (val < min) return min;
    else return val;
}

void Spinner::mouseDown(const MouseEvent &event)
{
    if (type != SpinnerType::PERIOD) setColour (ColourIds::backgroundColourId, Colours::lightgrey);
    
    enabled = false;
    mousePoint.setY(event.y);
}

void Spinner::mouseDrag(const MouseEvent &event)
{
        int delta = mousePoint.getY() - event.y;
        int absDelta = abs(delta);
        if (!enabled && absDelta < 5) return;
        if (!enabled)
        {
            enabled = true;
            mousePoint.setY (event.y);
            return;
        }
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
        if (absDelta == 0) return;
        int val = value;
        for (int i = 0; i < absDelta; i++)
        {

            if (delta < 0) val -= 1;
            else val += 1;

            setText (val);
        }
        mousePoint.setY (event.y);
}

void Spinner::mouseDoubleClick (const MouseEvent &event)
{
    setColour (ColourIds::backgroundColourId, Colours::white);
    
    if (getParentComponent()) getParentComponent()->mouseDoubleClick (event);
}

void Spinner::mouseExit (const MouseEvent &event)
{
    setColour (ColourIds::backgroundColourId, Colours::white);
}

String Spinner::getNote (int value)
{
    switch (value) {
        case 0:
            return "C";
            break;
        case 1:
            return "C#";
            break;
        case 2:
            return "D";
            break;
        case 3:
            return "D#";
            break;
        case 4:
            return "E";
            break;
        case 5:
            return "F";
            break;
        case 6:
            return "F#";
            break;
        case 7:
            return "G";
            break;
        case 8:
            return "G#";
            break;
        case 9:
            return "A";
            break;
        case 10:
            return "A#";
            break;
        case 11:
            return "B";
            break;
            
        default:
            return "";
            break;
    }
}
