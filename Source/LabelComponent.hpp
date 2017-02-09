//
//  LabelComponent.hpp
//  MusicCalculator
//
//  Created by London Oliver on 2/8/17.
//
//

#ifndef LabelComponent_hpp
#define LabelComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class LabelComponent :  public Label,
private LabelListener
{
public:
    LabelComponent();
    
    void setFormattedText(double d, NotificationType notification);
    
private:
    Point<int> mousePoint;
    bool enabled, draggable;
    String oldText;
    
    void labelTextChanged(Label* labelThatHasChanged) override;
    void editorShown(Label* lablel, TextEditor& editor) override;
    void editorHidden(Label* label, TextEditor& editor) override;
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    String formatBpm(double d);
    
};

#endif /* LabelComponent_hpp */
