#pragma once

#include "rigidbody.h"

#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

namespace Engine {
namespace Physics {

    struct RigidBody::Data {
        Data(RigidBody *component);

        uint16_t collisionGroup() const;
        void setCollisionGroup(uint16_t group);

        uint16_t collisionMask() const;
        void setCollisionMask(uint16_t mask);

        void add();
        void remove();

        uint16_t mCollisionGroup = 2;
        uint16_t mCollisionMask = 65533;
        
        PhysicsManager *mMgr = nullptr;

        btRigidBody mRigidBody;
    };

}
}