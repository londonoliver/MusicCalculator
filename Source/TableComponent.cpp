//
//  TableComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "LabelComponent.hpp"
#include <iostream>

using namespace std;

//==============================================================================
/**
 This class shows how to implement a TableListBoxModel to show in a TableListBox.
 */
class TableComponent   :    public Component,
                            public TableListBoxModel,
                            public LookAndFeel_V3
{
public:
    TableComponent()   : font (14.0f)
    {
        // Load some data from an embedded XML file..
        loadData();
        
        // Create our table component and add it to this component..
        addAndMakeVisible (table);
        table.setModel (this);
        
        // give it a border
        table.setColour (ListBox::outlineColourId, Colours::grey);
        table.setOutlineThickness (1);
        
        // Add some columns to the table header, based on the column list in our database..
        forEachXmlChildElement (*columnList, columnXml)
        {
            table.getHeader().addColumn (columnXml->getStringAttribute ("name"),
                                         columnXml->getIntAttribute ("columnId"),
                                         columnXml->getIntAttribute ("width"),
                                         30, 100,
                                         TableHeaderComponent::defaultFlags);
        }
        
        // un-comment this line to have a go of stretch-to-fit mode
        table.getHeader().setStretchToFitActive (true);
        
        table.setMultipleSelectionEnabled (true);
        
        noteType = 1;
        Hz = false;
        
        setLookAndFeel(this);
        
    }
    
    // This is overloaded from TableListBoxModel, and must return the total number of rows in our table
    int getNumRows() override
    {
        return numRows;
    }
    
    // This is overloaded from TableListBoxModel, and should fill in the background of the whole row
    void paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll (Colours::lightblue);
        else if (rowNumber % 2)
            g.fillAll (Colour (0xffeeeeee));
    }
    
    // This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
    // components.
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool /*rowIsSelected*/) override
    {
        g.setColour (Colours::black);
        g.setFont (font);
        
        if (const XmlElement* rowElement = dataList->getChildElement (rowNumber))
        {
            const String text (rowElement->getStringAttribute (getAttributeNameForColumnId (columnId)));
            
            g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
        }
        
        g.setColour (Colours::black.withAlpha (0.2f));
        g.fillRect (width - 1, 0, 1, height);
    }
    
    // This is overloaded from TableListBoxModel, and tells us that the user has clicked a table header
    // to change the sort order.
    void sortOrderChanged (int newSortColumnId, bool isForwards) override
    {
        /*if (newSortColumnId != 0)
        {
            DemoDataSorter sorter (getAttributeNameForColumnId (newSortColumnId), isForwards);
            dataList->sortChildElements (sorter);
            
            table.updateContent();
        }*/
        
        String s;
        
        if (newSortColumnId == 0)
            return;
        else if (newSortColumnId == 1)
        {
            if (noteType == 1)
                noteType = 2;
            else if (noteType == 2)
                noteType = 3;
            else
                noteType = 1;
            
            columnOneName = (noteType == 1) ? "Note (Whole)" : ((noteType == 2) ? "Note (Dotted)" : "Note (Triplet)");
            
        }
        else if (newSortColumnId == 2)
        {
            Hz = !Hz;
            columnTwoName = (Hz) ? "Hz" : "Ms";
        }
        setMilliseconds();
        
    }
    
    // This is overloaded from TableListBoxModel, and must update any custom components that we're using
    Component* refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                        Component* existingComponentToUpdate) override
    {
        // The other columns are editable text columns, for which we use the custom Label component
        EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
        
        // same as above...
        if (textLabel == nullptr)
            textLabel = new EditableTextCustomComponent (*this);
        
        textLabel->setRowAndColumn (rowNumber, columnId);
        return textLabel;
    }
    
    // This is overloaded from TableListBoxModel, and should choose the best width for the specified
    // column.
    int getColumnAutoSizeWidth (int columnId) override
    {
        int widest = 32;
        
        // find the widest bit of text in this column..
        for (int i = getNumRows(); --i >= 0;)
        {
            if (const XmlElement* rowElement = dataList->getChildElement (i))
            {
                const String text (rowElement->getStringAttribute (getAttributeNameForColumnId (columnId)));
                
                widest = jmax (widest, font.getStringWidth (text));
            }
        }
        
        return widest + 8;
    }
    
    // A couple of quick methods to set and get cell values when the user changes them
    String getText (const int columnNumber, const int rowNumber) const
    {
        return dataList->getChildElement (rowNumber)->getStringAttribute ( getAttributeNameForColumnId(columnNumber));
    }
    
    void setText (const int columnNumber, const int rowNumber, const String& newText)
    {
        const String& columnName = table.getHeader().getColumnName (columnNumber);
        dataList->getChildElement (rowNumber)->setAttribute (columnName, newText);
        table.updateContent();
    }
    
    int getNoteType ()
    {
        return noteType;
    }
    
    void setNoteType (int i)
    {
        noteType = i;
    }
    
    bool getHz ()
    {
        return Hz;
    }
    
    void setHz (bool b)
    {
        Hz = b;
    }
    
    void setLabelComponent(LabelComponent* l)
    {
        labelComponent = l;
    }
    
    void setMilliseconds()
    {
        double bpm = labelComponent->getTextValue().getValue();
        double ms = 1000.0 / (bpm / 60.0); // ms for whole quarter note
        double hz = bpm /60.0;             // hz for whole quarter note
        double value = (Hz) ? hz : ms;
        int noteType = getNoteType();
        int noteDenominator = 4, noteNumerator = 1;
        String s = "";
        switch (noteType) {
            case 1:     // whole note
            {
                break;
            }
            case 2:     // dotted note
            {
                value = value * (3.0/2.0);
                s = ".";
                break;
            }
            case 3:     // triplet note
            {
                value = value * (2.0/3.0);
                s = "T";
                break;
            }
            default:
                break;
        } // end switch
        
        for (int i = 0; i < table.getNumRows(); i++ )
        {
            setText(1, i, String(noteNumerator) + "/" + String(noteDenominator) + s);
            setText(2, i, String(value));
            if (Hz)
                value = value*2.0;
            else
                value = value/2.0;
            noteDenominator = noteDenominator * 2;
        }
    }
    
    TableListBox* getTable()
    {
        return &table;
    }
    
    //==============================================================================
    void resized() override
    {
        // position our table with a gap around its edge
        table.setBoundsInset (BorderSize<int> (8));
    }
    
protected:
    LabelComponent* labelComponent;
    
private:
    TableListBox table;     // the table component itself
    Font font;
    String columnOneName = "Note (Whole)", columnTwoName = "Ms";
    
    ScopedPointer<XmlElement> demoData;   // This is the XML document loaded from the embedded file "demo table data.xml"
    XmlElement* columnList; // A pointer to the sub-node of demoData that contains the list of columns
    XmlElement* dataList;   // A pointer to the sub-node of demoData that contains the list of data rows
    int numRows;            // The number of rows of data we've got
    
    int noteType;       // State of the note column: 1 = whole, 2 = dotted, 3 = triplet
    bool Hz = false;    // if true, then column two will show hz, if false it will show ms

    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class EditableTextCustomComponent  : public Label
    {
    public:
        EditableTextCustomComponent (TableComponent& td)  : owner (td)
        {
            // double click to edit the label text; single click handled below
            setEditable (false);
            setColour (textColourId, Colours::black);
        }
        
        void mouseDown (const MouseEvent& event) override
        {
            // single click on the label should simply select the row
            owner.table.selectRowsBasedOnModifierKeys (row, event.mods, false);
            
            Label::mouseDown (event);
        }
        
        void textWasEdited() override
        {
            owner.setText (columnId, row, getText());
        }
        
        // Our demo code will call this when we may need to update our contents
        void setRowAndColumn (const int newRow, const int newColumn)
        {
            row = newRow;
            columnId = newColumn;
            setText (owner.getText(columnId, row), dontSendNotification);
        }
        
    private:
        TableComponent& owner;
        int row, columnId;
    };
    
    //==============================================================================
    // A comparator used to sort our data when the user clicks a column header
    class DemoDataSorter
    {
    public:
        DemoDataSorter (const String& attributeToSortBy, bool forwards)
        : attributeToSort (attributeToSortBy),
        direction (forwards ? 1 : -1)
        {
        }
        
        int compareElements (XmlElement* first, XmlElement* second) const
        {
            int result = first->getStringAttribute (attributeToSort)
            .compareNatural (second->getStringAttribute (attributeToSort));
            
            if (result == 0)
                result = first->getStringAttribute ("ID")
                .compareNatural (second->getStringAttribute ("ID"));
            
            return direction * result;
        }
        
    private:
        String attributeToSort;
        int direction;
    };
    
    //==============================================================================
    // this loads the embedded database XML file into memory
    void loadData()
    {
        demoData = XmlDocument::parse (BinaryData::delay_times_data_xml);
        
        dataList   = demoData->getChildByName ("DATA");
        columnList = demoData->getChildByName ("COLUMNS");
        
        numRows = dataList->getNumChildElements();
    }
    
    // (a utility method to search our XML for the attribute that matches a column ID)
    String getAttributeNameForColumnId (const int columnId) const
    {
        forEachXmlChildElement (*columnList, columnXml)
        {
            if (columnXml->getIntAttribute ("columnId") == columnId)
                return columnXml->getStringAttribute ("name");
        }
        
        return String();
    }
    
    //==============================================================================
    // The folling methods implement the custom look and feel
    
    // Overloaded from LookAndFeel_V3
    void drawTableHeaderColumn(Graphics &g,
                               const String & columnName,
                               int 	columnId,
                               int 	width,
                               int 	height,
                               bool isMouseOver,
                               bool isMouseDown,
                               int 	columnFlags 
                               ) override
    {
        //if(columnId == 1)
        {
            if (isMouseDown)
                g.fillAll (Colour (0x8899aadd));
            else if (isMouseOver)
                g.fillAll (Colour (0x5599aadd));
        }
        
        Rectangle<int> area (width, height);
        area.reduce (4, 0);
        
        /*if ((columnFlags & (TableHeaderComponent::sortedForwards | TableHeaderComponent::sortedBackwards)) != 0)
        {
            Path sortArrow;
            sortArrow.addTriangle (0.0f, 0.0f,
                                   0.5f, (columnFlags & TableHeaderComponent::sortedForwards) != 0 ? -0.8f : 0.8f,
                                   1.0f, 0.0f);
            
            g.setColour (Colour (0x99000000));
            g.fillPath (sortArrow, sortArrow.getTransformToScaleToFit (area.removeFromRight (height / 2).reduced (2).toFloat(), true));
        }*/
        
        g.setColour (Colours::black);
        g.setFont (Font (height * 0.5f, Font::bold));
        if (columnId == 1)
            g.drawFittedText (columnOneName, area, Justification::centredLeft, 1);
        else
            g.drawFittedText (columnTwoName, area, Justification::centredLeft, 1);
    }
    
    // Overloaded from LookAndFeel_V3
    void drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header) override
    {
        Rectangle<int> r (header.getLocalBounds());
        
        g.setColour (Colours::black.withAlpha (0.5f));
        g.fillRect (r.removeFromBottom (1));
        
        g.setColour (Colours::white.withAlpha (0.6f));
        g.fillRect (r);
        
        g.setColour (Colours::black.withAlpha (0.5f));
        
        for (int i = header.getNumColumns (true); --i >= 0;)
            g.fillRect (header.getColumnPosition (i).removeFromRight (1));
    }
    
    void mouseDown (const MouseEvent &event) override
    {
        cout <<"mouseDown" << endl;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TableComponent)
};
