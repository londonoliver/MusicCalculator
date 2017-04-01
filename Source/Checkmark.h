//
//  Checkmark.h
//  MusicCalculator
//
//  Created by London Oliver on 3/31/17.
//
//

#ifndef Checkmark_h
#define Checkmark_h

#include "../JuceLibraryCode/JuceHeader.h"

class Checkmark : public Component
{
public:
    Colour colour;
    
    Checkmark();
    
    void paint (Graphics &g) override;
    
    void setColour (Colour c);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Checkmark)
};

#endif /* Checkmark_h */
