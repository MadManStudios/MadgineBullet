#include "../bulletlib.h"

#include "rigidbodydata.h"

#include "Madgine/scene/entity/components/transform.h"

#include "Meta/math/transformation.h"

#include "physicsmanager.h"

namespace Engine {
namespace Physics {

    RigidBody::Data::Data(RigidBody *component)
        : mRigidBody(btRigidBody::btRigidBodyConstructionInfo { 0.0f, nullptr, nullptr, { 0.0f, 0.0f, 0.0f } })
    {        
        mRigidBody.setUserPointer(component);
        mRigidBody.setUserIndex(0);
    }

    uint16_t RigidBody::Data::collisionGroup() const
    {
        return mCollisionGroup;
    }

    void RigidBody::Data::setCollisionGroup(uint16_t group)
    {
        if (mRigidBody.getBroadphaseProxy())
            mRigidBody.getBroadphaseProxy()->m_collisionFilterGroup = group;
        mCollisionGroup = group;
    }

    uint16_t RigidBody::Data::collisionMask() const
    {
        return mCollisionMask;
    }

    void RigidBody::Data::setCollisionMask(uint16_t mask)
    {
        if (mRigidBody.getBroadphaseProxy())
            mRigidBody.getBroadphaseProxy()->m_collisionFilterMask = mask;
        mCollisionMask = mask;
    }

    void RigidBody::Data::add()
    {
        if (mMgr && mMgr->isInitialized() && mRigidBody.getCollisionShape() && !mRigidBody.getUserIndex()) {
            mMgr->world().addRigidBody(&mRigidBody, mCollisionGroup, mCollisionMask);
            mRigidBody.activate(true);
            mRigidBody.setUserIndex(1);
            mRigidBody.clearForces();
        }
    }

    void RigidBody::Data::remove()
    {
        if (mRigidBody.getUserIndex()) {
            mMgr->world().removeRigidBody(&mRigidBody);
            mRigidBody.setUserIndex(0);
        }
    }

}
}