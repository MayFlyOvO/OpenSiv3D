#pragma once

# include <memory>

# include "../Common.hpp"
# include "../SceneManager.hpp"

# include "BasicComponents.hpp"

namespace s3d {
	namespace ECS
	{
		using Registry = entt::registry;

		class Entity;

		template <class State, class Data = void>
		class BaseScene : public SceneManager<State, Data>::Scene, public std::enable_shared_from_this<BaseScene<State, Data>>
		{
		public:
			using InitData = SceneManager<State, Data>::Scene::InitData;
			using IScene = IScene<State, Data>;

			BaseScene(const InitData& init)
				: IScene{ init } {}

			virtual ~BaseScene() {};
		protected:
			[[nodiscard]] decltype(auto) createEntity()
			{
				Entity newEntity = m_registry.create();

				// Add TransformComponent by default
				newEntity.addComponent<TransformComponent>(m_registry);

				return newEntity;
			}

			[[nodiscard]] decltype(auto) getSharedPtr()
			{
				return this->shared_from_this();
			}

			[[nodiscard]] decltype(auto) getWeakPtr()
			{
				return this->weak_from_this();
			}

		protected:
			Registry m_registry;
		private:

		};
	}
}