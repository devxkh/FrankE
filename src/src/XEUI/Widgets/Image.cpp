#include <XEUI/Widgets/Image.hpp>


#include <XEUI/Container.hpp>

#include <XERenderer/GUI/GUIRenderer.hpp> //includes sprite data struct

#include <XERenderer/GUI/WLayer.hpp>
#include <XERenderer/GUI/WScreen.hpp>
//#include <SFGUI/Context.hpp>
//#include <SFGUI/Engine.hpp>
//#include <SFGUI/Renderer.hpp>
//#include <SFGUI/RenderQueue.hpp>
//#include <SFGUI/Primitive.hpp>
//#include <SFGUI/PrimitiveTexture.hpp>

//#include <SFML/Graphics/Image.hpp>

namespace XE {

	Image::Image(WLayer& parentLayer, const std::string& imageName)
		: m_rectangle(parentLayer, 0, 0, 0, 0)
		, m_imageName(imageName)
		, m_sprite(0)
	{
		SetAlignment(sf::Vector2f(.5f, .5f));
		SetImage(imageName);
	}

	Image::Ptr Image::Create(WLayer& parentLayer, const std::string& imageName) {
		return Ptr(new Image(parentLayer, imageName));
	}

	void Image::SetImage(const std::string& imageName) {
		
		m_sprite = m_rectangle.setBackgroundImage(imageName);

		m_imageName = imageName;


		//if (image->width || !image->height) {
		//	return;
		//}

		//if (m_image.getSize() == image.getSize()) {
		//	m_image = image;

		//	sfg::Renderer::Get().UpdateImage(m_texture_offset, image);
		//}
		//else {
		//	m_image = image;

			//RequestResize();
			draw();
	//	}
	}

	//const sf::Image& Image::GetImage() const {
	//	return m_image;
	//}

	void Image::draw()  {

	/*	sf::FloatRect req(GetAllocation());
		sf::FloatRect parentAllocation(GetParent()->GetAllocation());*/

		m_rectangle.setPosition(Widget::getPosition()); // sf::Vector2f(parentAllocation.left + req.left, parentAllocation.top + req.top));
		m_rectangle.setSize(sf::Vector2f(size.x, size.y));

		//std::unique_ptr<RenderQueue> queue = Context::Get().GetEngine().CreateImageDrawable(std::dynamic_pointer_cast<const Image>(shared_from_this()));

	//	m_texture_offset = queue->GetPrimitives()[0]->GetTextures()[0]->offset;

	//	return queue;
	}

	//sf::Vector2f Image::CalculateRequisition() {
	//	
	//	if (m_sprite)
	//		return sf::Vector2f(static_cast<float>(m_sprite->spriteWidth), static_cast<float>(m_sprite->spriteHeight));
	//	else
	//		return sf::Vector2f(0, 0);
	//}

	const std::string& Image::GetName() const {
		static const std::string name("Image");
		return name;
	}

}