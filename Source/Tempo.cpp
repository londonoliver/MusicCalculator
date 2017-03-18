//
//  Tempo.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoSpinner.h"

class Tempo : public Component
{
public:
    TempoSpinner ts;
    Label l;
    
    Tempo()
    {
        addAndMakeVisible (ts);
        addAndMakeVisible(l);
        ts.setTextColour (Colour (177, 202, 225));
        
        l.setColour(Label::ColourIds::backgroundColourId, Colours::white.withAlpha(0.0f));
        l.setColour(Label::ColourIds::textColourId, Colour (57, 73, 94));
        l.setEditable(false);
        l.setText("TEMPO", dontSendNotification);
        l.setBorderSize(BorderSize<int> (0));
    }
    
    ~Tempo()
    {
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha(0.0f));
    }
    
    void resized() override
    {
        ts.setFontHeight(20.f);
        ts.setBounds((getWidth() - ts.width)/2, (getHeight() - ts.height)/2, ts.width, ts.height);
        int lwidth = l.getFont().getStringWidth(l.getText());
        l.setBounds((getWidth() - lwidth)/2, ts.getY() + ts.height, lwidth, l.getFont().getHeight());
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tempo)
};
