#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <XESystem/Entityx/entityx.h>

namespace XE {

	class EntityHolder
	{
	public:
		EntityHolder(entityx::Entity ent)
		{
			Entity = ent;
		}

		entityx::Entity Entity;
	};
} // ns XE


#endif // __NODE_HPP__