#pragma once

#include <XEUI/Bin.hpp>

#include <SFML/System/String.hpp>
#include <memory>

#include <XEUI/Widgets/Button.hpp>

#include <XERenderer/GUI/WRectangle.hpp>
#include <XERenderer/GUI/WCaption.hpp>

namespace XE {

	/** Toggle button.
	* A toggle button can be raised or depressed.
	*/
	class ToggleButton : public Button {
	public:
		typedef std::shared_ptr<ToggleButton> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const ToggleButton> PtrConst; //!< Shared pointer.

														/** Create button.
														* @param label Label.
														* @return Button.
														*/
		static Ptr Create(WLayer& parentLayer, const sf::String& label = L"");

		virtual ~ToggleButton();

		const std::string& GetName() const override;

		/** Set active.
		* @param active Active.
		*/
		void SetActive(bool active);

		/** Check if active.
		* @return true if active.
		*/
		bool IsActive() const;

		// Signals.
		static Signal::SignalID OnToggle; //!< Fired when toggled.

	protected:
		/** Ctor.
		*/
		ToggleButton(WLayer& parentLayer);// = default;

		void draw() override;

		void HandleMouseButtonEvent(bool press, int x, int y) override;
		
	private:

		bool m_active;
	};

}