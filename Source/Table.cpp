//
//  TableComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//
#include "Table.h"
#include <iostream>

using namespace std;


Table::Table()   : font (14.0f)
{
    
    
    width = 200;
    height = 300;
    
    header = new CustomTableHeader();
    header->setTable(this);
    table.setHeader(header);
    
    numTempoRows = 8;
    numNoteRows = 1;
    numHertzRows = 1;
    
    
    table.getHeader().addColumn(columnOneName, 1, width/2);
    table.getHeader().addColumn(columnTwoName, 2, width/2);
    
    addAndMakeVisible (table);
    table.setModel (this);
    
    setTableType();
}




int Table::getNumRows()
{
    return  (display)   ?
    
                            (display->displayType == Display::DisplayType::TEMPO)   ?   numTempoRows
    
                                                                                    :
    
                            ((display->displayType == Display::DisplayType::NOTE)   ?   numNoteRows
                             
                                                                                    :   numHertzRows)
    
                        :
    
                            0;
}




void Table::paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected)
{
    if (rowNumber % 2)
        g.fillAll (Colour (0xffeeeeee));
}




void Table::paintCell (Graphics& g, int rowNumber, int columnId,
                int width, int height, bool /*rowIsSelected*/)
{
}




void Table::sortOrderChanged (int newSortColumnId, bool isForwards)
{
}




Component* Table::refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                    Component* existingComponentToUpdate)
{
    EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
    
    if (textLabel == nullptr)
        textLabel = new EditableTextCustomComponent (*this);
    
    if (columnId == 2)
    {
        textLabel->setEditable(true);
    }
    
    textLabel->setText(
                       
       (display)    ?
       
                        (display->displayType == Display::DisplayType::TEMPO)   ?   setTempoTable (rowNumber, columnId)
                   
                                                                                :
                   
                        ((display->displayType == Display::DisplayType::NOTE)   ?   setNoteTable (rowNumber, columnId)
                    
                                                                                :   setHertzTable (rowNumber, columnId))
       
                    :
       
                        "", sendNotification
    );
    
    return textLabel;
}




int Table::getColumnAutoSizeWidth (int columnId)
{
    return width/2;
}




String Table::getText (const int columnNumber, const int rowNumber) const
{
    return "";
}




void Table::setText (const int columnNumber, const int rowNumber, const String& newText)
{
    table.updateContent();
}




void Table::setDisplay (Display *display)
{
    this->display = display;
}



double Table::getTempo()
{
    return (display) ? display->getTempo() : 0;
}




int Table::getNote()
{
    return (display) ? display->getNote() : 0;
}




int Table::getOctave()
{
    return (display) ? display->getOctave() : 0;
}




double Table::noteToHz(int note, int octave)
{
    note -= 9;
    octave -= 4;
    return semitoneShift(440, (float)note + (float)(octave * 12));
}




double Table::semitoneShift(double value, double amount)
{
    return value / pow (2, amount / -12);
}




double Table::getWholeNoteMs()
{
    return (1000.0 / (getTempo() / 60.0)) * 4.0 *
            ((delayType == DelayType::DOTTED) ? (3.0 / 2.0) :
             ((delayType == DelayType::TRIPLET) ? (2.0 / 3.0) : 1));
}




double Table::getWholeNoteHz()
{
    return (getTempo() / 60.0) / 4.0 /
    ((delayType == DelayType::DOTTED) ? (3.0 / 2.0) :
     ((delayType == DelayType::TRIPLET) ? (2.0 / 3.0) : 1));
}




String Table::setTempoTable (int rowNumber, int columnId)
{
    return  (columnId == 1)     ?   "1/"                                            +
                                    String (pow (2, rowNumber))                     +
    
                                    ((delayType == DelayType::DOTTED)   ?   "."
                                     
                                                                        :
                                     
                                    ((delayType == DelayType::TRIPLET)  ?   "T"
                                     
                                                                        :   ""))
    
                                :
    
            ((columnId == 2)    ?   (tempoConversion == TempoConversion::MS)    ?   String (getWholeNoteMs() / pow (2, rowNumber))
             
                                                                                :   String (getWholeNoteHz() * pow (2, rowNumber))
             
                                :   "");
}




String Table::setNoteTable (int rowNumber, int columnId)
{
    return  (columnId == 1)     ?   String (noteToHz (getNote(), getOctave()))
    
                                :   "";
}




String Table::setHertzTable (int rowNumber, int columnId)
{
    return  "";
}



void Table::setTableType ()
{
    if (display)
    {
        if (display->displayType == Display::DisplayType::TEMPO)
        {
            table.getHeader().setColumnVisible(1, true);
            table.getHeader().setColumnVisible(2, true);
            
            table.getHeader().setColumnWidth(1, width/2);
            table.getHeader().setColumnWidth(2, width/2);
            
            columnOneName = (delayType == DelayType::NORMAL)    ?   "Note (Normal)"
                                                                :
                            ((delayType == DelayType::DOTTED)   ?   "Note (Dotted)"
                                                                :   "Note (Triplet)");
            
            columnTwoName = (tempoConversion == TempoConversion::MS)    ?   "Ms"
                                                                        :   "Hz";
        }
        else if (display->displayType == Display::DisplayType::NOTE)
        {
            table.getHeader().setColumnVisible(1, true);
            table.getHeader().setColumnVisible(2, false);
            
            table.getHeader().setColumnWidth(1, width);
            
            columnOneName = "Hz";
        }
        else
        {
            table.getHeader().setColumnVisible(1, true);
            table.getHeader().setColumnVisible(2, false);
            
            table.getHeader().setColumnWidth(1, width);
        }
    }
    table.getHeader().resized();
}




TableListBox* Table::getTable()
{
    return &table;
}




void Table::resized()
{
    table.setBounds (0, 0, width, height);
    table.setBoundsInset (BorderSize<int> (0));
    table.getHeader().setBounds(0, 0, 0, 0);
    
    if (getParentComponent())
        getParentComponent()->resized();
}



//=============================================================================
/*
 *  EditableTextCustomComponent
 */
//=============================================================================


    Table::EditableTextCustomComponent::EditableTextCustomComponent (Table& td)  : owner (td)
    {
        setEditable (false);
        setColour (textColourId, Colours::black);
    }


    void Table::EditableTextCustomComponent::mouseDown (const MouseEvent& event)
    {
        Label::mouseDown (event);
    }


    void Table::EditableTextCustomComponent::textWasEdited()
    {
    }


    void Table::EditableTextCustomComponent::setRowAndColumn (const int newRow, const int newColumn)
    {
    }


    void Table::EditableTextCustomComponent::editorShown (TextEditor *editor)
    {
        editor->setReadOnly(true);
        editor->setCaretVisible(false);
    }



//=============================================================================
/*
 *  CustomTableHeader
 */
//=============================================================================


    Table::CustomTableHeader::CustomTableHeader()
    {
        addAndMakeVisible(b1);
        addAndMakeVisible(b2);
        b1.setName("b1");
        b2.setName("b2");
    }

    void Table::CustomTableHeader::paint (Graphics& g)
    {
    }


    void Table::CustomTableHeader::resized()
    {
        if (table)
        {
            b1.setBounds(0, 0, table->width/getNumColumns(true), 20);
        }
    }


    void Table::CustomTableHeader::setTable (Table* t)
    {
        table = t;
    }

    void Table::CustomTableHeader::buttonClicked (Button *button)
    {
        if (table && table->display->displayType == Display::DisplayType::TEMPO)
        {
            if (button->getName() == b1.getName())
            {
                table->delayType =  (table->delayType == DelayType::NORMAL)     ?   DelayType::DOTTED
                :
                ((table->delayType == DelayType::DOTTED)    ?   DelayType::TRIPLET
                 :   DelayType::NORMAL);
                
                
                table->setTableType();
                
                b1.setButtonText(table->columnOneName);
                
                table->table.updateContent();
                
            }
            else if (button->getName() == b2.getName())
            {
                table->tempoConversion = (table->tempoConversion == TempoConversion::MS)    ?   TempoConversion::HZ
                :   TempoConversion::MS;
                
                
                table->setTableType();
                
                b2.setButtonText(table->columnTwoName);
                
                table->table.updateContent();
            }
            
            table->resized();
        }
    }
