//
//  Fraction.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/18/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

using namespace std;

class Fraction : public Component
{
public:
    Spinner numerator, denominator;
    
    Fraction() :    numerator {Spinner::SpinnerType::ARRAY, Array<int> {1, 2, 3, 4, 5, 6, 7, 8} },
                    denominator {Spinner::SpinnerType::ARRAY, Array<int> {1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192} }
    {
        addAndMakeVisible (numerator);
        addAndMakeVisible (denominator);
        
        numerator.setText(0, dontSendNotification);
        denominator.setText(3, dontSendNotification);
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha (0.0f));
        g.setColour (Colours::black);
        int lwidth = numerator.getFont().getStringWidth("128");
        g.drawHorizontalLine(getHeight()/2, (getWidth() - lwidth)/2, (getWidth() + lwidth)/2);
    }
    
    void resized() override
    {
        numerator.setFont (Font (getHeight()/2.0f));
        denominator.setFont (Font (getHeight()/2.0f));
        
        int width = getWidth();
        int height = getHeight();
        int numWidth = numerator.getFont().getStringWidth(numerator.getText());
        int numHeight = height/2;
        int denWidth = denominator.getFont().getStringWidth(denominator.getText());
        int denHeight = height/2;
        numerator.setBounds((width - numWidth)/2, 0, numWidth, numHeight);
        denominator.setBounds((width - denWidth)/2, numHeight, denWidth, denHeight);
    }
    
    void attachListener (LabelListener *l)
    {
        numerator.addListener (l);
        denominator.addListener (l);
    }
    
    void detachListener (LabelListener *l)
    {
        numerator.removeListener (l);
        denominator.removeListener (l);
    }
    
    int getNumerator()      {   return numerator.getTextValue().getValue();     }
    int getDenominator()    {   return denominator.getTextValue().getValue();   }
    
    void setFraction (int numerator, int denominator)
    {
        this->numerator.setText (this->numerator.arr.indexOf (numerator), dontSendNotification);
        this->denominator.setText (this->denominator.arr.indexOf (denominator), dontSendNotification);
    }
    
    double getFraction()
    {
        return (double) numerator.getTextValue().getValue() / (double) denominator.getTextValue().getValue();
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fraction)
};
