//
//  NewDisplay.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "NewDisplay.cpp"
#include "ModeButtons.cpp"
//#include "Sync.cpp"

class Header : public Component
{
public:
    NewDisplay nd;
    ModeButtons mb;
   // Sync s;
    
    Header()
    {
        addAndMakeVisible (nd);
        addAndMakeVisible (mb);
        //addAndMakeVisible (s);
    }
    
    ~Header()
    {
        
    }
    
    void paint (Graphics &g)
    {
        /*ColourGradient gradient (Colour (188, 188, 188), 0.0f, 0.0f, Colour (143, 143, 143), 0.0f, getHeight(), false);
        g.setGradientFill(gradient);
        g.fillRect(getLocalBounds());*/
        g.fillAll(Colours::white.withAlpha(0.0f));
    }
    
    void resized()
    {
        mb.setBounds(10, (getHeight() - 30)/2, 60, 30);
        int ndwidth = 180;
        //nd.setBounds((getWidth() - ndwidth)/2, (getHeight() - 50)/2, ndwidth, 50);
        nd.setBounds(80, (getHeight() - 50)/2, ndwidth, 50);
       // s.setBounds(getWidth() - 60, (getHeight() - 50)/2, 50, 50);
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};