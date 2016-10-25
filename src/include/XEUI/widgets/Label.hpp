#pragma once

//#include <SFGUI/Config.hpp>
#include <XEUI/Widget.hpp>
#include <XEUI/Misc.hpp>
#include <memory>
#include <SFML/System/String.hpp>


namespace XE {

	class Font;
	class WRectangle;
	class WCaption;

/** Text label.
 */
class  Label : public Widget, public Misc {
	public:
		typedef std::shared_ptr<Label> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Label> PtrConst; //!< Shared pointer.

		/** Create label.
		 * @param text Text.
		 * @return Label.
		 */
		static Ptr Create(WLayer& parentLayer, const sf::String& text = L"", Uint16 fontId = 14);

		virtual const std::string& GetName() const override;

		/** Set text.
		 * @param text New text.
		 */
		void SetText( const sf::String& text );

		/** Get text.
		 * @return Text.
		 */
		const sf::String& GetText() const;

		/** Enable or disable line wrapping of the text.
		 * Be sure to use a custom requisition in x direction when enabling this.
		 * @param wrap True to wrap text.
		 */
		void SetLineWrap( bool wrap );

		/** Check if line wrapping is enabled for this label.
		 * @return True when line wrapping is enabled.
		 */
		bool GetLineWrap() const;

		/** Get text after wrapping has been performed and newlines inserted.
		 * @return Wrapped text.
		 */
		sf::String GetWrappedText() const;


		void UpdateAlignment();

		Uint16 fontId;

	protected:
		/** Ctor.
		 * @param text Text.
		 */
		Label(WLayer& parentLayer, Uint16 fontId, const sf::String& text = "");

		//KH std::unique_ptr<RenderQueue>
		void draw() override;

		sf::Vector2f CalculateRequisition();
		//virtual void HandleRequisitionChange() override;
		//virtual void HandleSizeChange() override;

	private:



		void WrapText();

		sf::String m_text;
		sf::String m_wrapped_text;
		

		WRectangle* m_DebugRectangle;

		bool m_wrap;
		WCaption* m_wcaption;
};

}
