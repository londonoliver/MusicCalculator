//
//  Note.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/20/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteSpinner.h"

class Note : public Component
{
public:
    NoteSpinner ns;
    
    Note()
    {
        addAndMakeVisible (ns);
        ns.setTextColour (Colour (177, 202, 225));
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha (0.0f));
    }
    
    void resized() override
    {
        ns.setFontHeight (getHeight()/2);
        ns.setBounds ((getWidth() - ns.width)/2, (getHeight() - ns.height)/2, ns.getWidth(), ns.getHeight());
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Note)
};
