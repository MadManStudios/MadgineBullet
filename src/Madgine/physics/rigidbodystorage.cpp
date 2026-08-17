#include "../bulletlib.h"

#include "rigidbodystorage.h"

#include "Madgine/scene/entity/entity.h"
#include "Madgine/scene/entity/components/transform.h"

#include "Meta/math/transformation.h"

#include "Meta/math/matrix4.h"

namespace Engine {
	namespace Scene {
		namespace Entity {

			void EntityComponentStorage<Physics::RigidBody>::setWorldTransform(const btTransform& transform)
			{
				assert(!isnan(transform.getOrigin().x()) && !isnan(transform.getOrigin().y()) && !isnan(transform.getOrigin().z()) &&
					!isnan(transform.getRotation().x()) && !isnan(transform.getRotation().y()) && !isnan(transform.getRotation().z()) && !isnan(transform.getRotation().w()));

				Transform* transformComponent = mEntity->getComponent<Transform>();

				Math::Matrix4 p = transformComponent->parentMatrix(entity());

				btQuaternion q = transform.getRotation();

				Math::Matrix4 m = p.Inverse() * TransformMatrix(Math::Vector3{ transform.getOrigin() }, Math::Vector3::UNIT_SCALE, Math::Quaternion{ q.x(), q.y(), q.z(), q.w() });

				std::tie(transformComponent->mPosition, transformComponent->mScale, transformComponent->mOrientation) = DecomposeTransformMatrix(m);

			}

			void EntityComponentStorage<Physics::RigidBody>::getWorldTransform(btTransform& transform) const
			{
				Transform* transformComponent = mEntity->getComponent<Transform>();

				Math::Matrix4 m = transformComponent->worldMatrix(entity());

				Math::Vector3 pos;
				Math::Vector3 scale;
				Math::Quaternion orientation;
				std::tie(pos, scale, orientation) = DecomposeTransformMatrix(m);

				assert(!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z) &&
					!isnan(orientation.x) && !isnan(orientation.y) && !isnan(orientation.z) && !isnan(orientation.z));

				transform = btTransform{ { orientation.x, orientation.y, orientation.z, orientation.w }, { pos.x, pos.y, pos.z } };
			}

		}
	}
}