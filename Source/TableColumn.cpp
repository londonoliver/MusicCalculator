//
//  TableColumn.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/18/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomTableCell.h"

class TableColumn : public Component
{
public:
    OwnedArray<CustomTableCell, CriticalSection> cells;
    int numRows;
    
    TableColumn(int numRows)
    {
        this->numRows = numRows;
        
        for (int row = 0; row < numRows; row++)
        {
            cells.add(new CustomTableCell());
            addAndMakeVisible(cells[row]);
        }
    }
    
    void paint (Graphics &g) override
    {
        g.setColour(Colours::white);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 2.0f);
    }
    
    void resized() override
    {
        int cellWidth = getWidth();
        int cellHeight = getHeight() / numRows;
        
        for (int row = 0; row < numRows; row++)
        {
            cells[row]->setBounds(0, row * cellHeight, cellWidth, cellHeight);
        }
    }
    
private:
};
