//
//  HertzSpinner.h
//  MusicCalculator
//
//  Created by London Oliver on 2/19/17.
//
//

#ifndef HertzSpinner_h
#define HertzSpinner_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

class HertzSpinner : public Component, private LabelListener
{
public:
    int width;
    int height;
    
    Font font;
    
    Spinner s1;
    Spinner s2;
    Spinner s3;
    Spinner s4;
    
    Label ed;
    
    int s1Width;
    int s2Width;
    int s3Width;
    int s4Width;
    
    HertzSpinner();
    
    String toString();
    void fitBounds();
    void setSpinnersText (String val);
    void attachListener(Label::Listener *listener);
    void resized() override;
private:
    void mouseDoubleClick (const MouseEvent &e) override;
    void setSpinnersVisible (bool visible);
    void editorHidden (Label *label, TextEditor &editor) override;
    void labelTextChanged (Label *labelThatHasChanged) override;
    void editorShown (Label *, TextEditor &) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HertzSpinner)
};
#endif /* HertzSpinner_h */
