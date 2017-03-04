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

class CustomTabbedComponent : public TabbedComponent
{
public:
    TempoConversionComponent tcc;
    NoteConversionComponent ncc;
    CustomTableCell ctc;
    
    CustomTabbedComponent();
    ~CustomTabbedComponent();
};

#endif /* CustomTabbedComponent_h */
