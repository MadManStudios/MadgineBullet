#pragma once

#include "Madgine/scene/entity/entitycomponent.h"

#include "Meta/math/vector3.h"

class btSoftBody;

namespace Engine {
namespace Physics {

    struct MADGINE_BULLET_EXPORT SoftBodySkeleton : Scene::Entity::EntityComponent<SoftBodySkeleton> {
        SERIALIZABLEUNIT(SoftBodySkeleton)

        SoftBodySkeleton();
        SoftBodySkeleton(const SoftBodySkeleton& other);
        SoftBodySkeleton(SoftBodySkeleton &&other);
        ~SoftBodySkeleton();

        SoftBodySkeleton &operator=(SoftBodySkeleton &&other);
        SoftBodySkeleton& operator=(const SoftBodySkeleton &other);

        void init(Scene::Entity::Entity& entity);
        void finalize();

        void update();

        btSoftBody *get();
        void activate();

        void attach(RigidBody *rigidbody, size_t index, const Math::Vector3 &offset = Math::Vector3::ZERO);

        friend struct PhysicsManager;

    private:
        struct Data;
        std::unique_ptr<Data> mData;
    };

}
}