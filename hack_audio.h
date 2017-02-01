/*

BEGIN_JUCE_MODULE_DECLARATION

	ID:			  	hack_audio
	vendor:		  	HackAudio
	version:	  	0.1.0
	name:		  	HackAudio
	description:	Custom JUCE UI for HackAudio Plugins
	website:		http://www.hackaudio.com
	license:		MIT

END_JUCE_MODULE_DECLARATION

*/

#ifndef HACK_AUDIO_UI_INCLUDED
#define HACK_AUDIO_UI_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace HackAudio
{

    struct Colours
    {

        static const juce::Colour
        Black,
        Gray,
        White,
        Cyan;

    };

    class Slider;

    #include "components/hack_audio_Slider.h"

}

#endif
