//
//  NewTable.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/17/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "TableColumn.cpp"

using namespace std;

class NewTable : public Component
{
public:
    OwnedArray<TableColumn, CriticalSection> cols;
    
    NewTable()
    {
        for (int i = 0; i < 9; i++)
        {
            cols.add (new  TableColumn (8));
            addAndMakeVisible (cols [i]);
            for (int j = 0; j < cols[i]->cells.size(); j++)
            {
                cols[i]->cells[j]->label.setText("("+String(i)+", "+String(j)+")", dontSendNotification);
            }
        }
    }
    
    ~NewTable()
    {
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll(Colours::white.withAlpha(0.0f));
        g.setColour(Colours::white);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 0.015f);
    }
    
    void resized() override
    {
        int colWidth = getWidth()/9;
        int colHeight = getHeight();
        for (int i = 0; i < cols.size(); i++)
        {
            cols [i]->setBounds(colWidth * i, 0, colWidth, colHeight);
        }
        
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewTable)
};
