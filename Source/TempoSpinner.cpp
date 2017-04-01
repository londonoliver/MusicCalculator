//
//  Spinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/15/17.
//
//
#include "TempoSpinner.h"
#include <iostream>
#include <regex>

using namespace std;

TempoSpinner::TempoSpinner() :  s1 {Spinner::SpinnerType::NUMBER, 5, 990},
                                s2 {Spinner::SpinnerType::PERIOD, 0, 0},
                                s3 {Spinner::SpinnerType::NUMBER, 0, 9},
                                s4 {Spinner::SpinnerType::NUMBER, 0, 9},
                                s5 {Spinner::SpinnerType::NUMBER, 0, 9},
                                s6 {Spinner::SpinnerType::NUMBER, 0, 9}
{
    f = s1.getFont().getTypefaceName();
    font = Font (f, 50, Font::plain);
    
    s1.setText (120, dontSendNotification);
    s2.Label::setText (".", dontSendNotification);
    s3.setText (0, dontSendNotification);
    s4.setText (0, dontSendNotification);
    s5.setText (0, dontSendNotification);
    s6.setText (0, dontSendNotification);
    
    addAndMakeVisible (s1);
    addAndMakeVisible (s2);
    addAndMakeVisible (s3);
    addAndMakeVisible (s4);
    addAndMakeVisible (s5);
    addAndMakeVisible (s6);
    
    attachListener (this);
    
    ed.setFont (font);
    ed.setBorderSize (BorderSize<int> (0));
    addAndMakeVisible (ed);
    ed.setVisible (false);
    ed.addListener (this);
    ed.setLookAndFeel (this);
    ed.setColour (TextEditor::ColourIds::focusedOutlineColourId, Colours::white.withAlpha(0.0f));
    ed.setColour (TextEditor::ColourIds::highlightColourId, Colours::white.withAlpha(0.5f));
}

TempoSpinner::~TempoSpinner()
{
    detachListener (this);
    //ed.removeListener (this);
}
String TempoSpinner::toString()
{
    return s1.getTextValue().toString() + "." + s3.getTextValue().toString() + s4.getTextValue().toString() + s5.getTextValue().toString() + s6.getTextValue().toString();
}

double TempoSpinner::getValue()
{
    return (double) s1.getTextValue().getValue() +
            (double) s3.getTextValue().getValue() * 0.1 +
            (double) s4.getTextValue().getValue() * 0.01 +
            (double) s5.getTextValue().getValue() * 0.001 +
            (double) s6.getTextValue().getValue() * 0.0001;
    
}

void TempoSpinner::setSpinnersText (String val, NotificationType notification)
{
    int len = val.length();
    
    int i = 0;
    
    while (i < len && val[i] != '.') i++;
    
    int i1 = stoi (val.substring (0, i).toStdString());
    
    s1.setText (i1, notification);
    s3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0, notification);
    s4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0, notification);
    s5.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0, notification);
    s6.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0, notification);
}

void TempoSpinner::attachListener(Label::Listener *listener)
{
    s1.addListener (listener);
    s2.addListener (listener);
    s3.addListener (listener);
    s4.addListener (listener);
    s5.addListener (listener);
    s6.addListener (listener);
}

void TempoSpinner::detachListener(Label::Listener *listener)
{
    s1.removeListener (listener);
    s2.removeListener (listener);
    s3.removeListener (listener);
    s4.removeListener (listener);
    s5.removeListener (listener);
    s6.removeListener (listener);
}

void TempoSpinner::resized()
{
    s1Width = s1.getFont().getStringWidth (s1.getTextValue().toString());
    s2Width = s2.getFont().getStringWidth (s2.getTextValue().toString());
    s3Width = s3.getFont().getStringWidth (s3.getTextValue().toString());
    s4Width = s4.getFont().getStringWidth (s4.getTextValue().toString());
    s5Width = s5.getFont().getStringWidth (s5.getTextValue().toString());
    s6Width = s6.getFont().getStringWidth (s6.getTextValue().toString());
    
    int height = s1.getFont().getHeight();
    int width = s1Width + s2Width + s3Width + s4Width + s5Width + s6Width;
    width *= 1.1; // to make up for caret in editor
    
    s1.setBounds ((getWidth() - width)/2, 0, s1Width, height);
    s2.setBounds (s1.getX() + s1.getWidth(), 0, s2Width, height);
    s3.setBounds (s2.getX() + s2.getWidth(), 0, s3Width, height);
    s4.setBounds (s3.getX() + s3.getWidth(), 0, s4Width, height);
    s5.setBounds (s4.getX() + s4.getWidth(), 0, s5Width, height);
    s6.setBounds (s5.getX() + s5.getWidth(), 0, s6Width, height);
    
    if (ed.isBeingEdited())
    {
        int edWidth = ed.getCurrentTextEditor()->getFont().getStringWidth(ed.getCurrentTextEditor()->getText()) * 1.1;
        edWidth = jmax (edWidth, ed.getCurrentTextEditor()->getFont().getStringWidth("0"));
        ed.setBounds((getWidth() - edWidth)/2, 0, edWidth, height);
    }
    else
    {
        ed.setBounds((getWidth() - width)/2, 0, width, height);
    }
}

void TempoSpinner::mouseDoubleClick (const MouseEvent &e)
{
    if (isEnabled())
    {
        setSpinnersVisible (false);
        
        ed.setVisible (true);
        ed.setText (toString(), dontSendNotification);
        ed.showEditor();
    }
}

void TempoSpinner::mouseDown (const MouseEvent &e)
{
    if (e.mods.isCtrlDown() && isEnabled())
    {
        s3.setText(0, sendNotification);
        s4.setText(0, sendNotification);
        s5.setText(0, sendNotification);
        s6.setText(0, sendNotification);
    }
}

void TempoSpinner::setSpinnersVisible (bool visible)
{
    s1.setVisible(visible);
    s2.setVisible(visible);
    s3.setVisible(visible);
    s4.setVisible(visible);
    s5.setVisible(visible);
    s6.setVisible(visible);
}

void TempoSpinner::editorHidden (Label *label, TextEditor &editor)
{
    ed.setVisible (false);
    
    setSpinnersVisible (true);
    
    String val = ed.getTextValue().toString().trim();
    
    if (regex_match (val.toStdString(), regex ("(\\d+)((\\.)(\\d*)?)?")))
    {
        setSpinnersText (val, sendNotification);
    }
    
    editor.removeListener (this);
}

void TempoSpinner::labelTextChanged (Label *labelThatHasChanged)
{
    resized();
}

void TempoSpinner::editorShown (Label *, TextEditor &editor)
{
    editor.addListener (this);
    editor.setBorder (BorderSize<int> (0));
    editor.setInputRestrictions(8, "1234567890.");
}

void TempoSpinner::textEditorTextChanged (TextEditor &editor)
{
    resized();
}

void TempoSpinner::setFontHeight (float fontHeight)
{    
    s1.setFont (Font (fontHeight));
    s2.setFont (Font (fontHeight));
    s3.setFont (Font (fontHeight));
    s4.setFont (Font (fontHeight));
    s5.setFont (Font (fontHeight));
    s6.setFont (Font (fontHeight));
    
    ed.setFont (Font (fontHeight));
    
    resized();
}

void TempoSpinner::setBackgroundColour (Colour colour)
{
    s1.setBgColour (colour);
    s2.setBgColour (colour);
    s3.setBgColour (colour);
    s4.setBgColour (colour);
    s5.setBgColour (colour);
    s6.setBgColour (colour);
    
    ed.setColour(Label::ColourIds::backgroundWhenEditingColourId, colour);
}

void TempoSpinner::setTextColour (Colour colour)
{
    s1.setColour (Label::ColourIds::textColourId, colour);
    s2.setColour (Label::ColourIds::textColourId, colour);
    s3.setColour (Label::ColourIds::textColourId, colour);
    s4.setColour (Label::ColourIds::textColourId, colour);
    s5.setColour (Label::ColourIds::textColourId, colour);
    s6.setColour (Label::ColourIds::textColourId, colour);
    
    ed.setColour (Label::ColourIds::textWhenEditingColourId, colour);
    ed.setColour (CaretComponent::ColourIds::caretColourId, colour);
}
