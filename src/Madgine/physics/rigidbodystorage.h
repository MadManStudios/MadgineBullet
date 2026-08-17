#pragma once

#include "rigidbody.h"

#include "LinearMath/btMotionState.h"

#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

namespace Engine {
	namespace Physics {

		template <>
		struct Scene::Entity::EntityComponentStorage<RigidBody> : Scene::Entity::EntityComponentStorageImpl<RigidBody>, btMotionState {

			template <typename... Args>
			EntityComponentStorage(Scene::Entity::Entity& entity, Args &&... args)
				: Scene::Entity::EntityComponentStorageImpl<RigidBody>(entity, std::forward<Args>(args)...)
			{
				mComponent.get()->setMotionState(this);
			}

			void setWorldTransform(const btTransform& transform) override;
			void getWorldTransform(btTransform& transform) const override;


		};

	}
}