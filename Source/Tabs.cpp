//
//  Tabs.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/8/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoConversionComponent.h"
#include "NoteConversionComponent.h"

class Tabs : public Component
{
public:
    ScopedPointer<DrawableButton> b1;
    ScopedPointer<TempoConversionComponent> tcc;
    ScopedPointer<NoteConversionComponent> ncc;
    
    int width, height;
    
    Tabs()
    {
        b1 = new DrawableButton ("Tab1", DrawableButton::ImageFitted);
        addAndMakeVisible(b1);
        addAndMakeVisible(tcc);
        addAndMakeVisible(ncc);
        
        
        
        width = 300;
        height = 400;
        setSize(width, height);
    }
    
    void paint(Graphics &g)
    {
        ScopedPointer<XmlElement> svg (XmlDocument::parse(BinaryData::metronome_svg));
        ScopedPointer<Drawable> drawable;
        if (svg != nullptr)
        {
            g.setColour(Colours::black);
            drawable = Drawable::createFromSVG (*svg);
            b1->addAndMakeVisible(drawable);
        }
    }
    
    void resized()
    {
        if (getParentComponent())
        {
        int width = getParentWidth();
        int height = getParentHeight();
        b1->setBounds(0, 0, width/6, height/12);
        tcc->setBounds(0, b1->getHeight(), width, height - b1->getHeight());
        repaint();
        }
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tabs)
};
