/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "DraggableLabel.hpp"


//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private Label::Listener
{
public:
    MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor&);
    ~MusicCalculatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MusicCalculatorAudioProcessor& processor;
    
    bool sync;
    DraggableLabel bpmLabel;
    Label msLabel;
    void timerCallback() override;
    double bpmToMs(double bpm);
    void labelTextChanged(Label *labelThatHasChanged) override;
    TableListBox table;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
