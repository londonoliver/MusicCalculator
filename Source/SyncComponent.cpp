//
//  SyncComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/13/17.
//
//

#include "SyncComponent.hpp"

SyncComponent::SyncComponent()
{
    syncButton.setButtonText ("Manual");
    syncButton.setLookAndFeel (this);
    syncButton.setBoundsInset (BorderSize<int> (0));
    syncLabel.setText ("Sync", sendNotification);
    syncLabel.setLookAndFeel (this);
    syncLabel.setBorderSize (BorderSize<int> (0));
    addAndMakeVisible (syncButton);
    addAndMakeVisible (syncLabel);
}

SyncComponent::~SyncComponent()
{
}

void SyncComponent::paint(Graphics &g)
{
    g.fillAll (Colours::white.withAlpha(0.0f));
}

void SyncComponent::resized()
{
    int buttonWidth = getWidth() * 0.25;
    
    int buttonHeight = getHeight() * 0.75;
    syncLabel.setFont(Font (0.6f * (float) syncLabel.getHeight()));
    int margin = getWidth() * 0.02;
    int labelWidth = syncLabel.getFont().getStringWidth(syncLabel.getText());
    int labelHeight = buttonHeight;
    syncButton.setBounds (syncLabel.getX() + labelWidth + margin, (getHeight() - labelHeight)/2, buttonWidth, labelHeight);
    syncLabel.setBounds (0, (getHeight() - labelHeight)/2, labelWidth, labelHeight);
    syncButton.changeWidthToFitText();
}

Font SyncComponent::getTextButtonFont (TextButton &, int buttonHeight)
{
    return Font (0.6f * (float) buttonHeight);
}
