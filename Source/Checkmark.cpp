//
//  Checkmark.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/28/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"

class Checkmark : public Component
{
public:
    Colour colour;
    
    Checkmark()
    {
    }
    
    void paint (Graphics &g) override
    {
        float w = getWidth();
        float h = getHeight() * 0.9;
        Path tick;
        tick.startNewSubPath (w/4, h/2);
        tick.lineTo (w/2, h);
        tick.lineTo (h, 0.0f);
        
        g.setColour (colour);
        g.strokePath (tick, PathStrokeType (w/10));
    }
    
    void setColour (Colour c)
    {
        this->colour = c;
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Checkmark)
};
