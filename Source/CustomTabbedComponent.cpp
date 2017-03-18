//
//  CustomTabbedComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#include "CustomTabbedComponent.h"
//#include "CustomLookAndFeel.cpp"

using namespace std;

CustomTabbedComponent::CustomTabbedComponent() : TabbedComponent (TabbedButtonBar::TabsAtTop)
{
    //setDefaultLookAndFeel (this);
    
    addTab ("Tempo", Colours::white, &tcc, true);
    addTab ("Note", Colours::white, &ncc, true);
    
    setOutline (0);
    
    ScopedPointer<XmlElement> svg1 (XmlDocument::parse(BinaryData::metronome_svg));
    if (svg1 != nullptr)
    {
        metronome = Drawable::createFromSVG (*svg1);
    }
    
    ScopedPointer<XmlElement> svg2 (XmlDocument::parse(BinaryData::note_svg));
    if (svg2 != nullptr)
    {
        note = Drawable::createFromSVG (*svg2);
    }
    
    //addAndMakeVisible (tcc.syncComponent);
}

CustomTabbedComponent::~CustomTabbedComponent()
{
}

void CustomTabbedComponent::paint(Graphics &g)
{
    g.setColour(Colours::white);
    Rectangle<int> r (0, 0, getWidth(), getHeight());
    const float cornerSize = getHeight() * 0.01;
    
    Path outline;
    outline.addRoundedRectangle (r.getX(), r.getY(), r.getWidth(), r.getHeight(), cornerSize, cornerSize, true, true, true, true);
    
    g.fillPath(outline);
}

void CustomTabbedComponent::resized()
{
    /*Rectangle<int> content (getLocalBounds());
    BorderSize<int> outline (1);
    
    tabs->setBounds (getTabArea (content, outline, getOrientation(), getTabBarDepth()));
    content = BorderSize<int> (0).subtractedFrom (outline.subtractedFrom (content));*/
    
    int margin = (0.025 * getHeight());
    
    int tabsWidth = getTabBarDepth() * 2;
    tabs->setBounds(0, 0, tabsWidth, getTabBarDepth());
    int syncWidth = getWidth() - tabsWidth;
    
    tcc.syncComponent.setBounds(tabsWidth, 0, syncWidth, getTabBarDepth());
    
    BorderSize<int> inset (0.05 * getWidth());
    inset.setTop(getTabBarDepth());
    tcc.setBoundsInset(inset);
    ncc.setBoundsInset(inset);
}

Rectangle<int> CustomTabbedComponent::getTabArea (Rectangle<int>& content, BorderSize<int>& outline,
                                  const TabbedButtonBar::Orientation orientation, const int tabDepth)
{
    switch (orientation)
    {
        case TabbedButtonBar::TabsAtTop:    outline.setTop (0);     return content.removeFromTop (tabDepth);
        case TabbedButtonBar::TabsAtBottom: outline.setBottom (0);  return content.removeFromBottom (tabDepth);
        case TabbedButtonBar::TabsAtLeft:   outline.setLeft (0);    return content.removeFromLeft (tabDepth);
        case TabbedButtonBar::TabsAtRight:  outline.setRight (0);   return content.removeFromRight (tabDepth);
        default: jassertfalse; break;
    }
    
    return Rectangle<int>();
}

int CustomTabbedComponent::getTabButtonBestWidth (TabBarButton& button, int tabDepth)
{
    return tabDepth;
}

void CustomTabbedComponent::drawTabButton(TabBarButton &button, Graphics &g, bool isMouseOver, bool isMouseDown)
{
    const Rectangle<int> activeArea (button.getActiveArea());
    
    const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
    
    const Colour bkg (button.getTabBackgroundColour());
    
    if (button.getToggleState())
    {
        g.setColour (bkg);
    }
    else
    {
        Point<int> p1, p2;
        
        switch (o)
        {
            case TabbedButtonBar::TabsAtBottom:   p1 = activeArea.getBottomLeft(); p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtTop:      p1 = activeArea.getTopLeft();    p2 = activeArea.getBottomLeft(); break;
            case TabbedButtonBar::TabsAtRight:    p1 = activeArea.getTopRight();   p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtLeft:     p1 = activeArea.getTopLeft();    p2 = activeArea.getTopRight();   break;
            default:                              jassertfalse; break;
        }
        
        g.setGradientFill (ColourGradient (bkg.brighter (0.2f), (float) p1.x, (float) p1.y,
                                           bkg.darker (0.1f),   (float) p2.x, (float) p2.y, false));
    }
    
    const float cornerSize = getHeight() * 0.01;
    
    Path outline;
    outline.addRoundedRectangle (activeArea.getX(), activeArea.getY(), activeArea.getWidth(), activeArea.getHeight(), cornerSize, cornerSize, true, true, false, false);
    
    g.fillPath(outline);
    
    //g.fillRoundedRectangle (activeArea.toFloat(), 0.0f);
    
    //g.fillRect (activeArea);
    
    g.setColour (button.findColour (TabbedButtonBar::tabOutlineColourId));
    
    Rectangle<int> r (activeArea);
    
    //if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect (r.removeFromTop (1));
    //if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
    //if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
    //if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));
    
    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
    
    Colour col (bkg.contrasting().withMultipliedAlpha (alpha));
    
    const Rectangle<float> area (button.getTextArea().toFloat());
    
    float length = area.getWidth();
    float depth  = area.getHeight();
    
    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);
    
    TextLayout textLayout;
    createTabTextLayout (button, length, depth, col, textLayout);
    
    AffineTransform t;
    
    switch (o)
    {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }
    
    //g.addTransform (t);
    float reduced = 0.2f;
    
    if (button.getIndex() == 0 && metronome)
        metronome->drawWithin(g, activeArea.toFloat().reduced(activeArea.getHeight() * reduced), RectanglePlacement::centred, 1.0f);
    else if (button.getIndex() == 1 && note)
        note->drawWithin(g, activeArea.toFloat().reduced(activeArea.getHeight() * reduced), RectanglePlacement::centred, 1.0f);

}

void CustomTabbedComponent::drawTabAreaBehindFrontButton (TabbedButtonBar &, Graphics &, int w, int h)
{
}

int CustomTabbedComponent::getTabButtonOverlap (int tabDepth)
{
    return 0;
}
