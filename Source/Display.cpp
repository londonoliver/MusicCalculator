//
//  Display.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/19/17.
//
//

#include "Display.h"
#include <regex>

using namespace std;
    
    
    
Display::Display() :    t1 {Spinner::SpinnerType::NUMBER, 5, 990},
                        t2 {Spinner::SpinnerType::PERIOD, 0, 0},
                        t3 {Spinner::SpinnerType::NUMBER, 0, 9},
                        t4 {Spinner::SpinnerType::NUMBER, 0, 9},
                        t5 {Spinner::SpinnerType::NUMBER, 0, 9},
                        t6 {Spinner::SpinnerType::NUMBER, 0, 9},

                        n1 {Spinner::SpinnerType::NOTE, 0, 11},
                        n2 {Spinner::SpinnerType::NUMBER, 0, 8},

                        h1 {Spinner::SpinnerType::NUMBER, 0, 20000},
                        h2 {Spinner::SpinnerType::PERIOD, 0, 0},
                        h3 {Spinner::SpinnerType::NUMBER, 0, 9},
                        h4 {Spinner::SpinnerType::NUMBER, 0, 9}
{
    font = Font ("Roboto", 50, Font::plain);
    
    /*t1.setText (120);*/
    t2.Label::setText (".", sendNotification);
    /*t3.setText (0);
    t4.setText (0);
    t5.setText (0);
    t6.setText (0);
    
    n1.setText (0);
    n2.setText (3);
    
    h1.setText (440);
    h2.Label::setText (".", sendNotification);
    h3.setText (0);
    h4.setText (0);*/
    
    fitBounds();
    
    addAndMakeVisible (t1);
    addAndMakeVisible (t2);
    addAndMakeVisible (t3);
    addAndMakeVisible (t4);
    addAndMakeVisible (t5);
    addAndMakeVisible (t6);
    
    addAndMakeVisible (n1);
    addAndMakeVisible (n2);
    
    addAndMakeVisible (h1);
    addAndMakeVisible (h2);
    addAndMakeVisible (h3);
    addAndMakeVisible (h4);
    
    attachListener (this);
    
    setDisplayType (DisplayType::TEMPO);
    
    setSpinnersVisible (true);
    
    ed.setFont (font);
    ed.setBorderSize (BorderSize<int> (0));
    addAndMakeVisible (ed);
    ed.setVisible (false);
    ed.addListener(this);
}




String Display::toString (DisplayType displayType)
{
    return  (displayType == DisplayType::TEMPO)     ?       t1.getTextValue().toString() +
                                                            "." +
                                                            t3.getTextValue().toString() +
                                                            t4.getTextValue().toString() +
                                                            t5.getTextValue().toString() +
                                                            t6.getTextValue().toString()
    
                                                    :
    
            ((displayType == DisplayType::NOTE)     ?       n1.getTextValue().toString() +
                                                            n2.getTextValue().toString()
               
                                                    :
    
                                                            h1.getTextValue().toString() +
                                                            "." +
                                                            h3.getTextValue().toString() +
                                                            h4.getTextValue().toString());
}




double Display::getTempo()
{
    return  (double) t1.getTextValue().getValue()           +
            (double) t3.getTextValue().getValue() * 0.1     +
            (double) t4.getTextValue().getValue() * 0.01    +
            (double) t5.getTextValue().getValue() * 0.001   +
            (double) t6.getTextValue().getValue() * 0.0001;
}





int Display::getNote()
{
    return n1.value;
}




int Display::getOctave()
{
    return n2.value;
}




double Display::getHertz()
{
    return  (double) h1.getTextValue().getValue()           +
            (double) h3.getTextValue().getValue() * 0.1     +
            (double) h4.getTextValue().getValue() * 0.01;
}




void Display::fitBounds()
{
    t1Width = font.getStringWidth (t1.getTextValue().toString());
    t2Width = font.getStringWidth (t2.getTextValue().toString());
    t3Width = font.getStringWidth (t3.getTextValue().toString());
    t4Width = font.getStringWidth (t4.getTextValue().toString());
    t5Width = font.getStringWidth (t5.getTextValue().toString());
    t6Width = font.getStringWidth (t6.getTextValue().toString());
    
    n1Width = font.getStringWidth (n1.getTextValue().toString());
    n2Width = font.getStringWidth (n2.getTextValue().toString());
    
    h1Width = font.getStringWidth (h1.getTextValue().toString());
    h2Width = font.getStringWidth (h2.getTextValue().toString());
    h3Width = font.getStringWidth (h3.getTextValue().toString());
    h4Width = font.getStringWidth (h4.getTextValue().toString());
    
    height = font.getHeight();
    width = (displayType == DisplayType::TEMPO)     ?       t1Width +
                                                            t2Width +
                                                            t3Width +
                                                            t4Width +
                                                            t5Width +
                                                            t6Width
    
                                                    :
    
            ((displayType == DisplayType::NOTE)     ?       n1Width +
                                                            n2Width
             
                                                    :
             
                                                            h1Width +
                                                            h2Width +
                                                            h3Width +
                                                            h4Width);
    
    setBounds       (0                                                  , 0,    width,      height);
    
    t1.setBounds    (0                                                  , 0,    t1Width,    height);
    t2.setBounds    (t1Width                                            , 0,    t2Width,    height);
    t3.setBounds    (t1Width + t2Width                                  , 0,    t3Width,    height);
    t4.setBounds    (t1Width + t2Width + t3Width                        , 0,    t4Width,    height);
    t5.setBounds    (t1Width + t2Width + t3Width + t4Width              , 0,    t5Width,    height);
    t6.setBounds    (t1Width + t2Width + t3Width + t4Width + t5Width    , 0,    t6Width,    height);
    
    n1.setBounds    (0                                                  , 0,    n1Width,    height);
    n2.setBounds    (n1Width                                            , 0,    n2Width,    height);
    
    h1.setBounds    (0                                                  , 0,    h1Width,    height);
    h2.setBounds    (h1Width                                            , 0,    h2Width,    height);
    h3.setBounds    (h1Width + h2Width                                  , 0,    h3Width,    height);
    h4.setBounds    (h1Width + h2Width + h3Width                        , 0,    h4Width,    height);
    
    ed.setBounds    (0                                                  , 0,    width,      height);
}




void Display::setDisplay (String val, DisplayType displayType)
{
        int len = val.length();
        
        int i = 0;
    
        if (displayType == DisplayType::TEMPO)
        {
                while (i < len && val[i] != '.') i++;
                
                int i1 = stoi (val.substring (0, i).toStdString());
                
                if (i1 >= t1.min)
                {
                    t1.setText (i1);
                    t3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                    t4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                    t5.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                    t6.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                }
        }
        else if (displayType == DisplayType::NOTE)
        {
                String str1;
                String str2;
                
                str2 = val.substring(len - 1, len);

                if (regex_match (str2.toStdString(), regex ("^[0-8]$")))
                {
                    str1 = val.substring(0, len - 1);
                    if (noteIndex(str1) != -1)
                    {
                        n1.setText(noteIndex (str1));
                        n2.setText (stoi (str2.toStdString()));
                    }
                }
                else
                {
                    str1 = val.substring(0, len);
                    if (noteIndex (str1) != -1)
                        n1.setText(noteIndex (str1));
                }
        }
        else
        {
                while (i < len && val[i] != '.') i++;

                h1.setText ((i != 0) ? stoi (val.substring (0, i).toStdString()) : 0);
                h3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                h4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
        }

}




void Display::attachListener(Label::Listener *listener)
{
    t1.addListener (listener);
    t2.addListener (listener);
    t3.addListener (listener);
    t4.addListener (listener);
    t5.addListener (listener);
    t6.addListener (listener);
    
    n1.addListener (listener);
    n2.addListener (listener);
    
    h1.addListener (listener);
    h2.addListener (listener);
    h3.addListener (listener);
    h4.addListener (listener);
}

void Display::removeListeners(Label::Listener *listener)
{
    t1.removeListener (listener);
    t2.removeListener (listener);
    t3.removeListener (listener);
    t4.removeListener (listener);
    t5.removeListener (listener);
    t6.removeListener (listener);
    
    n1.removeListener (listener);
    n2.removeListener (listener);
    
    h1.removeListener (listener);
    h2.removeListener (listener);
    h3.removeListener (listener);
    h4.removeListener (listener);
}




void Display::setDisplayType (DisplayType displayType)
{
    this->displayType = displayType;
    
    setSpinnersVisible (true);
    
    resized();
}




void Display::resized()
{
    fitBounds();
    
    if (getParentComponent())
        getParentComponent()->resized();
}




void Display::mouseDoubleClick (const MouseEvent &e)
{
    if (displayType == DisplayType::TEMPO && tempoSync)
        return;
    
    setSpinnersVisible (false);
    
    ed.setVisible (true);
    
    ed.setText (toString (displayType), sendNotification);
    
    ed.showEditor();
}



void Display::setSpinnersVisible (bool visible)
{
    t1.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
    t2.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
    t3.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
    t4.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
    t5.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
    t6.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
    
    n1.setVisible ((displayType == DisplayType::NOTE)   ?   visible : false);
    n2.setVisible ((displayType == DisplayType::NOTE)   ?   visible : false);
    
    h1.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
    h2.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
    h3.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
    h4.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
}




void Display::setSpinnersEnabled (bool enabled)
{
    t1.setVisible ((displayType == DisplayType::TEMPO)  ?   enabled : false);
    t2.setVisible ((displayType == DisplayType::TEMPO)  ?   enabled : false);
    t3.setVisible ((displayType == DisplayType::TEMPO)  ?   enabled : false);
    t4.setVisible ((displayType == DisplayType::TEMPO)  ?   enabled : false);
    t5.setVisible ((displayType == DisplayType::TEMPO)  ?   enabled : false);
    t6.setVisible ((displayType == DisplayType::TEMPO)  ?   enabled : false);
    
    n1.setVisible ((displayType == DisplayType::NOTE)   ?   enabled : false);
    n2.setVisible ((displayType == DisplayType::NOTE)   ?   enabled : false);
    
    h1.setVisible ((displayType == DisplayType::HERTZ)  ?   enabled : false);
    h2.setVisible ((displayType == DisplayType::HERTZ)  ?   enabled : false);
    h3.setVisible ((displayType == DisplayType::HERTZ)  ?   enabled : false);
    h4.setVisible ((displayType == DisplayType::HERTZ)  ?   enabled : false);
}

void Display::setTempoSync (bool sync)
{
    tempoSync = sync;

    t1.setColour (Label::ColourIds::textColourId, (tempoSync) ? Colours::grey : Colours:: black);
    t2.setColour (Label::ColourIds::textColourId, (tempoSync) ? Colours::grey : Colours:: black);
    t3.setColour (Label::ColourIds::textColourId, (tempoSync) ? Colours::grey : Colours:: black);
    t4.setColour (Label::ColourIds::textColourId, (tempoSync) ? Colours::grey : Colours:: black);
    t5.setColour (Label::ColourIds::textColourId, (tempoSync) ? Colours::grey : Colours:: black);
    t6.setColour (Label::ColourIds::textColourId, (tempoSync) ? Colours::grey : Colours:: black);
    
    t1.setBgColorClicked((tempoSync) ? Colours::white : Colours::lightgrey);
    t3.setBgColorClicked((tempoSync) ? Colours::white : Colours::lightgrey);
    t4.setBgColorClicked((tempoSync) ? Colours::white : Colours::lightgrey);
    t5.setBgColorClicked((tempoSync) ? Colours::white : Colours::lightgrey);
    t6.setBgColorClicked((tempoSync) ? Colours::white : Colours::lightgrey);
    
    t1.setDraggable ((tempoSync) ? false : true);
    t3.setDraggable ((tempoSync) ? false : true);
    t4.setDraggable ((tempoSync) ? false : true);
    t5.setDraggable ((tempoSync) ? false : true);
    t6.setDraggable ((tempoSync) ? false : true);
}

void Display::setMidiSync (bool sync)
{
    midiSync = sync;
}




void Display::editorHidden (Label *label, TextEditor &editor)
{
    ed.setVisible (false);
    
    setSpinnersVisible (true);
    
    String val = ed.getTextValue().toString().trim();
    
    
    if (displayType == DisplayType::TEMPO)
    {
        if (regex_match (val.toStdString(), regex ("(\\d+)((\\.)(\\d*)?)?")))
            setDisplay (val, displayType);
    }
    else if (displayType == DisplayType::NOTE)
    {
        setDisplay (val, displayType);
    }
    else
    {
        if (regex_match (val.toStdString(), regex ("(\\d*)((\\.)(\\d*)?)?")))
            setDisplay (val, displayType);
    }
}




void Display::labelTextChanged (Label *labelThatHasChanged)
{
    resized();
}




void Display::editorShown (Label *, TextEditor &)
{
}




int Display::noteIndex (String val)
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
