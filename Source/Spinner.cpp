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
    
    font = getFont();
    setFont (font);
    
    setJustificationType (Justification::right);
    
    setBorderSize (BorderSize<int> (0));
    
    setEditable (false);
    
    bgColour = Colours::white.withAlpha(0.0f);
    highlightColour = Colours::white.withAlpha(0.4f);
    setColour (Label::ColourIds::backgroundColourId, bgColour);
    
    draggable = true;
}

Spinner::Spinner (SpinnerType type, Array<int> a)
{
    this->type = type;
    this->arr = a;
    this->min = 0;
    this->max = a.size() - 1;
    
    font = getFont();
    setFont (font);
    
    setJustificationType (Justification::right);
    
    setBorderSize (BorderSize<int> (0));
    
    setEditable (false);
    
    bgColour = Colours::white.withAlpha(0.0f);
    highlightColour = Colours::white.withAlpha(0.4f);
    setColour (Label::ColourIds::backgroundColourId, bgColour);
    
    draggable = true;
}

void Spinner::resized()
{
    if (getParentComponent())
        getParentComponent()->resized();
}

void Spinner::setRange (int min, int max)
{
    this->min = min;
    this->max = max;
}

void Spinner::setText (int val, NotificationType notification)
{
    value = inRange (val);
    
    if (type == SpinnerType::NUMBER)
        Label::setText (String (value), notification);
    else if (type == SpinnerType::NOTE)
    {
        Label::setText (getNote (value), notification);
    }
    else if (type == SpinnerType::PERIOD)
    {
        Label::setText (".", notification);
    }
    else
    {
        Label::setText(String (arr [value]), notification);
    }
    
    resized();
    
}

int Spinner::inRange (int val)
{
    if (val > max) return max;
    else if (val < min) return min;
    else return val;
}

void Spinner::mouseDown(const MouseEvent &event)
{
    if (type != SpinnerType::PERIOD && isEnabled()) setColour (ColourIds::backgroundColourId, highlightColour);
    
    if (getParentComponent()) getParentComponent()->mouseDown (event);
    
    enabled = false;
    mousePoint.setY(event.y);
}

void Spinner::setBgColour (Colour colour)
{
    bgColour = colour;
    setColour(ColourIds::backgroundColourId, bgColour);
}

void Spinner::setHighlightColour (Colour colour)
{
    highlightColour = colour;
}

void Spinner::setDraggable (bool draggable)
{
    this->draggable = draggable;
}

void Spinner::mouseDrag(const MouseEvent &event)
{
    if (draggable && isEnabled())
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
        }
        setText (val, sendNotification);
        mousePoint.setY (event.y);
    }
}

void Spinner::mouseDoubleClick (const MouseEvent &event)
{
    setColour (ColourIds::backgroundColourId, bgColour);
    
    if (getParentComponent()) getParentComponent()->mouseDoubleClick (event);
}

void Spinner::mouseEnter (const MouseEvent &event)
{
    if (type != SpinnerType::PERIOD && isEnabled()) setColour (ColourIds::backgroundColourId, highlightColour);
}

void Spinner::mouseExit (const MouseEvent &event)
{
    setColour (ColourIds::backgroundColourId, bgColour);
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

void Spinner::setFontHeight (float fontHeight)
{
    font.setHeight (fontHeight);
}
