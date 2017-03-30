//
//  NoteSpinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/16/17.
//
//

#include "NoteSpinner.h"
#include <iostream>
#include <regex>

using namespace std;

NoteSpinner::NoteSpinner()  :   s1 {Spinner::SpinnerType::NOTE, 0, 11},
                                s2 {Spinner::SpinnerType::NUMBER, 0, 8}
{
    font = Font ("Roboto", 50, Font::plain);
    
    s1.setText (0, dontSendNotification);
    s2.setText (3, dontSendNotification);
    
    addAndMakeVisible (s1);
    addAndMakeVisible (s2);
    
    attachListener (this);
    
    ed.setFont (font);
    ed.setBorderSize (BorderSize<int> (0));
    addAndMakeVisible (ed);
    ed.setVisible (false);
    ed.addListener (this);
    ed.setColour (TextEditor::ColourIds::focusedOutlineColourId, Colours::white.withAlpha(0.0f));
    ed.setColour (TextEditor::ColourIds::highlightColourId, Colours::white.withAlpha(0.5f));
}

NoteSpinner::~NoteSpinner()
{
    detachListener (this);
    ed.removeListener (this);
}

String NoteSpinner::toString()
{
    return s1.getTextValue().toString() + s2.getTextValue().toString();
}

void NoteSpinner::setSpinnersText (String val, NotificationType notification)
{
    int len = val.length();
    
    String str1;
    String str2;
    
    str2 = val.substring (len - 1, len);
    if (regex_match (str2.toStdString(), regex ("^[0-8]$")))
    {
        str1 = val.substring(0, len - 1);
        if (noteIndex(str1) != -1)
        {
            s1.setText (noteIndex (str1), notification);
            s2.setText (stoi (str2.toStdString()), notification);
        }
    }
    else
    {
        str1 = val.substring(0, len);
        if (noteIndex (str1) != -1)
            s1.setText (noteIndex (str1), notification);
    }
}

void NoteSpinner::attachListener(Label::Listener *listener)
{
    s1.addListener (listener);
    s2.addListener (listener);
}

void NoteSpinner::detachListener(Label::Listener *listener)
{
    s1.removeListener (listener);
    s2.removeListener (listener);
}

void NoteSpinner::resized()
{
    s1Width = font.getStringWidth (s1.getTextValue().toString());
    s2Width = font.getStringWidth (s2.getTextValue().toString());
    
    height = font.getHeight();
    width = s1Width + s2Width;
    width *= 1.1; // to make up for caret in editor
    
    s1.setBounds (0, 0, s1Width, height);
    s2.setBounds (s1Width, 0, s2Width, height);
    
    ed.setBounds (0, 0, width, height);
}

void NoteSpinner::mouseDoubleClick (const MouseEvent &e)
{
    setSpinnersVisible (false);
    
    ed.setVisible (true);
    ed.setText (toString(), dontSendNotification);
    ed.showEditor();
}

void NoteSpinner::setSpinnersVisible (bool visible)
{
    s1.setVisible(visible);
    s2.setVisible(visible);
}

void NoteSpinner::editorHidden (Label *label, TextEditor &editor)
{
    ed.setVisible (false);
    
    setSpinnersVisible (true);
    
    setSpinnersText (ed.getTextValue().toString().trim(), sendNotification);
}

void NoteSpinner::labelTextChanged (Label *labelThatHasChanged)
{
    resized();
}

void NoteSpinner::editorShown (Label *l, TextEditor &ed)
{
}

bool NoteSpinner::isNumber (String val)
{
    return regex_match (val.toStdString(), regex ("^[0-9]$"));
}

int NoteSpinner::getNote()
{
    return noteIndex (s1.getTextValue().getValue());
}

void NoteSpinner::setNote (int note)
{
    s1.setText (note, sendNotification);
}

int NoteSpinner::getOctave()
{
    return s2.getTextValue().getValue();
}

void NoteSpinner::setOctave (int octave)
{
    s2.setText (octave, sendNotification);
}

int NoteSpinner::noteIndex (String val)
{
    if (val == "C" || val == "c")
        return 0;
    else if (val == "C#" || val == "c#" || val == "Db" || val == "db")
        return 1;
    else if (val == "D" || val == "d")
        return 2;
    else if (val == "D#" || val == "d#" || val == "Eb" || val == "eb")
        return 3;
    else if (val == "E" || val == "e" || val == "Fb" || val == "fb")
        return 4;
    else if (val == "F" || val == "f")
        return 5;
    else if (val == "F#" || val == "f#" || val == "Gb" || val == "gb")
        return 6;
    else if (val == "G" || val == "g")
        return 7;
    else if (val == "G#" || val == "g#" || val == "Ab" || val == "ab")
        return 8;
    else if (val == "A" || val == "a")
        return 9;
    else if (val == "A#" || val == "a#" || val == "Bb" || val == "bb")
        return 10;
    else if (val == "B" || val == "b" || val == "Cb" || val == "cb")
        return 11;
    else
        return -1;
}

void NoteSpinner::setFontHeight (float fontHeight)
{
    font.setHeight (fontHeight);
    
    s1.setFont (Font ("Roboto", fontHeight, Font::plain));
    s2.setFont (Font ("Roboto", fontHeight, Font::plain));
    
    ed.setFont (Font ("Roboto", fontHeight, Font::plain));
    
    resized();
}

void NoteSpinner::setTextColour (Colour colour)
{
    s1.setColour(Label::ColourIds::textColourId, colour);
    s2.setColour(Label::ColourIds::textColourId, colour);
    
    ed.setColour(Label::ColourIds::textWhenEditingColourId, colour);
}
