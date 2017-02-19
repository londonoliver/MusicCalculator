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
    enum class LabelType{BPM, NOTENAME, NOTENUMBER};
    void setFormattedText(double d, NotificationType notification);
    void setLabelType (LabelType);
    LabelType getLabelType();
    int getNote();
    void setNote (int i);
    int getOctave();
    void setOctave (int i);
    
    Font getFont();
    
    int getNoteIndex();
    
    int note, octave;
    
private:
    Point<int> mousePoint;
    bool enabled, draggable;
    String oldText;
    int noteIndex, noteNumber;
    LabelType labelType;
    double bpm;
    Font font;
    
    int noteToIndex (String s);
    
    bool mouseIsDownWithCtrl;

    
    void labelTextChanged(Label* labelThatHasChanged) override;
    void editorShown(Label* lablel, TextEditor& editor) override;
    void editorHidden(Label* label, TextEditor& editor) override;
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    String formatBpm(double d);
    String getNoteNameString (int i);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelComponent)
};

#endif /* LabelComponent_hpp */
