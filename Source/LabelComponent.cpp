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
    font = Font("Roboto", 50, Font::plain);
    setFont(font);
    setJustificationType(Justification::centred);
    addListener(this);
    setFormattedText(120, dontSendNotification);
    noteIndex = 0;
    octave = 3;
    setEditable(false, true, true);;
    setBorderSize(BorderSize<int> (0));
}

void LabelComponent::setFormattedText(double d, NotificationType notification)
{
    if (labelType == LabelType::BPM)    // bpm
        setText (formatBpm (d), notification);
    else if (labelType == LabelType::NOTENAME)  // note
        setText (getNoteNameString(noteIndex), notification);
    else                                            // octave
        setText (String(octave), notification);
}


Point<int> mousePoint;
bool enabled, draggable;
String oldText = "120.000";

// Overloaded from LabelListener - checks to make sure that new text is a valid BPM,
// and if not, reverts label to the previous text
void LabelComponent::labelTextChanged(Label* labelThatHasChanged)
{
    string s = getText().trim().toStdString();
    if (labelType == LabelType::BPM)    // bpm
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
    else if (labelType == LabelType::NOTENAME)     // note name
    {
        regex r ("^(c|(c#)|(cb)|d|(d#)|(db)|e|f|(f#)|(fb)|g|(g#)|(gb)|a|(a#)|(ab)|b|(b#)|(bb)|C|(C#)|(Cb)|D|(D#)|(Db)|E|F|(F#)|(Fb)|G|(G#)|(Gb)|A|(A#)|(Ab)|B|(B#)|(Bb))$");
        if (regex_match (s, r))
        {
            noteIndex = noteToIndex(s);
            setText(getNoteNameString(noteIndex), sendNotification);
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
            octave = getTextValue().getValue();
            setText(String(octave), sendNotification);
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
        /*bool ctrlDown = event.mods.isCtrlDown();
        if (ctrlDown)
        {
            double value = getTextValue().getValue();
            value = floor(value);
            setText(formatBpm(value), sendNotification);
        }*/
        
        enabled = false;
        mousePoint.setY(event.y);
    }
}

void LabelComponent::mouseUp(const juce::MouseEvent &event)
{
    bool ctrlDown = event.mods.isCtrlDown();
    if (ctrlDown)
    {
        double value = getTextValue().getValue();
        value = floor(value);
        setText(formatBpm(value), sendNotification);
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
            if (ctrlDown && (labelType == LabelType::BPM))  // bpm
            {
                if(delta < 0.0) value -= 0.01;
                else value += 0.01;
            }
            else
            {
                if (labelType == LabelType::BPM)    // bpm
                {
                    if(delta < 0.0) value -= 1.0;
                    else value += 1.0;
                }
                else if (labelType == LabelType::NOTENAME)   // note name
                {
                    if(delta < 0.0) noteIndex -= 1.0;
                    else noteIndex += 1.0;
                    
                    if (noteIndex > 11.0)
                        noteIndex = 11.0;
                    else if (noteIndex < 0.0)
                        noteIndex = 0.0;
                }
                else                                    // note number
                {
                    if(delta < 0.0) octave -= 1.0;
                    else octave += 1.0;
                    
                    if (octave > 8.0)
                        octave = 8.0;
                    else if (octave < 0.0)
                        octave = 0.0;
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
    /*if (d > 990.0) d = 990.0;
    else if (d < 5.0) d = 5.0;
    stringstream ss;
    ss << fixed << setprecision(3) << d;
    return ss.str();*/
    return String (d);
}

void LabelComponent::setLabelType (LabelType type)
{
    labelType = type;
    setFormattedText(1, sendNotification);
}

LabelComponent::LabelType LabelComponent::getLabelType()
{
    return labelType;
}

int LabelComponent::getNote()
{
    return noteIndex;
}

void LabelComponent::setNote (int i)
{
    noteIndex = i;
    setFormattedText(note, sendNotification);
}

int LabelComponent::getOctave()
{
    return octave;
}

void LabelComponent::setOctave (int i)
{
    octave = i;
    setFormattedText(octave, sendNotification);
}

int LabelComponent::getNoteIndex()
{
    return noteIndex;
}

Font LabelComponent::getFont()
{
    return font;
}

String LabelComponent::getNoteNameString (int i)
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

int LabelComponent::noteToIndex (String s)
{
    if (s == "C" || s == "c")
        return 0;
    else if (s == "C#" || s == "c#" || s == "Db" || s == "db")
        return 1;
    else if (s == "D" || s == "d")
        return 2;
    else if (s == "D#" || s == "d#" || s == "Eb" || s == "eb")
        return 3;
    else if (s == "E" || s == "e" || s == "Fb" || s == "fb")
        return 4;
    else if (s == "F" || s == "f")
        return 5;
    else if (s == "F#" || s == "f#" || s == "Gb" || s == "gb")
        return 6;
    else if (s == "G" || s == "g")
        return 7;
    else if (s == "G#" || s == "g#" || s == "Ab" || s == "ab")
        return 8;
    else if (s == "A" || s == "a")
        return 9;
    else if (s == "A#" || s == "a#" || s == "Bb" || s == "bb")
        return 10;
    else if (s == "B" || s == "b" || s == "Cb" || s == "cb")
        return 11;
    else
        return -1;
}
