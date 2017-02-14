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
#include "NoteSpinner.hpp"


//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private LabelListener,
                                            private ButtonListener,
                                            private TableHeaderComponent::Listener
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
    void labelTextChanged (Label *labelThatHasChanged) override;
    
    void timerCallback() override;
    double bpmToMs(double bpm);
    
    
    TableComponent table;
    
    TextButton syncButton;
    void buttonClicked (Button *button) override;
    
    double bpm;
    
    bool hostHasTempoInformation();
    
    AlertComponent alert;
    
    void tableColumnsChanged (TableHeaderComponent *tableHeader) override;
    void tableColumnsResized (TableHeaderComponent *tableHeader) override;
    void tableSortOrderChanged (TableHeaderComponent *tableHeader) override;
    void tableColumnDraggingChanged (TableHeaderComponent *tableHeader, int columnIdNowBeingDragged) override;
    
    NoteSpinner noteSpinner;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
