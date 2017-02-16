//
//  Spinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/15/17.
//
//

#ifndef Spinner_hpp
#define Spinner_hpp
#endif

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>

class Spinner : public Label
{
public:
    enum class SpinnerType {NUMBER, NOTE, PERIOD};
    
    int min;
    int max;
    bool enabled;
    Point<int> mousePoint;
    SpinnerType type;
    int value;
    
    Spinner (SpinnerType type, int min, int max)
    {
        this->type = type;
        this->min = min;
        this->max = max;
        
        setFont (Font ("Roboto", 50, Font::plain));
        
        setJustificationType (Justification::right);
        
        setBorderSize (BorderSize<int> (0));
        
        setEditable (false);
    }
    
    void setRange (int min, int max)
    {
        this->min = min;
        this->max = max;
    }
    
    void setText (int value)
    {
        this->value = value;
        
        if (type == SpinnerType::NUMBER)
            Label::setText (String (value), sendNotification);
        else if (type == SpinnerType::NOTE)
            Label::setText (getNote (value), sendNotification);
        else
            Label::setText (".", sendNotification);
    }
    
private:
    
    void mouseDown(const MouseEvent &event) override
    {
        enabled = false;
        mousePoint.setY(event.y);
    }
    
    void mouseDrag(const MouseEvent &event) override
    {
            int delta = mousePoint.getY() - event.y;
            int absDelta = abs(delta);
            if (!enabled && absDelta < 5) return;
            if (!enabled)
            {
                enabled = true;
                mousePoint.setY (event.y);
                return;
            }
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
            if (absDelta == 0) return;
            int value = getTextValue().getValue();
            for (int i = 0; i < absDelta; i++)
            {

                if (delta < 0) value -= 1;
                else value += 1;
                
                if (value > max) value = max;
                else if (value < min) value = min;

                setText (value);
            }
            mousePoint.setY (event.y);
    }
    
    void mouseDoubleClick (const MouseEvent &event) override
    {
        getParentComponent()->mouseDoubleClick (event);
    }
    
    String getNote (int value)
    {
        switch (value) {
            case 0:
                return "C";
                break;
            case 1:
                return "C#";
                break;
            case 2:
                return "D";
                break;
            case 3:
                return "D#";
                break;
            case 4:
                return "E";
                break;
            case 5:
                return "F";
                break;
            case 6:
                return "F#";
                break;
            case 7:
                return "G";
                break;
            case 8:
                return "G#";
                break;
            case 9:
                return "A";
                break;
            case 10:
                return "A#";
                break;
            case 11:
                return "B";
                break;
                
            default:
                return "";
                break;
        }
    }
};
