#pragma once

# include <ThirdParty/entt/entt.hpp>

namespace s3d
{
	namespace ECS
	{
		using Entity = entt::entity;

		class Registry
		{
		public:
			Entity create();

		private:
			entt::registry m_registry;
		};
	}
}

# include "detail/ECS.ipp"