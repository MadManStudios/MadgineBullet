#pragma once

#include "Madgine/scene/entity/entitycomponent.h"

#include "Meta/math/vector3.h"

class btSoftBody;

namespace Engine {
namespace Physics {

    struct MADGINE_BULLET_EXPORT SoftBodySkeleton : Scene::Entity::EntityComponent<SoftBodySkeleton> {
        SERIALIZABLEUNIT(SoftBodySkeleton)

        SoftBodySkeleton(Scene::Entity::Entity &entity);
        SoftBodySkeleton(SoftBodySkeleton &&other);
        ~SoftBodySkeleton();

        SoftBodySkeleton &operator=(SoftBodySkeleton &&other);

        void init();
        void finalize();

        void update();

        btSoftBody *get();
        void activate();

        void attach(RigidBody *rigidbody, size_t index, const Engine::Vector3 &offset = Engine::Vector3::ZERO);

        friend struct PhysicsManager;

    private:
        struct Data;
        std::unique_ptr<Data> mData;
    };

}
}