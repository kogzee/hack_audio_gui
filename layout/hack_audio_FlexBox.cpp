#include "hack_audio_FlexBox.h"

HackAudio::FlexBox::FlexBox()
{

    justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    flexBoxBounds.setBounds(0, 0, 0, 0);

    defaultFlexSettings.alignSelf = juce::FlexItem::AlignSelf::center;

    resizeGuard = false;

}

HackAudio::FlexBox::~FlexBox()
{

}

void HackAudio::FlexBox::setDefaultItem(juce::FlexItem item, bool updateExistingItems)
{
    defaultFlexSettings = item;

    if (updateExistingItems)
    {
        applyGlobalFlexItem(item);
    }

}

void HackAudio::FlexBox::addComponent(juce::Component* component, int customOrder)
{

    juce::FlexItem itemToAdd = defaultFlexSettings;
    itemToAdd.associatedComponent = component;
    itemToAdd.width  = component->getWidth();
    itemToAdd.height = component->getHeight();
    itemToAdd.order  = customOrder;
    items.add(itemToAdd);

    component->addComponentListener(this);

    applyLayout();

}

void HackAudio::FlexBox::removeComponent(juce::Component* component)
{
    for (int i = 0; i < items.size(); ++i)
    {
        juce::FlexItem& fi = items.getReference(i);

        if (fi.associatedComponent == component || !fi.associatedComponent)
        {
            items.remove(i);
        }
    }
}

void HackAudio::FlexBox::setDirection(juce::FlexBox::Direction newDirection)
{
    flexDirection = newDirection;
    applyLayout();
}

void HackAudio::FlexBox::setWrap(juce::FlexBox::Wrap newWrap)
{
    flexWrap = newWrap;
    applyLayout();
}

void HackAudio::FlexBox::setAlignContent(juce::FlexBox::AlignContent newAlignment)
{
    alignContent = newAlignment;
    applyLayout();
}

void HackAudio::FlexBox::setAlignItems(juce::FlexBox::AlignItems newAlignment)
{
    alignItems = newAlignment;
    applyLayout();
}

void HackAudio::FlexBox::setJustifyContent(juce::FlexBox::JustifyContent newJustification)
{
    justifyContent = newJustification;
    applyLayout();
}

void HackAudio::FlexBox::applyItemFlex(float newFlexGrow)
{
    for (int i = 0; i < items.size(); ++i)
    {
        items.getReference(i).flexGrow = newFlexGrow;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyItemFlex(float newFlexGrow, float newFlexShrink)
{
    for (int i = 0; i < items.size(); ++i)
    {
        items.getReference(i).flexGrow   = newFlexGrow;
        items.getReference(i).flexShrink = newFlexShrink;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyItemFlex(float newFlexGrow, float newFlexShrink, float newFlexBasis)
{
    for (int i = 0; i < items.size(); ++i)
    {
        items.getReference(i).flexGrow   = newFlexGrow;
        items.getReference(i).flexShrink = newFlexShrink;
        items.getReference(i).flexBasis  = newFlexBasis;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyItemWidth(float newWidth)
{
    for (int i = 0; i < items.size(); ++i)
    {
        items.getReference(i).width = newWidth;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyItemHeight(float newHeight)
{
    for (int i = 0; i < items.size(); ++i)
    {
        items.getReference(i).width = newHeight;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyItemMargin(juce::FlexItem::Margin newMargin)
{
    for (int i = 0; i < items.size(); ++i)
    {
        items.getReference(i).margin = newMargin;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyGlobalFlexItem(juce::FlexItem newFlexProperties)
{
    for (int i = 0; i < items.size(); ++i)
    {
        juce::Component * c = items[i].associatedComponent;
        items[i] = newFlexProperties;
        items.getReference(i).associatedComponent = c;
    }
    applyLayout();
}

void HackAudio::FlexBox::applyBounds(juce::Rectangle<int> bounds)
{
    flexBoxBounds = bounds;
    applyLayout();
}

void HackAudio::FlexBox::applyLayout()
{

    resizeGuard = true;
    performLayout(flexBoxBounds);
    resizeGuard = false;

}

void HackAudio::FlexBox::componentMovedOrResized(juce::Component &component, bool wasMoved, bool wasResized)
{

    if (resizeGuard) { return; }

    for (int i = 0; i < items.size(); ++i)
    {
        juce::FlexItem& fi = items.getReference(i);

        if (fi.associatedComponent == &component)
        {
            fi.width  = component.getWidth();
            fi.height = component.getHeight();
        }
    }

    applyLayout();

}

void HackAudio::FlexBox::componentVisibilityChanged(juce::Component &component)
{

    if (component.isVisible())
    {
        juce::FlexItem fi = defaultFlexSettings;

        fi.associatedComponent = &component;
        fi.width = component.getProperties().getWithDefault(juce::Identifier("flexWidthCache"), juce::var(0));
        fi.height = component.getProperties().getWithDefault(juce::Identifier("flexHeightCache"), juce::var(0));

        component.getProperties().remove(juce::Identifier("flexWidthCache"));
        component.getProperties().remove(juce::Identifier("flexHeightCache"));

        int index = component.getProperties().getWithDefault(juce::Identifier("flexIndexCache"), juce::var(0));
        items.insert(index, fi);
    }
    else
    {
        for (int i = 0; i < items.size(); ++i)
        {
            juce::FlexItem& fi = items.getReference(i);

            if (fi.associatedComponent == &component)
            {
                component.getProperties().set(juce::Identifier("flexIndexCache"), juce::var(i));
                component.getProperties().set(juce::Identifier("flexWidthCache"), juce::var(component.getWidth()));
                component.getProperties().set(juce::Identifier("flexHeightCache"), juce::var(component.getHeight()));

                items.remove(i);
            }
        }
    }

    applyLayout();

}
