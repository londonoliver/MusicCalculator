//
//  CustomTabbedComponent.h
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#ifndef CustomTabbedComponent_h
#define CustomTabbedComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoConversionComponent.h"
#include "NoteConversionComponent.h"
#include "Spinner.h"
#include "Table.h"
#include "SyncComponent.hpp"

class CustomTabbedComponent : public TabbedComponent, public LookAndFeel_V3
{
public:
    TempoConversionComponent tcc;
    NoteConversionComponent ncc;
    SyncComponent sync;
    
    ScopedPointer<Drawable> metronome;
    ScopedPointer<Drawable> note;
    
    CustomTabbedComponent();
    ~CustomTabbedComponent();
    
    void paint(Graphics &g) override;
    void resized() override;
    
    static Rectangle<int> getTabArea (Rectangle<int>& content, BorderSize<int>& outline,
                                      const TabbedButtonBar::Orientation orientation, const int tabDepth);
    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override;
    int getTabButtonBestWidth (TabBarButton& button, int tabDepth) override;
    void drawTabAreaBehindFrontButton (TabbedButtonBar &, Graphics &, int w, int h) override;
    int getTabButtonOverlap (int tabDepth) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomTabbedComponent)
};

#endif /* CustomTabbedComponent_h */
