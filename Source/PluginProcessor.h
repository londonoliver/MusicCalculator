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
    double* getTempo();
    void setTempo (double d);
    
    bool setSync (bool b);
    bool getSync();
    
    int getNote();
    void setNote (int val);
    
    int getOctave();
    void setOctave (int val);
   
    bool tempoInformationAvailable();

private:
    //==============================================================================
    double bpm;
    double hostBpm;
    bool sync;
    int note;
    int octave;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessor)
    
    //==============================================================================
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
