//
//  CustomTableCell.h
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#ifndef CustomTableCell_h
#define CustomTableCell_h

#include "../JuceLibraryCode/JuceHeader.h"

class CustomTableCell : public Component, public ButtonListener, public ChangeListener
{
public:
    
    Label label;
    Label copied;
    bool fadeout;
    ScopedPointer<DrawableButton> button;
    Colour bgColour;
    
    CustomTableCell();
    ~CustomTableCell();
    
    void setBackgroundColor (Colour colour);
    void paint (Graphics &g) override;
    void resized() override;
    
private:
    
    void buttonClicked (Button *button) override;
    void changeListenerCallback (ChangeBroadcaster *source) override;
    void mouseEnter (const MouseEvent &event) override;
    void mouseExit (const MouseEvent &event) override;
    void mouseDown (const MouseEvent& event) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomTableCell)
};

#endif /* CustomTableCell_h */
