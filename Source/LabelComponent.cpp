//
//  DraggableLabelComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <string>


using namespace std;

class LabelComponent :  public Label
{
public:
    LabelComponent()
    {
        setColour(ColourIds::backgroundWhenEditingColourId, Colours::lightblue);
        setFont(Font("Roboto", 50, Font::plain));
        setJustificationType(Justification::centred);
    }
    
    void setFormattedText(double d, NotificationType notification)
    {
        setText(format(d), notification);
    }    
    
private:
    Point<int> mousePoint;
    bool enabled, draggable;
        
    void mouseEnter(const juce::MouseEvent &event) override
    {
        setColour(ColourIds::backgroundColourId, Colours::lightblue);
    }
    
    void mouseExit(const juce::MouseEvent &event) override
    {
        setColour(ColourIds::backgroundColourId, Colours::white);
    }
    
    void mouseDown(const juce::MouseEvent &event) override
    {
        bool ctrlDown = event.mods.isCtrlDown();
        if (ctrlDown)
        {
            double value = getTextValue().getValue();
            value = floor(value);
            setText(format(value), sendNotification);
        }
        
        enabled = false;
        mousePoint.setY(event.y);
    }
    
    void mouseDrag(const juce::MouseEvent &event) override
    {
        const float multiplier = 0.0;
        int delta = mousePoint.getY() - event.y;
        int absDelta = abs(delta);
        if(!enabled && absDelta < 5.0) return;
        if (!enabled)
        {
            enabled = true;
            mousePoint.setY(event.y);
            return;
        }
        bool ctrlDown = event.mods.isCtrlDown();
        //if(ctrlDown) absDelta = absDelta * .1;
        //if(absDelta < 50.0) absDelta *= 0.1;
        //else if (absDelta > 100) absDelta *= 2;
        double x = 0.125;
        for (int i = 10; i < 100; i+=10 )
        {
            if (absDelta < i)
            {
                absDelta *= x;
                break;
            }
            else
            {
                x *= 1.5;
            }
        }
        if(multiplier > 0.0) absDelta = (int)(absDelta * multiplier);
        if(absDelta == 0.0) return;
        double value = getTextValue().getValue();
        for (int i = 0; i < absDelta; i++)
        {
            if (ctrlDown)
            {
                if(delta < 0.0) value -= 0.01;
                else value += 0.01;
            }
            else
            {
                if(delta < 0.0) value -= 1.0;
                else value += 1.0;
            }
            value = valid(value);
            setText(format(value), sendNotification);
        }
        mousePoint.setY(event.y);
    }
    
    // Returns a double in the valid range of 5 -990 bpm
    double valid(double d)
    {
        if (d > 990.0) return 990.0;
        else if (d < 5.0) return 5.0;
        else return d;
    }
    
    // Formats a double with a precision of two decimal places
    String format(double d)
    {
        stringstream ss;
        ss << fixed << setprecision(2) << d;
        return ss.str();
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelComponent)
};
