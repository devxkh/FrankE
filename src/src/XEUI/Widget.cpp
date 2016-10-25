#include <XEUI/Widget.hpp>
#include <XEUI/Container.hpp>
//#include <SFGUI/Renderer.hpp>
//#include <SFGUI/RendererViewport.hpp>
//#include <SFGUI/Context.hpp>
#include <cmath>
#include <limits>

//#include <iostream>

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

	Signal::SignalID Widget::OnNav = 0;
	Signal::SignalID Widget::OnNavSelect = 0;
	Signal::SignalID Widget::OnNavEnter = 0;

	std::weak_ptr<Widget> Widget::m_focus_widget;
	std::weak_ptr<Widget> Widget::m_active_widget;
	std::weak_ptr<Widget> Widget::m_modal_widget;

	std::vector<Widget*> Widget::m_root_widgets;

	Widget::Widget() :
		m_z_order(0),
		m_state(State::NORMAL),
		m_mouse_button_down(false),
		m_mouse_in(false),
		m_visible(true)
	{
		// Register this as a root widget initially.
		m_root_widgets.push_back(this);
	}

	Widget::~Widget() {
		if (!m_parent.lock()) {
			// If this widget is an orphan, we assume it is
			// a root widget and try to de-register it.
			std::vector<Widget*>::iterator iter(std::find(m_root_widgets.begin(), m_root_widgets.end(), this));

			if (iter != m_root_widgets.end()) {
				m_root_widgets.erase(iter);
			}
		}
	}


	const sf::Vector2f& Widget::getPosition() const
	{ 
		return m_position; 
	}

	void Widget::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos; 

		draw();
	}

	bool Widget::IsLocallyVisible() const {
		return m_visible;
	}

	bool Widget::IsGloballyVisible() const {
		// If not locally visible, also cannot be globally visible.
		if (!IsLocallyVisible()) {
			return false;
		}

		// At this point we know the widget is locally visible.

		PtrConst parent(m_parent.lock());

		// If locally visible and no parent, globally visible.
		if (!parent) {
			return true;
		}

		// Return parent's global visibility.
		return parent->IsGloballyVisible();
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
	
	void Widget::ParentPositionChanged()
	{

	}

	void Widget::draw() {
		//KH return nullptr;
	}

	void Widget::SetParent(Widget::Ptr parent) {
		auto cont = std::dynamic_pointer_cast<Container>(parent);
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

			//SetHierarchyLevel(parent->GetHierarchyLevel() + 1);
		}
		else {
			// If this widget does not have a parent, it becomes a root widget.
			if (iter == m_root_widgets.end()) {
				m_root_widgets.push_back(this);
			}

		//	SetHierarchyLevel(0);
		}

	}

	void Widget::HandleUpdate(float /*seconds*/) {

	}

	bool Widget::HandleEvent() {

	//	std::cout << "-----IsGloballyVisible! " << IsGloballyVisible() << std::endl;

		if (!IsGloballyVisible()) {
			return false;
		}

	//	std::cout << "-----GetState! " << std::endl;
		
		// Ignore the event if widget is insensitive
		if (GetState() == State::INSENSITIVE) {
			return false;
		}

	//	std::cout << "-----IsActiveWidget! " << std::endl;
		
		// Ignore the event if another widget is active.
		if (!IsActiveWidget() && !IsActiveWidget(PtrConst())) {
			return false;
		}

	//	std::cout << "-----HasModal! " << std::endl;
		
		// Ignore the event if another widget is modal.
		if (HasModal() && !IsModal()) {
			return false;
		}
	
	//	std::cout << "-----ok! " << std::endl;

		auto parent = m_parent.lock();

	/*	switch (event.type) {
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
*/
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

	bool Widget::IsMouseInWidget() const {
		return m_mouse_in;
	}

	void Widget::SetMouseInWidget(bool in_widget) {
		m_mouse_in = in_widget;
	}

	//bool Widget::IsMouseButtonDown(sf::Mouse::Button button) const {
	//	// Check if any button is down if requested.
	//	if (button == sf::Mouse::ButtonCount) {
	//		return m_mouse_button_down != sf::Mouse::ButtonCount;
	//	}

	//	// Check if requested button is down.
	//	return m_mouse_button_down == button;
	//}

	//void Widget::SetMouseButtonDown(sf::Mouse::Button button) {
	//	m_mouse_button_down = static_cast<unsigned char>(button & 0x3f); // 6 bits
	//}

	void Widget::Show(bool show) {
		if (show == IsLocallyVisible()) {
			return;
		}

		auto old_global_visibility = IsGloballyVisible();

		// Flip the visible bit since we know show != IsLocallyVisible()
		m_visible = !m_visible;

		HandleLocalVisibilityChange();

		if (old_global_visibility != IsGloballyVisible()) {
			HandleGlobalVisibilityChange();
		}
	}
	
	void  Widget::Update(float seconds)
	{
	}

	void Widget::UpdateDrawablePosition() {
		//infinity loop !! dont do this here		//SetPosition(GetAbsolutePosition()) ;


		//KH if( m_drawable ) {
		//KH 	m_drawable->SetPosition( GetAbsolutePosition() );
		//KH }
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


	void Widget::HandleMouseMoveEvent(int x, int y) {
	}

	void Widget::HandleMouseButtonEvent(bool press, int x, int y) {
	}

	void Widget::HandleKeyEvent(const SDL_KeyboardEvent& key, bool press) {
	}

	void Widget::HandleMouseClick(int x, int y) {

	}

	void Widget::onPointMoved(const float& x, const float& y) {
		
	//	std::cout << "-----start.onPointMoved! " << x << std::endl;

		if (!HandleEvent())
			return;

		SDL_Rect rec{ Widget::getPosition().x,Widget::getPosition().y , size.x,size.y };
		SDL_Point point{x,y};

	//	std::cout << "SDL_Point.onPointMoved! " << x << std::endl;

		// Check if pointer inside of widget's allocation.
		if (SDL_PointInRect(&point, &rec)) {
			
	//		std::cout << "SDL_PointInRect.onPointMoved! " << x << std::endl;

			// Check for enter event.
			if (!IsMouseInWidget()) {

		//		std::cout << "!IsMouseInWidget.onPointMoved! " << x << std::endl;
				
				SetMouseInWidget(true);

				GetSignals().Emit(OnMouseEnter);
				HandleMouseEnter(x, y);
			}

			GetSignals().Emit(OnMouseMove);
		}
		else if (IsMouseInWidget()) { // Check for leave event.
			SetMouseInWidget(false);

			GetSignals().Emit(OnMouseLeave);
			HandleMouseLeave(x, y);
		}

		HandleMouseMoveEvent(x, y);
	}

	void Widget::onPointDown(const float& x, const float& y) {
		
		if (!HandleEvent())
			return;

		/*if (!IsMouseButtonDown() && IsMouseInWidget()) {
			SetMouseButtonDown(event.mouseButton.button);
		}*/

		//HandleMouseButtonEvent(event.mouseButton.button, true, event.mouseButton.x, event.mouseButton.y);
		HandleMouseButtonEvent(true, x, y);

		if (IsMouseInWidget()) {
			//if (event.mouseButton.button == sf::Mouse::Left) {
				GetSignals().Emit(OnMouseLeftPress);
		//	}
		/*	else if (event.mouseButton.button == sf::Mouse::Right) {
				GetSignals().Emit(OnMouseRightPress);
			}*/
		}


	}
	void Widget::onPointUp(const float& x, const float& y) {
		if (!HandleEvent())
			return;

		// Only process as a click when mouse button has been pressed inside the widget before.
		/*if (IsMouseButtonDown(event.mouseButton.button)) {
			SetMouseButtonDown();*/

			// When released inside the widget, the event can be considered a click.
			if (IsMouseInWidget()) {
				HandleMouseClick(x, y);

				//if (event.mouseButton.button == sf::Mouse::Left) {
					GetSignals().Emit(OnLeftClick);
				/*}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					GetSignals().Emit(OnRightClick);
				}*/
			}
	//	}

		HandleMouseButtonEvent(false, x, y);

		if (IsMouseInWidget()) {
		//	if (event.mouseButton.button == sf::Mouse::Left) {
				GetSignals().Emit(OnMouseLeftRelease);
			/*}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				GetSignals().Emit(OnMouseRightRelease);
			}*/
		}
	}
	
	void Widget::onKeyEvent(const SDL_KeyboardEvent& key) {
		if (!HandleEvent())
			return;

		switch(key.type){
		case SDL_KEYDOWN:
			if (HasFocus()) {
				// TODO: Delegate event too when widget's not active?
				HandleKeyEvent(key, true);
				GetSignals().Emit(OnKeyPress);
			}

			break;

		case SDL_KEYUP:
			if (HasFocus()) {
				// TODO: Delegate event too when widget's not active?
				HandleKeyEvent(key, false);
				GetSignals().Emit(OnKeyRelease);
			}
			break;

		default:
			break;
		}
	}

	void Widget::onTextEvent(const SDL_TextInputEvent& text) {
		if (!HandleEvent())
			return;

			if (HasFocus()) {
				// TODO: Delegate event too when widget's not active?
				HandleTextEvent(text.text);// event.text.unicode);
				GetSignals().Emit(OnText);
			}	
	}

	void Widget::onNav(NavAction navAction)
	{
		if (!HandleEvent())
			return;

		HandleNavEvent(navAction);
		GetSignals().Emit(OnNav);
	}

	void  Widget::HandleNavEvent(NavAction navAction)
	{

	}

	//void Widget::HandleMouseButtonEvent(sf::Mouse::Button /*button*/, bool /*press*/, int /*x*/, int /*y*/) {
	//}

	//void Widget::HandleKeyEvent(sf::Keyboard::Key /*key*/, bool /*press*/) {
	//}
	
	void Widget::HandleStateChange(State /*old_state*/) {
		
	}

	void Widget::HandleTextEvent(const char* /*character*/) {
	}

	void Widget::HandleMouseEnter(int /*x*/, int /*y*/) {
	}

	void Widget::HandleMouseLeave(int /*x*/, int /*y*/) {
	}

	//void Widget::HandleMouseClick(sf::Mouse::Button /*button*/, int /*x*/, int /*y*/) {
	//}

	void Widget::HandleFocusChange(Widget::Ptr focused_widget) {
		if ((focused_widget != shared_from_this()) && (GetState() == State::ACTIVE)) {
			SetState(State::NORMAL);
		}
	}

	void Widget::HandleLocalVisibilityChange() {
	}

	void Widget::HandleGlobalVisibilityChange() {
		auto state = GetState();

		if ((state == State::PRELIGHT) || (state == State::ACTIVE)) {
			SetState(State::NORMAL);
		}

		m_shapesContainer.Show( IsGloballyVisible() );
	}
	
	void Widget::Refresh() {
		/*RequestResize();

		Invalidate();*/
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

	void Widget::GrabModal() {
		if (m_modal_widget.lock()) {
#if defined( SFGUI_DEBUG )
			std::cerr << "SFGUI warning: Tried to grab modal while existing widget has it.\n";
#endif

			return;
		}

		m_modal_widget = shared_from_this();
	}

	void Widget::ReleaseModal() {
		if (m_modal_widget.lock() == shared_from_this()) {
			m_modal_widget.reset();

			return;
		}

#if defined( SFGUI_DEBUG )
		std::cerr << "SFGUI warning: Tried to release modal although current widget not modal.\n";
#endif
	}

	bool Widget::IsModal() const {
		if (m_modal_widget.lock() == shared_from_this()) {
			return true;
		}

		return false;
	}

	bool Widget::HasModal() {
		return !m_modal_widget.expired();
	}

	const std::vector<Widget*>& Widget::GetRootWidgets() {
		return m_root_widgets;
	}

}
