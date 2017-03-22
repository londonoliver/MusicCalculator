//
//  Display.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/21/17.
//
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoSpinner.h"
#include "NoteSpinner.h"

class Display : public Component
{
public:
    TempoSpinner ts;
    NoteSpinner ns;
    
    Display()
    {
        addAndMakeVisible (ts);
        addAndMakeVisible (ns);
        ns.setVisible (false);
    }
    
    void resized() override
    {
        ts.setBounds ((getWidth() - ts.width)/2, (getHeight() - ts.height)/2, ts.getWidth(), ts.getHeight());
        ns.setBounds ((getWidth() - ns.width)/2, (getHeight() - ns.height)/2, ns.getWidth(), ns.getHeight());
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};
