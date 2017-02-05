//
//  Table.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//

#include "Table.hpp"

Table::Table()
{
    setModel(this);
    int denominators[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
}

Table::~Table()
{
}

int Table::getNumRows()
{
    return 8;
}

void Table::paintListBoxItem(int rowNumber,
                             juce::Graphics &g,
                             int width, int height,
                             bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(Colours::lightblue);
    
    String note = "1/" + String(denominators[rowNumber]);
    g.drawText(note, 5, 0, width, height, Justification::centredLeft, true);
}
