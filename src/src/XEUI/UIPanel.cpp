
#include <XEUI/UIPanel.hpp>

#include <XEUI/Widget.hpp>

#include <XEUI/UIManager.hpp>
#include <XERenderer/GUI/WLayer.hpp>
#include <XEUI/Desktop.hpp>
//#include <XEUI/widgets/Menu.hpp>
//#include <XEUI/widgets/Navigation.hpp>
//#include <XEUI/OgreConsoleForGorilla.h>
//#include <XEUI/Widgets/Button.hpp>
//#include <XEUI/Widgets/ListBox.hpp>
//#include <XEUI/widgets/ComboBox.hpp>
//#include <XEUI/widgets/Caption.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XEUI/DAL/FB_UI_StateData_generated.h> //need to include ... else link error

namespace XE {


using namespace std;

UIPanel::UIPanel( WLayer&  layer, const Ogre::uint16& grp)
	: //Widget(nullptr,""), mXEUI(gui), 
	//, mPosition(position) , mSize(size), 
	//  mMousePointer(NULL), mBackground(NULL)
//	m_guiRenderer(guiRenderer)
	 m_layer(layer)
	, m_DebugRectangle(layer, 0, 0, 0, 0)

{
}


UIPanel::~UIPanel()
{
//	mXEUI->destroyUIPanel(this);
}

void UIPanel::HandleAlignmentChange(const sf::Vector2f& old_alignment)
{

	HandlePositionChange();
}
void UIPanel::HandleAbsolutePositionChange()
{
	HandlePositionChange();
}

void UIPanel::setDesktop(std::shared_ptr<Desktop> desktopPtr)
{
	m_Desktop = desktopPtr;
}

void UIPanel::HandlePositionChange()
{
	//if (m_Desktop)
	//{
	//	//sf::FloatRect parentAllocation(m_Desktop->wi->GetAllocation());


	//	const sf::Vector2f& alignment = GetAlignment();
	//	auto newAlloc = GetAllocation(); //copy
	//	auto requistion = GetRequisition(); //copy
	//	
	//	//auto dektopWidth = GetParent().get m_guiRenderer.getLayerRenderer().getActualWidth();
	//	//auto dektopHeight = m_guiRenderer.getLayerRenderer().getActualHeight();

	///*	newAlloc.left = std::max(0.0f, std::min(dektopWidth - requistion.x, dektopWidth * alignment.x - newAlloc.width / 2));
	//	newAlloc.top = std::max(0.0f, std::min(dektopHeight - requistion.y, dektopHeight * alignment.y - newAlloc.height / 2));*/
	//	newAlloc.left = std::max(0.0f, std::min(m_Desktop->width - requistion.x, m_Desktop->width * alignment.x - newAlloc.width / 2));
	//	newAlloc.top = std::max(0.0f, std::min(m_Desktop->height - requistion.y, m_Desktop->height * alignment.y - newAlloc.height / 2));

	//	SetAllocation(newAlloc);
	//}

	//for (const auto& children : GetChildren()) 
	//{
	//	children->HandleAbsolutePositionChange();
	//	children->Invalidate();// HandleAbsolutePositionChange();

	//	/*requisition.x = std::max(requisition.x, child_position.second.x + child_position.first->GetRequisition().x);
	//	requisition.y = std::max(requisition.y, child_position.second.y + child_position.first->GetRequisition().y);*/
	//}

	//Invalidate();
}

UIPanel::Ptr UIPanel::Create( WLayer& layer) {
	Ptr panel(new UIPanel( layer));
	//label->RequestResize();

//	desktop->Add(panel);

	return panel;
}


void UIPanel::SetStyle(const char* menuElement, const  char* menuStyle)
{
	if (menuElement)
	{
		flatbuffers::GetRoot<XFB_UI::Panel2D>(menuElement);
	}


}
void UIPanel::draw() {


	//m_DebugRectangle.setBackgroundImage("item_ball_hover.png");
	////m_DebugRectangle.setBackground(Ogre::ColourValue::Blue);

	//auto& req = GetAllocation();
	//m_DebugRectangle.setPosition(sf::Vector2f(req.left, req.top));
	//m_DebugRectangle.setSize(sf::Vector2f(req.width, req.height));
	////m_Label.SetText(GetText());
	////return Context::Get().GetEngine().CreateLabelDrawable( std::dynamic_pointer_cast<const Label>( shared_from_this() ) );
}



void UIPanel::SetLabel(const sf::String& label) {
	m_label = label;
	//RequestResize();
	//Invalidate();
}

void UIPanel::HandleSizeChange()
{


}


void  UIPanel::HandleUpdate(float seconds)
{
	/*for each (auto& var in GetChildren())
	{
		var->Update(seconds);
	}*/
}

const sf::String& UIPanel::GetLabel() const {
	return m_label;
}


const std::string& UIPanel::GetName() const {
	static const std::string name("UIPanel");
	return name;
}

//sf::Vector2f UIPanel::CalculateRequisition() {
//
//	sf::Vector2f requisition(0.f, 0.f);
//
//	//// Find size needed to accomodate all widgets without overlapping any other widgets
//	//for (const auto& child_position : m_children_position_map) {
//	//	requisition.x = std::max(requisition.x, child_position.second.x + child_position.first->GetRequisition().x);
//	//	requisition.y = std::max(requisition.y, child_position.second.y + child_position.first->GetRequisition().y);
//	//}
//
//	return requisition;
//}


void UIPanel::Put(Widget::Ptr widget, const sf::Vector2f& position) {
	m_children_position_map[widget] = position;

	Container::Add(widget);
}

void UIPanel::Move(Widget::Ptr widget, const sf::Vector2f& position) {
	/*if (m_children_position_map.find(widget) != m_children_position_map.end()) {
		m_children_position_map[widget] = position;

		widget->SetAllocation(sf::FloatRect(position, widget->GetRequisition()));

		RequestResize();
	}*/
}


bool UIPanel::HandleAdd(Widget::Ptr child) {

	// If there's no position info present for the widget, the user added the widget
	// manually, which is not allowed for this class.
	if (m_children_position_map.find(child) == m_children_position_map.end()) {

#if defined( SFGUI_DEBUG )
		std::cerr << "SFGUI warning: Child must be added via Put() for sfg::Fixed widgets.\n";
#endif

		return false;
	}

	/*Container::HandleAdd(child);

	child->SetAllocation(sf::FloatRect(m_children_position_map[child], child->GetRequisition()));

	RequestResize();*/

	return true;
}

void UIPanel::HandleRemove(Widget::Ptr child) {
	m_children_position_map.erase(child);

//	RequestResize();
}


void UIPanel::selectOveredItem()
{
	//for (WidgetVector::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it)
	//	if ((*it)->getName() == mCurrentItemName)
	//		(*it)->selectOveredItem();
}

bool UIPanel::makeNextItemOver()
{
	//if (mCurrentItemName.empty())
	//	if (mWidgets.size() > 0)
	//		mCurrentItemName = mWidgets[0]->getName(); // set first Element as actual
	//	else
	//		return false; //no Elemets

	//for (WidgetVector::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it)
	//{
	//	if ((*it)->getName() == mCurrentItemName)
	//	{
	//		if ((*it)->makeNextItemOver()) //Current Element(Navigation,Menu ...) Next Item
	//			return true;
	//		else
	//		{
	//			++it;
	//			if (it != mWidgets.end())
	//			{
	//				mCurrentItemName = (*it)->getName();
	//				return (*it)->makeNextItemOver();  // Next Elemt First Item
	//			}
	//			else
	//				return false;
	//		}
	//	}
	//}

	return false;
}

bool UIPanel::makePrevItemOver()
{
	//if (mCurrentItemName.empty())
	//	if (mWidgets.size() > 0)
	//		mCurrentItemName = mWidgets[0]->getName(); // set first Element as actual
	//	else
	//		return false; //no Elemets

	//for (WidgetVector::iterator it = mWidgets.end(); it != mWidgets.begin();)
	//{
	//	--it;

	//	if ((*it)->getName() == mCurrentItemName)
	//	{
	//		if ((*it)->makePrevItemOver()) //Current Element(Navigation,Menu ...) Next Item
	//			return true;
	//		else
	//		{
	//			//	--it;
	//			if (it != mWidgets.begin())
	//			{
	//				mCurrentItemName = (*it)->getName();
	//				return (*it)->makePrevItemOver();  // Next Elemt First Item
	//			}
	//			else
	//				return false;
	//		}
	//	}
	//}

	return false;
}

} // namespace XE