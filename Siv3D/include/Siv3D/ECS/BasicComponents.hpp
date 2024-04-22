#pragma once

# include "../Common.hpp"
# include "../Quaternion.hpp"

namespace s3d
{
	namespace ECS
	{
		struct TransformComponent
		{
			Vec3 position = Vec3::Zero();
			Quaternion rotation = Quaternion::Identity();
			Vec3 scale = Vec3::One();

			TransformComponent() = default;
			~TransformComponent() = default;

			TransformComponent(const Vec3& position, const Vec3& rotation, const Vec3& scale)
			{
				this->position = position;
				this->rotation = Quaternion::RollPitchYaw(rotation);
				this->scale = scale;
			}

			TransformComponent(const Vec3& position, const Quaternion& rotation, const Vec3& scale)
			{
				this->position = position;
				this->rotation = rotation;
				this->scale = scale;
			}
		};
	}
}