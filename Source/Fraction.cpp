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
    Spinner num, den;
    
    Fraction() :    num {Spinner::SpinnerType::ARRAY, Array<int> {1, 2, 3, 4, 5, 6, 7, 8} },
                    den {Spinner::SpinnerType::ARRAY, Array<int> {1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192} }
    {
        addAndMakeVisible (num);
        addAndMakeVisible (den);
        
        num.setText(0);
        den.setText(3);
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha (0.0f));
        g.setColour (Colours::black);
        int lwidth = num.getFont().getStringWidth("128");
        g.drawHorizontalLine(getHeight()/2, (getWidth() - lwidth)/2, (getWidth() + lwidth)/2);
    }
    
    void resized() override
    {
        num.setFont (Font (getHeight()/2.0f));
        den.setFont (Font (getHeight()/2.0f));
        
        int width = getWidth();
        int height = getHeight();
        int numWidth = num.getFont().getStringWidth(num.getText());
        int numHeight = height/2;
        int denWidth = den.getFont().getStringWidth(den.getText());
        int denHeight = height/2;
        num.setBounds((width - numWidth)/2, 0, numWidth, numHeight);
        den.setBounds((width - denWidth)/2, numHeight, denWidth, denHeight);
    }
    
    void attachListener (LabelListener *l)
    {
        num.addListener (l);
        den.addListener (l);
    }
    
    void detachListener (LabelListener *l)
    {
        num.removeListener (l);
        den.removeListener (l);
    }
    
    double getFraction()
    {
        return (double) num.getTextValue().getValue() / (double) den.getTextValue().getValue();
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fraction)
};
