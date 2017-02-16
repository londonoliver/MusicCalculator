//
//  Spinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/15/17.
//
//

#ifndef Display_hpp
#define Display_hpp
#endif

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.cpp"
#include <iostream>

using namespace std;

class Display : public Component, private Label::Listener
{
public:
    int width;
    int height;
    
    Font font;
    
    Spinner s1 {Spinner::SpinnerType::NUMBER, 5, 990};
    Spinner s2 {Spinner::SpinnerType::PERIOD, 0, 0};
    Spinner s3 {Spinner::SpinnerType::NUMBER, 0, 9};
    Spinner s4 {Spinner::SpinnerType::NUMBER, 0, 9};
    Spinner s5 {Spinner::SpinnerType::NUMBER, 0, 9};
    Spinner s6 {Spinner::SpinnerType::NUMBER, 0, 9};
    
    
    Label d;
    
    int s1Width;
    int s2Width;
    int s3Width;
    int s4Width;
    int s5Width;
    int s6Width;

    
    Display()
    {
        font = Font ("Roboto", 50, Font::plain);
        
        s1.setText (120);
        s2.Label::setText (".", sendNotification);
        s3.setText (0);
        s4.setText (0);
        s5.setText (0);
        s6.setText (0);
        
        s1Width = font.getStringWidth ("120");
        s2Width = font.getStringWidth (".");
        s3Width = font.getStringWidth ("0");
        s4Width = font.getStringWidth ("0");
        s5Width = font.getStringWidth ("0");
        s6Width = font.getStringWidth ("0");
        
        height = font.getHeight();
        width = s1Width + s2Width + s3Width + s4Width + s5Width + s6Width;
        
        setBounds (0, 0, width, height);
        s1.setBounds (0, 0, s1Width, height);
        s2.setBounds (s1Width, 0, s2Width, height);
        s3.setBounds (s1Width + s2Width, 0, s3Width, height);
        s4.setBounds (s1Width + s2Width + s3Width, 0, s4Width, height);
        s5.setBounds (s1Width + s2Width + s3Width + s4Width, 0, s5Width, height);
        s6.setBounds (s1Width + s2Width + s3Width + s4Width + s5Width, 0, s6Width, height);
        
        
        addAndMakeVisible (s1);
        addAndMakeVisible (s2);
        addAndMakeVisible (s3);
        addAndMakeVisible (s4);
        addAndMakeVisible (s5);
        addAndMakeVisible (s6);
        
        
        d.setFont(font);
        d.setBorderSize(BorderSize<int> (0));
        d.setBounds (0, 0, width, height);
        addAndMakeVisible (d);
        d.setVisible (false);
        d.addListener(this);
    }
    
    String getBpmString()
    {
        return s1.getTextValue().toString() + "." + s3.getTextValue().toString() + s4.getTextValue().toString() + s5.getTextValue().toString() + s6.getTextValue().toString();
    }
    
private:
    void mouseDoubleClick (const MouseEvent &e) override
    {
        setSpinnersVisible (false);
        d.setVisible (true);
        d.setText (getBpmString(), sendNotification);
        d.showEditor();
    }
    
    void setSpinnersVisible (bool visible)
    {
        s1.setVisible(visible);
        s2.setVisible(visible);
        s3.setVisible(visible);
        s4.setVisible(visible);
        s5.setVisible(visible);
        s6.setVisible(visible);
    }
    
    void editorHidden (Label *label, TextEditor &editor) override
    {
        d.setVisible (false);
        setSpinnersVisible (true);
        setSpinnersText (d.getTextValue().toString());
    }
    
    void labelTextChanged (Label *labelThatHasChanged) override {}
    void editorShown (Label *, TextEditor &) override {}
    
    void setSpinnersText (String val)
    {
        val.trim();
        
        int len = val.length();
        
        String str1;
        String str3;
        String str4;
        String str5;
        String str6;
        
        int i = 0;
        
        while (i < len && val[i] != '.') i++;
        
        cout << "len = " << len << " i = " << i << " val[i] = " << val[i] << " val.substring(0, i-1) = " << val.substring (0, i - 1) << endl;
        
        
        
        str1 = val.substring (0, i);
        str3 = (++i < len) ? val.substring(i, i + 1) : "0";
        str4 = (++i < len) ? val.substring(i, i + 1) : "0";
        str5 = (++i < len) ? val.substring(i, i + 1) : "0";
        str6 = (++i < len) ? val.substring(i, i + 1) : "0";
        
        s1.Label::setText (str1, sendNotification);
        s3.Label::setText (str3, sendNotification);
        s4.Label::setText (str4, sendNotification);
        s5.Label::setText (str5, sendNotification);
        s6.Label::setText (str6, sendNotification);
        
    }
};
