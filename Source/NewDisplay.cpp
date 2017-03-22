//
//  NewDisplay.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Tempo.cpp"
#include "ToggleTextButton.cpp"
#include "Fraction.cpp"

class NewDisplay : public Component
{
public:
    
    Tempo t;
    ToggleTextButton s;
    Fraction f;
    
    NewDisplay()
    {
        addAndMakeVisible (t);
        addAndMakeVisible (s);
        addAndMakeVisible (f);
    }
    
    ~NewDisplay()
    {
        
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha (0.0f));
        g.setColour(Colour (27, 30, 44));
        g.fillRoundedRectangle (getLocalBounds().toFloat(), 2.0f);
    }
    
    void resized() override
    {
        int width = getWidth();
        int height = getHeight();
        int twidth = width * (2.0/4.0);
        int swidth = width * (1.0/4.0);
        int dwidth = width * (1.0/4.0);
        
        t.setBounds(0, 0, twidth, height);
        s.setBounds(twidth, 0, swidth, height);
        f.setBounds (twidth + swidth, 0, dwidth, height);
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewDisplay)
};
