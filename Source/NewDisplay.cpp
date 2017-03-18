//
//  NewDisplay.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Tempo.cpp"
#include "Sync.cpp"

class NewDisplay : public Component
{
public:
    
    Tempo t;
    Sync s;
    
    NewDisplay()
    {
        addAndMakeVisible (t);
        addAndMakeVisible (s);
    }
    
    ~NewDisplay()
    {
        
    }
    
    void paint (Graphics &g)
    {
        g.fillAll (Colours::white.withAlpha (0.0f));
        g.setColour(Colour (27, 30, 44));
        g.fillRoundedRectangle (getLocalBounds().toFloat(), 2.0f);
    }
    
    void resized()
    {
        t.setBounds(0, 0, getWidth() * (3.0/5.0), getHeight());
        s.setBounds(getWidth() * (3.0/5.0), 0, getWidth() * (2.0/5.0), getHeight());
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewDisplay)
};
