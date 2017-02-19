//
//  HertzSpinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/16/17.
//
//

#ifndef HertzSpinner_hpp
#define HertzSpinner_hpp
#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.cpp"
#include <iostream>
#include <regex>
#endif



using namespace std;

class HertzSpinner : public Component, private LabelListener
{
public:
    int width;
    int height;
    
    Font font;
    
    Spinner s1 {Spinner::SpinnerType::NUMBER, 0, 20000};
    Spinner s2 {Spinner::SpinnerType::PERIOD, 0, 0};
    Spinner s3 {Spinner::SpinnerType::NUMBER, 0, 9};
    Spinner s4 {Spinner::SpinnerType::NUMBER, 0, 9};
    
    Label ed;
    
    int s1Width;
    int s2Width;
    int s3Width;
    int s4Width;
    
    HertzSpinner()
    {
        font = Font ("Roboto", 50, Font::plain);
        
        s1.setText (440);
        s2.Label::setText (".", sendNotification);
        s3.setText (0);
        s4.setText (0);
        
        setBounds();
        
        addAndMakeVisible (s1);
        addAndMakeVisible (s2);
        addAndMakeVisible (s3);
        addAndMakeVisible (s4);
        
        s1.addListener (this);
        s2.addListener (this);
        s3.addListener (this);
        s4.addListener (this);
        
        ed.setFont (font);
        ed.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (ed);
        ed.setVisible (false);
        ed.addListener(this);
    }
    
    String toString()
    {
        return s1.getTextValue().toString() + "." + s3.getTextValue().toString() + s4.getTextValue().toString();
    }
    
    void setBounds()
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
    
    void setSpinnersText (String val)
    {
        int len = val.length();
        
        int i = 0;
        
        while (i < len && val[i] != '.') i++;
        
        s1.setText ((i != 0) ? stoi (val.substring (0, i).toStdString()) : 0);
        s3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
        s4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
    }
    
    void resized() override
    {
        setBounds();
        
        if (getParentComponent())
            getParentComponent()->resized();
    }
    
private:
    void mouseDoubleClick (const MouseEvent &e) override
    {
        setSpinnersVisible (false);
        
        ed.setVisible (true);
        
        ed.setText (toString(), sendNotification);
        
        ed.showEditor();
    }
    
    void setSpinnersVisible (bool visible)
    {
        s1.setVisible(visible);
        s2.setVisible(visible);
        s3.setVisible(visible);
        s4.setVisible(visible);
    }
    
    void editorHidden (Label *label, TextEditor &editor) override
    {
        ed.setVisible (false);
        
        setSpinnersVisible (true);
        
        String val = ed.getTextValue().toString().trim();
        
        if (regex_match (val.toStdString(), regex ("(\\d*)((\\.)(\\d*)?)?")))
            setSpinnersText (val);
    }
    
    void labelTextChanged (Label *labelThatHasChanged) override
    {
        resized();
    }
    
    void editorShown (Label *, TextEditor &) override
    {
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HertzSpinner)
};
