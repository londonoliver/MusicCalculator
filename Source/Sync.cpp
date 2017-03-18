//
//  Sync.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"

class Sync : public Component, private LookAndFeel_V3
{
public:
    Label b;
    Label l;
    
    Sync()
    {
        addAndMakeVisible(b);
        addAndMakeVisible(l);
        
        b.setText ("HOST", dontSendNotification);
        b.setColour(Label::ColourIds::backgroundColourId, Colours::white.withAlpha(0.0f));
        b.setColour(Label::ColourIds::textColourId, Colour (177, 202, 225));
        b.setBorderSize(BorderSize<int> (0));
        b.setEditable(false);
        //b.setLookAndFeel (this);
        
        l.setColour(Label::ColourIds::backgroundColourId, Colours::white.withAlpha(0.0f));
        l.setColour(Label::ColourIds::textColourId, Colour (57, 73, 94));
        l.setEditable(false);
        l.setText("SYNC", dontSendNotification);
        l.setBorderSize(BorderSize<int> (0));
    }
    
    ~Sync()
    {
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha(0.0f));
        g.setColour(Colour (57, 73, 94));
        g.drawLine(0, getY() + 2, 0, getHeight() - 2);
        g.drawLine(1, getY() + 2, 1, getHeight() - 2);
        g.drawLine(2, getY() + 2, 2, getHeight() - 2);
    }
    
    void resized() override
    {
        b.setFont(Font (20.0f));
        int bwidth = b.getFont().getStringWidth(b.getText());
        int bheight = b.getFont().getHeight();
        b.setBounds((getWidth() - bwidth)/2, (getHeight() - bheight)/2, bwidth, bheight);
        int lwidth = l.getFont().getStringWidth(l.getText());
        l.setBounds((getWidth() - lwidth)/2, b.getY() + b.getHeight(), lwidth, l.getFont().getHeight());
    }
    
private:
    void drawButtonBackground (Graphics &, Button &, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sync)
};
