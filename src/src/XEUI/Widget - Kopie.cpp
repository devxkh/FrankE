
#include <XEUI/Widget.hpp>

#include <XEUI/UIPanel.hpp>

namespace XE {

	// Signals.
	Signal::SignalID Widget::OnStateChange = 0;
	Signal::SignalID Widget::OnGainFocus = 0;
	Signal::SignalID Widget::OnLostFocus = 0;

	Signal::SignalID Widget::OnExpose = 0;

	Signal::SignalID Widget::OnSizeAllocate = 0;
	Signal::SignalID Widget::OnSizeRequest = 0;

	Signal::SignalID Widget::OnMouseEnter = 0;
	Signal::SignalID Widget::OnMouseLeave = 0;
	Signal::SignalID Widget::OnMouseMove = 0;
	Signal::SignalID Widget::OnMouseLeftPress = 0;
	Signal::SignalID Widget::OnMouseRightPress = 0;
	Signal::SignalID Widget::OnMouseLeftRelease = 0;
	Signal::SignalID Widget::OnMouseRightRelease = 0;

	Signal::SignalID Widget::OnLeftClick = 0;
	Signal::SignalID Widget::OnRightClick = 0;

	Signal::SignalID Widget::OnKeyPress = 0;
	Signal::SignalID Widget::OnKeyRelease = 0;
	Signal::SignalID Widget::OnText = 0;

	std::weak_ptr<Widget> Widget::m_focus_widget;
	std::weak_ptr<Widget> Widget::m_active_widget;
	std::weak_ptr<Widget> Widget::m_modal_widget;


	Widget::Widget(WLayer* parentLayer, const std::string& name)
		: mHasFocus(false)
		, mOvered(false)
		, mName(name)
		//, m_parent(parentLayer)
		, m_destroy(false)
		, m_size()
		, m_pos()
		, m_background(nullptr)
		, m_visible(true)
		, m_state(State::NORMAL)
		, m_invalidated(true)

	{

	}

	Widget::~Widget()
	{

		destroy();

		//if (!m_parent.lock()) {
		//	// If this widget is an orphan, we assume it is
		//	// a root widget and try to de-register it.
		//	std::vector<Widget*>::iterator iter(std::find(m_root_widgets.begin(), m_root_widgets.end(), this));

		//	if (iter != m_root_widgets.end()) {
		//		m_root_widgets.erase(iter);
		//	}
		//}

	}

	void Widget::setPosition(const Ogre::Vector3& pos)
	{
		m_pos = pos;
		if (m_background)
			m_background->setPosition(Ogre::Vector2(pos.x, pos.y));
	}

	void Widget::destroy()
	{
		m_enabled = false;
		m_visible = false;
		m_destroy = true;
	}

	bool Widget::getOvered()
	{
		return mOvered;
	}


	bool Widget::getFocus()
	{
		return mHasFocus;
	}
	
	void Widget::setFocus(bool hasFocus)
	{
		mHasFocus = hasFocus;
		_actualize();
	}


	void Widget::setOvered(bool overed)
	{
		mOvered = overed;
		_actualize();
	}


	void Widget::resetState()
	{
		mOvered = false;
		mHasFocus = false;
		_actualize();
	}

	void Widget::GrabFocus(Ptr widget) {
		// Notify old focused widget.
		if (m_focus_widget.lock()) {
			m_focus_widget.lock()->GetSignals().Emit(OnLostFocus);
			m_focus_widget.lock()->HandleFocusChange(widget);
		}

		m_focus_widget = widget;

		if (m_focus_widget.lock()) {
			m_focus_widget.lock()->GetSignals().Emit(OnGainFocus);
			m_focus_widget.lock()->HandleFocusChange(widget);
		}
	}

	bool Widget::HasFocus(PtrConst widget) {
		if (m_focus_widget.lock() == widget) {
			return true;
		}

		return false;
	}

	const Ogre::FloatRect& Widget::GetAllocation() const {
		return m_allocation;
	}

	void Widget::Update(float seconds) {
		if (m_invalidated) {
			m_invalidated = false;
			m_parent_notified = false;

		//	m_drawable = InvalidateImpl();
			//todo gui rendererer job!
			//if (m_drawable) {
			//	m_drawable->SetPosition(GetAbsolutePosition());
			//	m_drawable->SetLevel(m_hierarchy_level);
			//	m_drawable->SetZOrder(m_z_order);
			//	m_drawable->Show(IsGloballyVisible());

			//	// We don't want to propagate container viewports for Canvases,
			//	// they have their own special viewport for drawing.
			//	if (m_drawable->GetPrimitives().empty() || !m_drawable->GetPrimitives()[0]->GetCustomDrawCallback()) {
			//		m_drawable->SetViewport(m_viewport);
			//	}
			//}
		}

		HandleUpdate(seconds);
	}

	void Widget::Invalidate() const {
		if (!m_invalidated) {
			m_invalidated = true;
		}

		if (!m_parent_notified) {
			auto parent = m_parent.lock();

			if (parent) {
				m_parent_notified = true;

				parent->HandleChildInvalidate(static_cast<Widget::PtrConst>(shared_from_this()));
			}
		}
	}


	//std::unique_ptr<RenderQueue>
	void Widget::InvalidateImpl() const {
		//return nullptr;
	}



	void Widget::SetParent(Widget::Ptr parent) {
		auto cont = std::dynamic_pointer_cast<UIPanel>(parent);
		auto oldparent = m_parent.lock();

		if (cont == oldparent) {
			return;
		}

		if (oldparent) {
			oldparent->Remove(shared_from_this());
		}

		m_parent = cont;

		auto iter = std::find(m_root_widgets.begin(), m_root_widgets.end(), this);

		if (parent) {
			// If this widget has a parent, it is no longer a root widget.
			if (iter != m_root_widgets.end()) {
				m_root_widgets.erase(iter);
			}

		//	SetHierarchyLevel(parent->GetHierarchyLevel() + 1);
		}
		else {
			// If this widget does not have a parent, it becomes a root widget.
			if (iter == m_root_widgets.end()) {
				m_root_widgets.push_back(this);
			}

		//	SetHierarchyLevel(0);
		}

		//HandleAbsolutePositionChange();
	}
	
	void Widget::HandleEvent(const sf::Event& event) {
		//if (!IsGloballyVisible()) {
		//	return;
		//}

		// Ignore the event if widget is insensitive
		if (GetState() == State::INSENSITIVE) {
			return;
		}

		// Ignore the event if another widget is active.
		if (!IsActiveWidget() && !IsActiveWidget(PtrConst())) {
			return;
		}

		// Ignore the event if another widget is modal.
	/*	if (HasModal() && !IsModal()) {
			return;
		}*/

		// Set widget active in context.
		//Context::Get().SetActiveWidget(shared_from_this());

		auto parent = m_parent.lock();

		switch (event.type) {
		case sf::Event::MouseLeft:
			if (IsMouseInWidget()) {
				SetMouseInWidget(false);

				GetSignals().Emit(OnMouseLeave);
				HandleMouseLeave(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
			}

			HandleMouseMoveEvent(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());

			SetMouseButtonDown();
			HandleMouseButtonEvent(sf::Mouse::Left, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
			HandleMouseButtonEvent(sf::Mouse::Right, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::min());

			break;

		case sf::Event::MouseMoved:
			// Check if pointer inside of widget's allocation.
			if (GetAllocation().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
				// Check for enter event.
				if (!IsMouseInWidget()) {
					SetMouseInWidget(true);

					GetSignals().Emit(OnMouseEnter);
					HandleMouseEnter(event.mouseMove.x, event.mouseMove.y);
				}

				GetSignals().Emit(OnMouseMove);
			}
			else if (IsMouseInWidget()) { // Check for leave event.
				SetMouseInWidget(false);

				GetSignals().Emit(OnMouseLeave);
				HandleMouseLeave(event.mouseMove.x, event.mouseMove.y);
			}

			HandleMouseMoveEvent(event.mouseMove.x, event.mouseMove.y);
			break;

		case sf::Event::MouseButtonPressed:
			if (!IsMouseButtonDown() && IsMouseInWidget()) {
				SetMouseButtonDown(event.mouseButton.button);
			}

			HandleMouseButtonEvent(event.mouseButton.button, true, event.mouseButton.x, event.mouseButton.y);

			if (IsMouseInWidget()) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					GetSignals().Emit(OnMouseLeftPress);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					GetSignals().Emit(OnMouseRightPress);
				}
			}

			break;

		case sf::Event::MouseButtonReleased:
			// Only process as a click when mouse button has been pressed inside the widget before.
			if (IsMouseButtonDown(event.mouseButton.button)) {
				SetMouseButtonDown();

				// When released inside the widget, the event can be considered a click.
				if (IsMouseInWidget()) {
					HandleMouseClick(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);

					if (event.mouseButton.button == sf::Mouse::Left) {
						GetSignals().Emit(OnLeftClick);
					}
					else if (event.mouseButton.button == sf::Mouse::Right) {
						GetSignals().Emit(OnRightClick);
					}
				}
			}

			HandleMouseButtonEvent(event.mouseButton.button, false, event.mouseButton.x, event.mouseButton.y);

			if (IsMouseInWidget()) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					GetSignals().Emit(OnMouseLeftRelease);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					GetSignals().Emit(OnMouseRightRelease);
				}
			}

			break;

		case sf::Event::KeyPressed:
			if (HasFocus()) {
				// TODO: Delegate event too when widget's not active?
				HandleKeyEvent(event.key.code, true);
				GetSignals().Emit(OnKeyPress);
			}

			break;

		case sf::Event::KeyReleased:
			if (HasFocus()) {
				// TODO: Delegate event too when widget's not active?
				HandleKeyEvent(event.key.code, false);
				GetSignals().Emit(OnKeyRelease);
			}
			break;

		case sf::Event::TextEntered:
			if (HasFocus()) {
				// TODO: Delegate event too when widget's not active?
				HandleTextEvent(event.text.unicode);
				GetSignals().Emit(OnText);
			}
			break;

		default:
			break;
		}
	}

	void Widget::SetState(State state) {
		// Do nothing if state wouldn't change.
		if (GetState() == state) {
			return;
		}

		auto old_state = GetState();

		// Store the new state.
		m_state = state;

		// If HandleStateChange() changed the state, do not call observer, will be
		// done from there too.
		if (GetState() != old_state) {
			HandleStateChange(static_cast<State>(old_state));
			GetSignals().Emit(OnStateChange);
		}

		if (state == State::ACTIVE) {
			GrabFocus(shared_from_this());
			SetActiveWidget(shared_from_this());
		}
		else if (old_state == State::ACTIVE) {
			SetActiveWidget(Ptr());
		}
	}

	Widget::State Widget::GetState() const {
		return m_state;
	}

	Container::Ptr Widget::GetParent() {
		return m_parent.lock();
	}

	Container::PtrConst Widget::GetParent() const {
		return m_parent.lock();
	}

	void Widget::GrabFocus() {
		GrabFocus(shared_from_this());
	}

	bool Widget::HasFocus() const {
		return HasFocus(shared_from_this());
	}


	sf::Vector2f Widget::GetAbsolutePosition() const {
		// If no parent, allocation's position is absolute position.
		PtrConst parent(m_parent.lock());

		if (!parent) {
			return sf::Vector2f(GetAllocation().left, GetAllocation().top);
		}

		// Get parent's absolute position and add own rel. position to it.
		sf::Vector2f parent_position(parent->GetAbsolutePosition());

		return sf::Vector2f(
			parent_position.x + GetAllocation().left,
			parent_position.y + GetAllocation().top
			);
	}



	void Widget::SetId(const std::string& id) {
		if (id.empty()) {
			return;
		}

		if (!m_class_id) {
			m_class_id.reset(new ClassId);
		}

		m_class_id->id = id;

		Refresh();
	}

	std::string Widget::GetId() const {
		if (!m_class_id) {
			return "";
		}

		return m_class_id->id;
	}

	void Widget::SetClass(const std::string& cls) {
		if (cls.empty()) {
			return;
		}

		if (!m_class_id) {
			m_class_id.reset(new ClassId);
		}

		m_class_id->class_ = cls;

		Refresh();
	}

	std::string Widget::GetClass() const {
		if (!m_class_id) {
			return "";
		}

		return m_class_id->class_;
	}

	Widget::Ptr SearchContainerForId(Container::PtrConst container, const std::string& id) {
		if (!container) {
			return Widget::Ptr();
		}

		for (const auto& child : container->GetChildren()) {
			if (child->GetId() == id) {
				return child;
			}

			auto child_container = std::dynamic_pointer_cast<Container>(child);

			if (child_container) {
				auto widget = SearchContainerForId(child_container, id);

				if (widget) {
					return widget;
				}
			}
		}

		return Widget::Ptr();
	}

	Widget::Ptr Widget::GetWidgetById(const std::string& id) {
		for (const auto& root_widget : m_root_widgets) {
			if (root_widget->GetId() == id) {
				return root_widget->shared_from_this();
			}

			auto container = std::dynamic_pointer_cast<Container>(
				root_widget->shared_from_this()
				);

			if (container) {
				auto widget = SearchContainerForId(container, id);

				if (widget) {
					return widget;
				}
			}
		}

		return Widget::Ptr();
	}

	Widget::WidgetsList SearchContainerForClass(Container::PtrConst container, const std::string& class_name) {
		Widget::WidgetsList result;

		if (!container) {
			return result;
		}

		for (const auto& child : container->GetChildren()) {
			if (child->GetClass() == class_name) {
				result.push_back(child);
			}

			auto child_container = std::dynamic_pointer_cast<Container>(child);

			if (child_container) {
				auto child_result = SearchContainerForClass(child_container, class_name);

				// Splice the 2 vectors.
				if (!child_result.empty()) {
					result.reserve(child_result.size());
					result.insert(result.end(), child_result.begin(), child_result.end());
				}
			}
		}

		return result;
	}

	Widget::WidgetsList Widget::GetWidgetsByClass(const std::string& class_name) {
		WidgetsList result;

		for (const auto& root_widget : m_root_widgets) {
			if (root_widget->GetClass() == class_name) {
				result.push_back(root_widget->shared_from_this());
			}

			auto container = std::dynamic_pointer_cast<Container>(
				root_widget->shared_from_this()
				);

			if (container) {
				auto container_result = SearchContainerForClass(container, class_name);

				// Splice the 2 vectors.
				if (!container_result.empty()) {
					result.reserve(container_result.size());
					result.insert(result.end(), container_result.begin(), container_result.end());
				}
			}
		}

		return result;
	}

	void Widget::HandleFocusChange(Widget::Ptr focused_widget) {
		if ((focused_widget != shared_from_this()) && (GetState() == State::ACTIVE)) {
			SetState(State::NORMAL);
		}
	}


	void Widget::HandleUpdate(float /*seconds*/) {
	}


	void Widget::Refresh() {
		RequestResize();

		Invalidate();
	}


	void Widget::RefreshAll() {
		for (const auto& root_widget : m_root_widgets) {
			root_widget->Refresh();
		}
	}


	void Widget::SetActiveWidget() {
		SetActiveWidget(shared_from_this());
	}

	void Widget::SetActiveWidget(Ptr widget) {
		m_active_widget = widget;
	}

	bool Widget::IsActiveWidget() const {
		return IsActiveWidget(shared_from_this());
	}

	bool Widget::IsActiveWidget(PtrConst widget) {
		if (m_active_widget.lock() == widget) {
			return true;
		}

		return false;
	}

} // namespace XE