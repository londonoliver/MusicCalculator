//
//  TempoConversionComponent.h
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#ifndef TempoConversionComponent_h
#define TempoConversionComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoSpinner.h"
#include "CustomTableCell.h"

class TempoConversionComponent : public Component, public LookAndFeel_V3, public ButtonListener
{
public:
    
    enum class ColumnOneMode {NORMAL, DOTTED, TRIPLET};
    enum class ColumnTwoMode {MS, HZ};
    
    ColumnOneMode col1_Mode = ColumnOneMode::NORMAL;
    ColumnTwoMode col2_Mode = ColumnTwoMode::MS;
    
    
    TempoSpinner tempoSpinner;
    TextButton b1, b2;
    
    CustomTableCell c11;
    CustomTableCell c12;
    CustomTableCell c13;
    CustomTableCell c14;
    CustomTableCell c15;
    CustomTableCell c16;
    CustomTableCell c17;
    CustomTableCell c18;
    
    CustomTableCell c21;
    CustomTableCell c22;
    CustomTableCell c23;
    CustomTableCell c24;
    CustomTableCell c25;
    CustomTableCell c26;
    CustomTableCell c27;
    CustomTableCell c28;
    
    
    int width, height;
    
    TempoConversionComponent();
    ~TempoConversionComponent();
    
    void resized() override;
    void setTableText();
    
private:
    
    Font getTextButtonFont (TextButton &, int buttonHeight) override;
    void buttonClicked (Button *button) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TempoConversionComponent)
};
#endif /* TempoConversionComponent_h */
