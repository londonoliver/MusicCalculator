//
//  Spinner.h
//  MusicCalculator
//
//  Created by London Oliver on 2/19/17.
//
//

#ifndef Spinner_h
#define Spinner_h

#include "../JuceLibraryCode/JuceHeader.h"

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
    
    Spinner (SpinnerType type, int min, int max);
    
    void setRange (int min, int max);
    void setText (int val);
private:
    int inRange (int val);
    void mouseDown(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    void mouseDoubleClick (const MouseEvent &event) override;
    void mouseExit (const MouseEvent &event) override;
    String getNote (int value);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Spinner)
};

#endif /* Spinner_h */
