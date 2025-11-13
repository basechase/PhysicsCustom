#include "Physics.h"

float ResolveCollision(const glm::vec2& PosA, const glm::vec2& VelA, float MassA, const glm::vec2& PosB, const glm::vec2& VelB, float MassB, float Elasticity, const glm::vec2& Normal)
{
    glm::vec2 RelVel = VelB - VelA;

    // calculate the impulse magnitude
    float ImpulseMag = glm::dot(-(1.0f + Elasticity) * RelVel, Normal) /
        glm::dot(Normal, Normal * (1 / MassA + 1 / MassB));

    // return impulse to apply to both objects
    return ImpulseMag;
}

void ResolvePhysObjects(PhysObject& Lhs, PhysObject& Rhs, float Elasticity, const glm::vec2& Normal, float Pen)
{
    // calculate resolution impulse
 //   normal and pen are passed by reference and will be updated
    float ImpulseMag = ResolveCollision(Lhs.Pos, Lhs.Velocity, Lhs.mass, Rhs.Pos, Rhs.Velocity, Rhs.mass, Elasticity, Normal);

    // depenetrate objects 
    glm::vec2 Mtv = Normal * Pen;
    Lhs.Pos -= Mtv;
    Rhs.Pos += Mtv;

    // TODO: don't bother applying impulses to static/kinematic objects

    // apply impulses to update velocity after collision
    // remember: apply an equal but opposite force to the other
    glm::vec2 Impulse = Normal * ImpulseMag;
    Lhs.AddImpulse(-Impulse);
    Rhs.AddImpulse(Impulse);
}
