//
//  OutputPanel.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/21/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomTableCell.h"

class OutputPanel : public Component
{
public:
    CustomTableCell c;
    Label l;
    
    OutputPanel()
    {
        addAndMakeVisible (c);
        addAndMakeVisible (l);
        
        l.setText ("Conversion", dontSendNotification);
        l.setJustificationType (Justification::centred);
    }
    
    void resized() override
    {
        int oneFifthHeight = (1.0/5.0) * getHeight();
        int threeFifthsHeight = (3.0/5.0) * getHeight();
        int oneSixthWidth = (1.0/6.0) * getWidth();
        
        l.setBounds (0, 0, getWidth(), oneFifthHeight);
        c.setBounds (0, oneFifthHeight*2, getWidth(), threeFifthsHeight);
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputPanel)
};
