//
//  CustomTableHeader.hpp
//  MusicCalculator
//
//  Created by London Oliver on 2/12/17.
//
//

#ifndef CustomTableHeader_hpp
#define CustomTableHeader_hpp

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>

using namespace std;

class CustomTableHeader : public TableHeaderComponent
{
public:
    CustomTableHeader();
private:
    void columnClicked (int columnId, const ModifierKeys &mods) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomTableHeader)
};

#endif /* CustomTableHeader_hpp */
