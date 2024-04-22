#pragma once

# include <Siv3D.hpp>

# include <memory>

struct MeshComponent
{
	Mesh mesh;

	MeshComponent() = default;
	~MeshComponent() = default;

	MeshComponent(const Mesh& mesh)
	{
		this->mesh = mesh;
	}
};

struct Camera3DComponent
{
	std::shared_ptr<BasicCamera3D> camera3D;

	Camera3DComponent() = default;
	~Camera3DComponent() = default;

	Camera3DComponent(std::shared_ptr<BasicCamera3D> camera3D)
		: camera3D(camera3D) {}
};

struct TextureComponent
{
	std::shared_ptr<Texture> texture;

	TextureComponent() = default;
	~TextureComponent() = default;

	TextureComponent(std::shared_ptr<Texture> texture)
		: texture(texture) {}
};
