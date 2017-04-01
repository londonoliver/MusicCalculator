//
//  Fraction.h
//  MusicCalculator
//
//  Created by London Oliver on 3/31/17.
//
//

#ifndef Fraction_h
#define Fraction_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

class Fraction : public Component, public LabelListener, public TextEditorListener
{
public:
    Spinner numerator, denominator;
    Label numEd, denEd;
    Colour colour;
    
    Fraction();
    ~Fraction();
    
    void paint (Graphics &g) override;
    void resized() override;
    void setColour (Colour c);
    void attachListener (LabelListener *l);
    void detachListener (LabelListener *l);
    int getNumerator();
    int getDenominator();
    void setFraction (int numerator, int denominator);
    double getFraction();
    
private:
    void mouseDoubleClick (const MouseEvent &e) override;
    void editorHidden (Label *label, TextEditor &editor) override;
    void textEditorTextChanged (TextEditor &ed) override;
    void editorShown (Label *, TextEditor &ed) override;
    void labelTextChanged (Label *labelThatHasChanged) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fraction)
};


#endif /* Fraction_h */
