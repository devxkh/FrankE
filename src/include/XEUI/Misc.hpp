#pragma once

//#include <SFGUI/Config.hpp>
#include <memory>
#include <SFML/System.hpp>

namespace XE {

/** Interface for all widgets with alignment.
 */
class  Misc {
	public:
		/** Dtor.
		 */
		virtual ~Misc() = default;

		/** Set alignment
		 * @param alignment Alignment (0..1 for x and y).
		 */
		void SetAlignment( const sf::Vector2f& alignment );

		/** Get alignment.
		 * @return Alignment.
		 */
		const sf::Vector2f& GetAlignment() const;

	protected:
		virtual void HandleAlignmentChange( const sf::Vector2f& old_alignment );

	private:
		sf::Vector2f m_alignment;
};

}
