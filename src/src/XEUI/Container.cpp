#include <XEUI/Container.hpp>

namespace XE {

	void Container::Add(Widget::Ptr widget) {
		if (IsChild(widget))
			return;

		m_children.push_back(widget);

		widget->SetParent(shared_from_this());
	}

	void Container::Remove(Widget::Ptr widget) {
		WidgetsList::iterator iter(std::find(m_children.begin(), m_children.end(), widget));

		if (iter != m_children.end()) {
			m_children.erase(iter);
			widget->SetParent(Widget::Ptr());
		}
	}

	void Container::RemoveAll() {
		while (!m_children.empty()) {
			auto widget = m_children.back();

			m_children.pop_back();
			widget->SetParent(Widget::Ptr());
		}
	}

	bool Container::IsChild(Widget::Ptr widget) const {
		return std::find(m_children.begin(), m_children.end(), widget) != m_children.end();
	}

	const Container::WidgetsList& Container::GetChildren() const {
		return m_children;
	}

	void Container::Refresh() {
		for (const auto& child : m_children) {
			child->Refresh();
		}

		Widget::Refresh();
	}

	void Container::HandleEvent(const sf::Event& event) {
		// Ignore event when widget is not visible.
		if (!IsGloballyVisible()) {
			return;
		}

		// Create a copy of the event and transform mouse coordinates to local
		// coordinates if event is a mouse event.
		/*sf::Event local_event(event);

		if (local_event.type == sf::Event::MouseMoved) {
			local_event.mouseMove.x -= static_cast<int>(getPosition().x);
			local_event.mouseMove.y -= static_cast<int>(getPosition().y);
		}

		if (
			local_event.type == sf::Event::MouseButtonPressed ||
			local_event.type == sf::Event::MouseButtonReleased
			) {
			local_event.mouseButton.x -= static_cast<int>(getPosition().x);
			local_event.mouseButton.y -= static_cast<int>(getPosition().y);
		}*/

		// Pass event to children.
		//dont use an iterator here! it's possible widget deletion happens while iterating here
		for (int index = 0; index < static_cast<int>(m_children.size()); ++index) {
			Widget::Ptr child(m_children[static_cast<std::size_t>(index)]);
			//for (const auto& child : m_children) {
			child->HandleEvent(event);
		}

		// Process event for own widget.
		Widget::HandleEvent(event);
	}
	
	void Container::HandleChildInvalidate(Widget::PtrConst child) const {
		auto parent = GetParent();

		if (parent) {
			parent->HandleChildInvalidate(child);
		}
	}
	

	void Container::HandleGlobalVisibilityChange() {
		Widget::HandleGlobalVisibilityChange();

		for (const auto& child : m_children) {
			child->HandleGlobalVisibilityChange();
		}
	}
}