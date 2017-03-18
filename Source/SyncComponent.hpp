//
//  SyncComponent.hpp
//  MusicCalculator
//
//  Created by London Oliver on 3/13/17.
//
//

#ifndef SyncComponent_hpp
#define SyncComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class SyncComponent : public Component, public LookAndFeel_V3
{
public:
    int labelHeight;
    TextButton syncButton;
    Label syncLabel;
    
    SyncComponent();
    ~SyncComponent();
    
    void paint (Graphics &g) override;
    void resized() override;
private:
    Font getTextButtonFont (TextButton &, int buttonHeight) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SyncComponent)
};

#endif /* SyncComponent_hpp */
