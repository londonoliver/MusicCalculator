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
#include "LabelComponent.hpp"
#include "TableComponent.cpp"
#include "AlertCompnent.cpp"


//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private LabelListener,
                                            private ButtonListener,
                                            private ChangeListener
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
    
    LabelComponent bpmLabel;
    Label msLabel;
    void labelTextChanged(Label *labelThatHasChanged) override;
    
    void timerCallback() override;
    double bpmToMs(double bpm);
    
    
    TableComponent table;
    
    TextButton syncButton;
    void buttonClicked(Button *button) override;
    
    double bpm;
    
    bool hostHasTempoInformation();
    
    AlertComponent alert;
    
    void changeListenerCallback (ChangeBroadcaster *source) override;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
