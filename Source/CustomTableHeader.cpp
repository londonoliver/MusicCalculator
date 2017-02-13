//
//  CustomTableHeader.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/12/17.
//
//

#include "CustomTableHeader.hpp"

CustomTableHeader::CustomTableHeader()
{
}

void CustomTableHeader::columnClicked(int columnId, const juce::ModifierKeys &mods)
{
    cout << "column " << columnId << " clicked" << endl;
    
}
