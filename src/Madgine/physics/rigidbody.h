#pragma once

#include "Madgine/scene/entity/entitycomponent.h"

#include "collisionshapemanager.h"

class btRigidBody;
class btMotionState;

namespace Engine {
namespace Physics {

    struct MADGINE_BULLET_EXPORT RigidBody : Scene::Entity::EntityComponent<RigidBody> {
        SERIALIZABLEUNIT(RigidBody)

        using Container = Containers::FreeListContainer<std::deque<Placeholder<0>>, Scene::Entity::EntityComponentFreeListConfig<Placeholder<0>>>;

        RigidBody();
        RigidBody(const RigidBody& other);
        RigidBody(RigidBody &&other);
        ~RigidBody();

        RigidBody& operator=(const RigidBody& other);
        RigidBody &operator=(RigidBody &&other);

        void init(Scene::Entity::Entity& entity);
        void finalize();

        void update();

        btRigidBody *get();
        const btRigidBody *get() const;
        void activate();
        
        float mass() const;
        void setMass(float mass);

        bool kinematic() const;
        void setKinematic(bool kinematic);

        bool ghost() const;
        void setGhost(bool ghost);

        float friction() const;
        void setFriction(float friction);

        Math::Vector3 linearFactor() const;
        void setLinearFactor(const Math::Vector3 &factor);

        Math::Vector3 angularFactor() const;
        void setAngularFactor(const Math::Vector3 &factor);

        Math::Vector3 angularVelocity() const;
        void setAngularVelocity(const Math::Vector3 &v);

        Math::Vector3 velocity() const;
        void setVelocity(const Math::Vector3 &v);

        void setOrientation(const Math::Quaternion &q);

        uint16_t collisionGroup() const;
        void setCollisionGroup(uint16_t group);

        uint16_t collisionMask() const;
        void setCollisionMask(uint16_t group);

        void setShape(typename CollisionShapeManager::Handle handle);
        void setShapeName(std::string_view name);
        CollisionShapeManager::Resource *getShape() const;
        CollisionShapeInstance *getShapeInstance() const;

        PhysicsManager *mgr() const;

        friend struct PhysicsManager;

    protected:
        typename CollisionShapeManager::InstanceHandle mShapeHandle;
        struct Data;
        std::unique_ptr<Data> mData;
    };

}
}