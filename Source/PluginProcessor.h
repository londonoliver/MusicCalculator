/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class MusicCalculatorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MusicCalculatorAudioProcessor();
    ~MusicCalculatorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    double* getBpm();
    void setBpm (double d);
    bool setSync (bool b);
    bool getSync();
    
    int getNoteType();
    void setNoteType (int i);
    bool getHz();
    void setHz (bool b);
    
    int getNoteName ();
    void setNoteName (int noteName);
    int getNoteNumber ();
    void setNoteNumber (int noteNumber);

private:
    double bpm;
    double hostBpm;
    bool sync;
    int noteName, noteNumber;
    
    // To rememeber table information
    int noteType;
    bool Hz;
    
    bool tempoInformationAvailable();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessor)
    
    //==============================================================================
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
