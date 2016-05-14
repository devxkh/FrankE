////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_CONVERTEVENT_H
#define SFML_CONVERTEVENT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <sfml/Window/Event.hpp>
#include <XEEditor/Event/Event.h>


////////////////////////////////////////////////////////////
// Define a function to convert a sf::Event ot a sfEvent
////////////////////////////////////////////////////////////
inline const sf::Event& convertEvent(const sfEvent& event)
{
	sf::Event SFMLEvent;

    // Convert its type
	SFMLEvent.type = static_cast<sf::Event::EventType>(event.type);

    // Fill its fields
	switch (SFMLEvent.type)
    {
        case sfEvtResized :
			SFMLEvent.size.width = event.size.width;
			SFMLEvent.size.height = event.size.height;
            break;

        case sfEvtTextEntered :
			SFMLEvent.text.unicode = event.text.unicode;
            break;

        case sfEvtKeyReleased :
        case sfEvtKeyPressed :
			SFMLEvent.key.code = static_cast<sf::Keyboard::Key>(event.key.code);
			SFMLEvent.key.alt = event.key.alt ? sfTrue : sfFalse;
			SFMLEvent.key.control = event.key.control ? sfTrue : sfFalse;
			SFMLEvent.key.shift = event.key.shift ? sfTrue : sfFalse;
			SFMLEvent.key.system = event.key.system ? sfTrue : sfFalse;
            break;

        case sfEvtMouseWheelMoved :
			SFMLEvent.mouseWheel.delta = event.mouseWheel.delta;
			SFMLEvent.mouseWheel.x = event.mouseWheel.x;
			SFMLEvent.mouseWheel.y = event.mouseWheel.y;
            break;

        case sfEvtMouseButtonPressed :
        case sfEvtMouseButtonReleased :
			SFMLEvent.mouseButton.button = static_cast<sf::Mouse::Button>(event.mouseButton.button);
			SFMLEvent.mouseButton.x = event.mouseButton.x;
			SFMLEvent.mouseButton.y = event.mouseButton.y;
            break;

        case sfEvtMouseMoved :
			SFMLEvent.mouseMove.x = event.mouseMove.x;
			SFMLEvent.mouseMove.y = event.mouseMove.y;
            break;

      
        default :
            break;
    }

	return SFMLEvent;
}

#endif // SFML_CONVERTEVENT_H
