//
//  DraggableLabel.hpp
//  MusicCalculator
//
//  Created by London Oliver on 2/3/17.
//
//

#ifndef DraggableLabel_hpp
#define DraggableLabel_hpp

#include "../JuceLibraryCode/JuceHeader.h"


class DraggableLabel : public Label
{
public:
    DraggableLabel();
    ~DraggableLabel();
    
private:
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    double valid(double d);
    Point<int> mousePoint;
    bool enabled;
};

#endif /* DraggableLabel_hpp */
