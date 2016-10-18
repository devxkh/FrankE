#pragma once

#include <XEUI/Bin.hpp>
#include <XEUI/Widgets/ToggleButton.hpp>

namespace XE {

	/** Check button.
	*/
	class CheckButton : public ToggleButton {
	public:
		typedef std::shared_ptr<CheckButton> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const CheckButton> PtrConst; //!< Shared pointer.

														/** Create button.
														* @param label Label.
														* @return Button.
														*/
		static Ptr Create(WLayer& parentLayer, const sf::String& label = L"", Uint16 fontId = 14);

		virtual ~CheckButton();

		const std::string& GetName() const override;
		
	protected:
		/** Ctor.
		*/
		CheckButton(WLayer& parentLayer, Uint16 fontId);// = default;

		void draw() override;
		

		WRectangle m_checkedRectangle;
	};

}