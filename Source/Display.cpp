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
    int width, height;
    TempoSpinner ts;
    NoteSpinner ns;
    Label l;
    
    Display()
    {
        addChildComponent (ts);
        addChildComponent (ns);
        addAndMakeVisible (l);
        l.setBorderSize (BorderSize<int> (0));
    }
    
    void resized() override
    {
        int lwidth = l.getFont().getStringWidth(l.getText());
        l.setBounds ((getWidth() - lwidth)/2, 0, lwidth, l.getFont().getHeight());
        ts.setBounds ((getWidth() - ts.width)/2, l.getHeight(), ts.getWidth(), ts.getHeight());
        ns.setBounds ((getWidth() - ns.width)/2, l.getHeight(), ns.getWidth(), ns.getHeight());
        height = ts.getX() + ts.getHeight();
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};
