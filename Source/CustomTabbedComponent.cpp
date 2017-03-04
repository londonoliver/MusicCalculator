//
//  CustomTabbedComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#include "CustomTabbedComponent.h"

CustomTabbedComponent::CustomTabbedComponent() : TabbedComponent (TabbedButtonBar::TabsAtTop)
{
    addTab("Tempo Conversion", Colours::white, &tcc, true);
    addTab("Note Conversion", Colours::white, &ncc, true);
}

CustomTabbedComponent::~CustomTabbedComponent()
{
}
