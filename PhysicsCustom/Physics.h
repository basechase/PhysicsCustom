#pragma once
#include "glm/glm.hpp"
#include "PhysObject.h"



    float ResolveCollision(const glm::vec2& PosA, const glm::vec2& VelA, float MassA,
        const glm::vec2& PosB, const glm::vec2& VelB, float MassB,
        float Elasticity, const glm::vec2& Normal);

    // Resolves a collision between two PhysObject instances
    void ResolvePhysObjects(PhysObject& Lhs, PhysObject& Rhs, float Elasticity, const glm::vec2& Normal, float Pen);

