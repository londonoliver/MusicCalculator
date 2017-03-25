//
//  ModeButtons.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"

class ModeButtons : public Component, private LookAndFeel_V3
{
public:
    ScopedPointer<DrawableButton> b1, b2;
    
    ModeButtons()
    {
        b1 = new DrawableButton ("Button 1", DrawableButton::ImageFitted);
        b1->setClickingTogglesState (true);
        b1->setLookAndFeel (this);
        b1->setButtonStyle (DrawableButton::ButtonStyle::ImageOnButtonBackground);
        b1->setConnectedEdges (Button::ConnectedOnRight);
        b1->setToggleState (true, dontSendNotification);
        b1->setRadioGroupId (1);
        
        b2 = new DrawableButton ("Button 2", DrawableButton::ImageFitted);
        b2->setClickingTogglesState (true);
        b2->setLookAndFeel (this);
        b2->setButtonStyle (DrawableButton::ButtonStyle::ImageOnButtonBackground);
        b2->setConnectedEdges (Button::ConnectedOnLeft);
        b2->setRadioGroupId (1);
        
        ScopedPointer<XmlElement> svg1 (XmlDocument::parse(BinaryData::metronome_svg));
        ScopedPointer<Drawable> normal1;
        ScopedPointer<Drawable> down1;
        
        ScopedPointer<XmlElement> svg2 (XmlDocument::parse(BinaryData::note_svg));
        ScopedPointer<Drawable> normal2;
        ScopedPointer<Drawable> down2;
        
        if (svg1 != nullptr)
        {
            normal1 = Drawable::createFromSVG (*svg1);
            normal1->replaceColour(Colours::black, Colours::red.darker());
            
            down1 = Drawable::createFromSVG (*svg1);
            down1->replaceColour(Colours::black, Colours::white);
            
            b1->setImages(normal1, nullptr, nullptr, nullptr, down1, nullptr, nullptr , nullptr);
        }
        
        if (svg2 != nullptr)
        {
            normal2 = Drawable::createFromSVG (*svg2);
            normal2->replaceColour(Colours::black, Colours::red.darker());
            
            down2 = Drawable::createFromSVG (*svg2);
            down2->replaceColour(Colours::black, Colours::white);
            
            b2->setImages(normal2, nullptr, nullptr, nullptr, down2, nullptr, nullptr , nullptr);
        }
        
        addAndMakeVisible (b1);
        addAndMakeVisible (b2);
    }
    
    void resized() override
    {
        b1->setBounds(getLocalBounds().removeFromLeft(getWidth()/2));
        b2->setBounds(getLocalBounds().removeFromRight(getWidth()/2 +1));
    }
    
private:
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        bool toggleState = button.getToggleState();
        
        g.setColour (toggleState ? Colours::red.darker() : Colours::white);
        
        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();
        
        const float width  = button.getWidth();
        const float height = button.getHeight();
        
        if (width > 0 && height > 0)
        {
            const float cornerSize = 4.0f;
            
            Path outline;
            outline.addRoundedRectangle (0.5f, 0.5f, width, height, cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));
            g.fillPath (outline);
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModeButtons)
};
