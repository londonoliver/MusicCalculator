//
//  Container.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/21/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Display.cpp"
#include "ButtonPanel.cpp"
#include "OutputPanel.cpp"
#include "ModeButtons.cpp"

class Container : public Component, public LabelListener
{
public:
    Display d;
    ButtonPanel p;
    OutputPanel o;
    ModeButtons m;
    
    Container()
    {
        addAndMakeVisible (d);
        addAndMakeVisible (p);
        addAndMakeVisible (o);
        addAndMakeVisible (m);
        
        d.ts.attachListener (this);
    }
    
    ~Container()
    {
        d.ts.detachListener (this);
    }
    
    void resized() override
    {
        int margin = (1.0/10.0) * getHeight();
        m.setBounds(0, 0, 100, 50);
        d.setBounds(0, 50 + margin, getWidth(), getHeight()/7);
        p.setBounds(0, d.getY() + d.getHeight() + margin, getWidth(), getHeight()/5);
        o.setBounds(0, p.getY() + p.getHeight() + margin, getWidth(), getHeight()/5);
    }
    
private:
    void labelTextChanged (Label *label) override
    {
        int bpm = d.ts.getValue();
        
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Container)
};
