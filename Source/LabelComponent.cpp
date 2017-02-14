//
//  LabelComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/8/17.
//
//

#include "LabelComponent.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <string>

using namespace std;

LabelComponent::LabelComponent()
{
    setColour(ColourIds::backgroundWhenEditingColourId, Colours::lightblue);
    setFont(Font("Roboto", 50, Font::plain));
    setJustificationType(Justification::centred);
    addListener(this);
    setFormattedText(120, dontSendNotification);
    noteIndex = 0;
}

void LabelComponent::setFormattedText(double d, NotificationType notification)
{
    if (bpm)
        setText (formatBpm (d), notification);
    else if (noteValue)
        setText (getNoteName(noteIndex), notification);
    else
        setText (String(d), notification);
}


Point<int> mousePoint;
bool enabled, draggable;
String oldText = "120.000";

// Overloaded from LabelListener - checks to make sure that new text is a valid BPM,
// and if not, reverts label to the previous text
void LabelComponent::labelTextChanged(Label* labelThatHasChanged)
{
    string s = getText().trim().toStdString();
    if (bpm)    // bpm
    {
        regex r ("(\\d*)((\\.)(\\d*)?)?");
        if (regex_match (s, r))
        {
            double d = getTextValue().getValue();
            setFormattedText(d, sendNotification);
        }
        else
        {
            setText(oldText, sendNotification);
        }
    }
    else if (noteValue)     // note value
    {
        regex r ("^(c|(c#)|d|(d#)|e|f|(f#)|g|(g#)|a|(a#)|b|C|(C#)|D|(D#)|E|F|(F#)|G|(G#)|A|(A#)|B)$");
        if (regex_match (s, r))
        {
            setText(getNoteName(noteIndex), sendNotification);
        }
        else
        {
            setText(oldText, sendNotification);
        }
    }
    else   // noteNumber
    {
        regex r ("^[0-8]$");
        if (regex_match(s, r))
        {
            setText(String(s), sendNotification);
        }
        else
        {
            setText(oldText, sendNotification);
        }
    }
}

// Overloaded from LabelListener, saves current text in case we need to revert back to it.
void LabelComponent::editorShown(Label* lablel, TextEditor& editor)
{
    oldText = getText();
}

// Overloaded from LabelListener.
void LabelComponent::editorHidden(Label* label, TextEditor& editor)
{
}

void LabelComponent::mouseEnter(const juce::MouseEvent &event)
{
    if (isEnabled())
        setColour(ColourIds::backgroundColourId, Colours::lightblue);
}

void LabelComponent::mouseExit(const juce::MouseEvent &event)
{
    setColour(ColourIds::backgroundColourId, Colours::white);
}

void LabelComponent::mouseDown(const juce::MouseEvent &event)
{
    if (isEnabled())
    {
        bool ctrlDown = event.mods.isCtrlDown();
        if (ctrlDown)
        {
            double value = getTextValue().getValue();
            value = floor(value);
            setText(formatBpm(value), sendNotification);
        }
        
        enabled = false;
        mousePoint.setY(event.y);
    }
}

void LabelComponent::mouseDrag(const juce::MouseEvent &event)
{
    if (isEnabled())
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
            if (ctrlDown && bpm)
            {
                if(delta < 0.0) value -= 0.01;
                else value += 0.01;
            }
            else
            {
                if(delta < 0.0) value -= 1.0;
                else value += 1.0;
                
                if (noteValue)
                {
                    noteIndex += value;
                    if (noteIndex > 11.0)
                        noteIndex = 11.0;
                    else if (noteIndex < 0.0)
                        noteIndex = 0.0;
                }
                else if (noteNumber)
                {
                    if (value > 8.0)
                        value = 8.0;
                    else if (value < 0.0)
                        value = 0.0;
                }
            }
            setFormattedText(value, sendNotification);
        }
        mousePoint.setY(event.y);
    }
}

// Returns a double in the range of 5.0 - 990.0 with a precision of two decimal places
String LabelComponent::formatBpm(double d)
{
    if (d > 990.0) d = 990.0;
    else if (d < 5.0) d = 5.0;
    stringstream ss;
    ss << fixed << setprecision(2) << d;
    return ss.str();
}

void LabelComponent::setType (int i)
{
    if (i == 1) // bpm
    {
        bpm = true;
        noteValue = false;
        noteNumber = false;
    }
    else if (i == 2)    // note value
    {
        bpm = false;
        noteValue = true;
        noteNumber = false;

    }
    else // note number
    {
        bpm = false;
        noteValue = false;
        noteNumber = true;

    }
}

String LabelComponent::getNoteName (int i)
{
    switch (i) {
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
