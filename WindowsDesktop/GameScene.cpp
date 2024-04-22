#include "stdafx.h"
#include "GameScene.h"

#include "Components.h"

constexpr ColorF SKY_COLOR = { 0.7, 0.9, 1.0 };

GameScene::GameScene(const InitData& init)
	: BaseScene{ init }
{
	m_mainCamera = createEntity();
	{
		auto& transform = m_mainCamera.getComponent<ECS::TransformComponent>();
		transform.position = Vec3{ 10, 16, -32 };

		auto& rt = m_mainCamera.addComponent<TextureComponent>(
			std::make_shared<MSRenderTexture>(
				Scene::Size(),
				TextureFormat::R8G8B8A8_Unorm_SRGB,
				HasDepth::Yes
			)
		);

		auto& camera = m_mainCamera.addComponent<Camera3DComponent>(
			std::make_shared<DebugCamera3D>(
				Scene::Size(),
				30_deg,
				transform.position
			)
		);
	}

	m_ground = createEntity();
	{

	}

	m_player = createEntity();
	{

	}

	m_mirror = createEntity();
	{

	}
}

GameScene::~GameScene()
{
}

void GameScene::update()
{
	// Update main camera
	{
		auto mainCam = std::dynamic_pointer_cast<DebugCamera3D>(m_mainCamera.getComponent<Camera3DComponent>().camera3D);

		mainCam->update(2.0);
	}
}

void GameScene::draw() const
{
	auto mainCam = std::dynamic_pointer_cast<DebugCamera3D>(m_mainCamera.getComponent<Camera3DComponent>().camera3D);
	auto mainRT = std::dynamic_pointer_cast<MSRenderTexture>(m_mainCamera.getComponent<TextureComponent>().texture);

	{
		const ScopedRenderTarget3D target{ mainRT->clear(SKY_COLOR) };

		Graphics3D::SetCameraTransform(mainCam->getMat4x4(), mainCam->getEyePosition());


	}

	{
		Graphics3D::Flush();

		mainRT->resolve();

		Shader::LinearToScreen(*mainRT);
	}
}
