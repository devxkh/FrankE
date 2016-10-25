#pragma once

#include <XESystem/SystemConfig.hpp>

#include <XEUI/Widget.hpp>
#include <XEUI/Misc.hpp>

//#include <SFML/Graphics/Image.hpp>

#include <memory>

namespace XE {

	struct SpriteData;
	class WRectangle;

	/** Image.
	*/
	class XE_API Image : public Widget, public Misc {
	public:
		typedef std::shared_ptr<Image> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Image> PtrConst; //!< Shared pointer.

													   /** Create image.
													   * @param image sf::Image.
													   * @return Image.
													   */
		static Ptr Create(WLayer& parentLayer, const std::string& imageName);

		const std::string& GetName() const override;

		/** Set associated sf::Image.
		* @param image New sf::Image.
		*/
		void SetImage(const std::string& imageName);

		/** Get associated sf::Image.
		* @return sf::Image.
		*/
		const std::string& GetImage() const;

	protected:
		/** Ctor.
		* @param image sf::Image.
		*/
		Image(WLayer& parentLayer, const std::string& imageName);

		void draw() override;
	//	sf::Vector2f CalculateRequisition();

	private:

		WRectangle* m_rectangle;
		std::string m_imageName;
		const SpriteData* m_sprite;
		//mutable sf::Vector2f m_texture_offset;
	};

}