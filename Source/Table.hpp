//
//  Table.hpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//

#ifndef Table_hpp
#define Table_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class Table : public TableListBox, public TableListBoxModel
{
public:
    Table();
    ~Table();
    
    
private:
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    int denominators[8];
};

#endif /* Table_hpp */
