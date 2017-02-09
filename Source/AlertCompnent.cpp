//
//  AlertCompnent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/8/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"

class AlertComponent    :   public Label

{
public:
    int width = 150;
    int height = 50;
    
    AlertComponent()
    {
    }
    
    void paint(Graphics &g) override
    {
        g.setColour(Colours::grey);
        g.fillRoundedRectangle(0, 0, width, height, 15);
        g.setColour(Colours::black);
        g.drawText("No Tempo Information", 0, 0, width, height, Justification::centred);
    }
    
    void flash()
    {
        setVisible(true);
        setAlpha(1.0f);
        Desktop::getInstance().getAnimator().animateComponent(this, this->getBounds(), 0.0f, 750, true, 0.0, 1.0);
    }
    
    int getWidth()
    {
        return width;
    }
    
    int getHeight()
    {
        return height;
    }

private:

};
