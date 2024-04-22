#pragma once

# include <memory>

# include <ThirdParty/entt/entt.hpp>

# include "BaseScene.hpp"

namespace s3d
{
	namespace ECS
	{
		class Entity
		{
		public:
			Entity(entt::entity entt = {})
				: m_entt(entt) {}

			template <typename Component, typename... Args>
			decltype(auto) addComponent(Registry& registry, Args &&...args)
			{
				return registry.emplace<Component>(m_entt, std::forward<Args>(args)...);
			}

			template <typename... Components>
			[[nodiscard]] decltype(auto) getComponent(Registry& registry)
			{
				return registry.get<Components...>(m_entt);
			}

			template <typename... Components>
			[[nodiscard]] decltype(auto) getComponent(const Registry& registry) const
			{
				return registry.get<Components...>(m_entt);
			}

			Entity& operator=(entt::entity rhs)
			{
				m_entt = rhs;
				return *this;
			}

		private:
			std::weak_ptr<BaseScene>
			entt::entity m_entt;
		};
	}
}