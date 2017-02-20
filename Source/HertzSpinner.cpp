//
//  HertzSpinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/16/17.
//
//

#include "HertzSpinner.h"
#include <iostream>
#include <regex>

using namespace std;

HertzSpinner::HertzSpinner()  :   s1 {Spinner::SpinnerType::NUMBER, 0, 20000},
                    s2 {Spinner::SpinnerType::PERIOD, 0, 0},
                    s3 {Spinner::SpinnerType::NUMBER, 0, 9},
                    s4 {Spinner::SpinnerType::NUMBER, 0, 9}
{
    font = Font ("Roboto", 50, Font::plain);
    
    s1.setText (440);
    s2.Label::setText (".", sendNotification);
    s3.setText (0);
    s4.setText (0);
    
    fitBounds();
    
    addAndMakeVisible (s1);
    addAndMakeVisible (s2);
    addAndMakeVisible (s3);
    addAndMakeVisible (s4);
    
    attachListener (this);
    
    ed.setFont (font);
    ed.setBorderSize (BorderSize<int> (0));
    addAndMakeVisible (ed);
    ed.setVisible (false);
    ed.addListener (this);
}

String HertzSpinner::toString()
{
    return s1.getTextValue().toString() + "." + s3.getTextValue().toString() + s4.getTextValue().toString();
}

void HertzSpinner::fitBounds()
{
    s1Width = font.getStringWidth (s1.getTextValue().toString());
    s2Width = font.getStringWidth (s2.getTextValue().toString());
    s3Width = font.getStringWidth (s3.getTextValue().toString());
    s4Width = font.getStringWidth (s4.getTextValue().toString());
    
    height = font.getHeight();
    width = s1Width + s2Width + s3Width + s4Width;
    
    Component::setBounds (0, 0, width, height);
    
    s1.setBounds (0, 0, s1Width, height);
    s2.setBounds (s1Width, 0, s2Width, height);
    s3.setBounds (s1Width + s2Width, 0, s3Width, height);
    s4.setBounds (s1Width + s2Width + s3Width, 0, s4Width, height);
    
    ed.setBounds (0, 0, width, height);
}

void HertzSpinner::setSpinnersText (String val)
{
    int len = val.length();
    
    int i = 0;
    
    while (i < len && val[i] != '.') i++;
    
    s1.setText ((i != 0) ? stoi (val.substring (0, i).toStdString()) : 0);
    s3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
    s4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
}

void HertzSpinner::attachListener(Label::Listener *listener)
{
    s1.addListener (listener);
    s2.addListener (listener);
    s3.addListener (listener);
    s4.addListener (listener);
}

void HertzSpinner::resized()
{
    fitBounds();
    
    /*if (getParentComponent())
        getParentComponent()->resized();*/
}

void HertzSpinner::mouseDoubleClick (const MouseEvent &e)
{
    setSpinnersVisible (false);
    
    ed.setVisible (true);
    
    ed.setText (toString(), sendNotification);
    
    ed.showEditor();
}

void HertzSpinner::setSpinnersVisible (bool visible)
{
    s1.setVisible(visible);
    s2.setVisible(visible);
    s3.setVisible(visible);
    s4.setVisible(visible);
}

void HertzSpinner::editorHidden (Label *label, TextEditor &editor)
{
    ed.setVisible (false);
    
    setSpinnersVisible (true);
    
    String val = ed.getTextValue().toString().trim();
    
    if (regex_match (val.toStdString(), regex ("(\\d*)((\\.)(\\d*)?)?")))
        setSpinnersText (val);
}

void HertzSpinner::labelTextChanged (Label *labelThatHasChanged)
{
    resized();
}

void HertzSpinner::editorShown (Label *, TextEditor &)
{
}
