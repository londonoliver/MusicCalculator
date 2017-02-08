//
//  AlertComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/7/17.
//
//

#include <stdio.h>
#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

class AlertComponent :  public Label, public ComponentAnimator
{
public:
    
    AlertComponent()
    {
        setText("Hello", dontSendNotification);
        setAlpha(0.0f);
        fadeIn(this, 1000);
        fadeOut(this, 1000);
    }
    
    void paint(Graphics &g) override
    {
        
        /*String s = "No tempo information";
        int width = 150;
        int height = 50;
        g.setColour(Colours::black);
        g.setColour(Colours::grey);
        g.fillRoundedRectangle(0, 0, width, height, 15);
        g.setColour(Colours::black);
        g.drawText(s, 0, 0, width, height, Justification::centred);*/
    }
    
    void doIt()
    {
        setVisible(false);
        setAlpha(1.0f);
        fadeIn(this, 1000);
        fadeOut(this, 1000);
        cout << "did it" << endl;
    }
    
    
private:
  
};
