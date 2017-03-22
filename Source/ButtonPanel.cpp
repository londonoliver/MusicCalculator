//
//  ButtonPanel.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/21/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Fraction.cpp"
#include "ToggleTextButton.cpp"

class ButtonPanel : public Component
{
public:
    Fraction f;
    ToggleTextButton s;
    ToggleTextButton u;
    
    Label l1, l2, l3;
    
    ButtonPanel()
    {
        addAndMakeVisible (f);
        addAndMakeVisible (s);
        addAndMakeVisible (u);
        addAndMakeVisible (l1);
        addAndMakeVisible (l2);
        addAndMakeVisible (l3);
        
        s.setToggleText ("HOST", "MANUAL");
        u.setToggleText( "MS", "HZ");
        l1.setText ("Sync", dontSendNotification);
        l2.setText ("Fraction", dontSendNotification);
        l3.setText ("Units", dontSendNotification);
        l1.setJustificationType(Justification::centred);
        l2.setJustificationType(Justification::centred);
        l3.setJustificationType(Justification::centred);
    }
    
    void resized() override
    {
        int oneTwelvethWidth = (1.0/12.0) * getWidth();
        int oneSixthWidth = (1.0/6.0) * getWidth();
        int threeSixthsWidth = (3.0/6.0) * getWidth();
        int fiveSixthsWidth = (5.0/6.0) * getWidth();
        int oneFifthHeight = (1.0/5.0) * getHeight();
        int threeFifthsHeight = (3.0/5.0) * getHeight();
        
        l1.setBounds(oneSixthWidth - oneTwelvethWidth, 0, oneSixthWidth, oneFifthHeight);
        l2.setBounds(threeSixthsWidth - oneTwelvethWidth, 0, oneSixthWidth, oneFifthHeight);
        l3.setBounds(fiveSixthsWidth - oneTwelvethWidth, 0, oneSixthWidth, oneFifthHeight);
        s.setBounds(oneSixthWidth - oneTwelvethWidth, oneFifthHeight * 2, oneSixthWidth, threeFifthsHeight);
        f.setBounds(threeSixthsWidth - oneTwelvethWidth, oneFifthHeight * 2, oneSixthWidth, threeFifthsHeight);
        u.setBounds(fiveSixthsWidth - oneTwelvethWidth, oneFifthHeight * 2 , oneSixthWidth, threeFifthsHeight);
        
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonPanel)
};
