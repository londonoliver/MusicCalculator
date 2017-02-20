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
    font = Font ("Roboto", 50, Font::plain);
    
    s1.setText (120);
    s2.Label::setText (".", sendNotification);
    s3.setText (0);
    s4.setText (0);
    s5.setText (0);
    s6.setText (0);
    
    fitBounds();
    
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
    ed.addListener(this);
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

void TempoSpinner::fitBounds()
{
    s1Width = font.getStringWidth (s1.getTextValue().toString());
    s2Width = font.getStringWidth (s2.getTextValue().toString());
    s3Width = font.getStringWidth (s3.getTextValue().toString());
    s4Width = font.getStringWidth (s4.getTextValue().toString());
    s5Width = font.getStringWidth (s5.getTextValue().toString());
    s6Width = font.getStringWidth (s6.getTextValue().toString());
    
    height = font.getHeight();
    width = s1Width + s2Width + s3Width + s4Width + s5Width + s6Width;
    
    Component::setBounds (0, 0, width, height);
    
    s1.setBounds (0, 0, s1Width, height);
    s2.setBounds (s1Width, 0, s2Width, height);
    s3.setBounds (s1Width + s2Width, 0, s3Width, height);
    s4.setBounds (s1Width + s2Width + s3Width, 0, s4Width, height);
    s5.setBounds (s1Width + s2Width + s3Width + s4Width, 0, s5Width, height);
    s6.setBounds (s1Width + s2Width + s3Width + s4Width + s5Width, 0, s6Width, height);
    
    ed.setBounds (0, 0, width, height);
}

void TempoSpinner::setSpinnersText (String val)
{
    int len = val.length();
    
    int i = 0;
    
    while (i < len && val[i] != '.') i++;
    
    int i1 = stoi (val.substring (0, i).toStdString());
    
    if (i1 >= 5)
    {
        s1.setText (i1);
        s3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
        s4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
        s5.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
        s6.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
    }
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

void TempoSpinner::resized()
{
    fitBounds();
    
    /*if (getParentComponent())
        getParentComponent()->resized();*/
}

void TempoSpinner::mouseDoubleClick (const MouseEvent &e)
{
    setSpinnersVisible (false);
    
    ed.setVisible (true);
    
    ed.setText (toString(), sendNotification);
    
    ed.showEditor();
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
        setSpinnersText (val);
}

void TempoSpinner::labelTextChanged (Label *labelThatHasChanged)
{
    resized();
}

void TempoSpinner::editorShown (Label *, TextEditor &)
{
}
