#ifndef HACK_AUDIO_NAVIGATIONBUTTON_H
#define HACK_AUDIO_NAVIGATIONBUTTON_H

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace HackAudio
{

class NavigationButton : public juce::Button
{
public:

    NavigationButton() : juce::Button("") { setWantsKeyboardFocus(false); }
    ~NavigationButton() {};

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    Direction buttonDirection = Left;

private:

    void mouseEnter(const juce::MouseEvent& e) override
    {

        if (isEnabled())
        {

            setMouseCursor(juce::MouseCursor::PointingHandCursor);
            
        }

        juce::Button::mouseEnter(e);

    }

    void mouseExit(const juce::MouseEvent& e) override
    {

        if (isEnabled())
        {

            setMouseCursor(juce::MouseCursor::NormalCursor);

        }

        juce::Button::mouseExit(e);
        
    }

    void enablementChanged() override
    {

        repaint();

    }

    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override
    {

        int width  = getWidth();
        int height = getHeight();

        juce::Button::ButtonState state = getState();

        if (state == juce::Button::ButtonState::buttonOver && state != juce::Button::ButtonState::buttonDown)
        {

            g.setColour(HackAudio::Colours::LightGray);

        }
        else if (state == juce::Button::ButtonState::buttonOver || state == juce::Button::ButtonState::buttonDown)
        {

            g.setColour(HackAudio::Colours::DarkGray);

        }
        else
        {

            g.setColour(HackAudio::Colours::White);

        }

        if (!isEnabled())
        {

            g.setColour(HackAudio::Colours::Black);

        }

        if (buttonDirection == Up)
        {

            g.drawLine((width/16), (height - height/4), (width/2), (height/4), 2);
            g.drawLine((width/2), (height/4), (width - width/16), (height - height/4), 2);

        }
        else if (buttonDirection == Down)
        {

            g.drawLine((width/16), (height/4), (width/2), (height - height/4), 2);
            g.drawLine((width/2), (height - height/4), (width - width/16), (height/4), 2);

        }
        else if (buttonDirection == Left)
        {

            g.drawLine((width/4), (height/2), (width - width/4), (height/16), 2);
            g.drawLine((width/4), (height/2), (width - width/4), (height - height/16), 2);

        }
        else if (buttonDirection == Right)
        {

            g.drawLine((width - width/4), (height/2), (width/4), (height/16), 2);
            g.drawLine((width - width/4), (height/2), (width/4), (height - height/16), 2);

        }

    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavigationButton)

};

}

#endif
