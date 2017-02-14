//
//  NoteSpinner.hpp
//  MusicCalculator
//
//  Created by London Oliver on 2/13/17.
//
//

#ifndef NoteSpinner_hpp
#define NoteSpinner_hpp

#include "../JuceLibraryCode/JuceHeader.h"
#include "LabelComponent.hpp"

class NoteSpinner : public Component
{
public:
    NoteSpinner();
    void setFont (Font f);
    Font getFont();
    void resized() override;
private:
    LabelComponent l1, l2;
    Font f;
};

#endif /* NoteSpinner_hpp */
