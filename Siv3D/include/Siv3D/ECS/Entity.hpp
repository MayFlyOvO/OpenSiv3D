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
			Entity() = default;

			Entity(std::weak_ptr<entt::registry> registry, entt::entity entt)
				: m_registry(registry), m_entt(entt) {}

			template <typename Component, typename... Args>
			decltype(auto) addComponent(Args &&...args)
			{
				return m_registry.lock()->emplace<Component>(m_entt, std::forward<Args>(args)...);
			}

			template <typename... Components>
			[[nodiscard]] decltype(auto) getComponent()
			{
				return m_registry.lock()->get<Components...>(m_entt);
			}

			template <typename... Components>
			[[nodiscard]] decltype(auto) getComponent() const
			{
				return m_registry.lock()->get<Components...>(m_entt);
			}
		private:
			std::weak_ptr<entt::registry> m_registry;
			entt::entity m_entt;
		};
	}
}