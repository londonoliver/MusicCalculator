//
//  NoteDisplay.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/19/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Note.cpp"

class NoteDisplay : public Component
{
public:
    Note n;
    
    NoteDisplay()
    {
        addAndMakeVisible (n);
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
        int nwidth = width * (2.0/3.0);
        
        n.setBounds(0, 0, nwidth, height);
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteDisplay)
};
