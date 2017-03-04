//
//  NoteConversionComponent.h
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#ifndef NoteConversionComponent_h
#define NoteConversionComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteSpinner.h"
#include "CustomTableCell.h"

class NoteConversionComponent : public Component
{
public:
    
    NoteSpinner noteSpinner;
    Label label;
    CustomTableCell c1;
    
    int width, height;
    
    NoteConversionComponent();
    ~NoteConversionComponent();
    void resized() override;
    void setTableText();
    double semitoneShift (double value, double amount);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteConversionComponent)
};
#endif /* NoteConversionComponent_h */
