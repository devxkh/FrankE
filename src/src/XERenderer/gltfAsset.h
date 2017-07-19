#ifndef glTFAsset_H_INC
#define glTFAsset_H_INC

#include <map>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>

namespace XE
{

	//! Values for the mesh primitive modes
	enum PrimitiveMode
	{
		PrimitiveMode_POINTS = 0,
		PrimitiveMode_LINES = 1,
		PrimitiveMode_LINE_LOOP = 2,
		PrimitiveMode_LINE_STRIP = 3,
		PrimitiveMode_TRIANGLES = 4,
		PrimitiveMode_TRIANGLE_STRIP = 5,
		PrimitiveMode_TRIANGLE_FAN = 6
	};
		
	class Asset
	{
	
	public:

		void load(const std::string& input_filename);

	private:
	
	};

}

#endif
