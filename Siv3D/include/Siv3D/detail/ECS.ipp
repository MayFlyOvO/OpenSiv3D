# pragma once

namespace s3d
{
	inline ECS::Entity ECS::Registry::create()
	{
		return m_registry.create();
	}
}