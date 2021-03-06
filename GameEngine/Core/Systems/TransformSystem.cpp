//
//  TransformSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 25/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "TransformSystem.h"
#include "Transform.h"
#include <glm/gtx/transform.hpp>

#include <iomanip>
#include <set>

using namespace entityx;
using namespace glm;

void logMat4(mat4& mat) {
    std::cout << "<mat4> " << &mat << std::endl;
    std::cout << std::fixed << std::setprecision(1) << " " << (mat[0][0] < 0.0f ? "" : " ") << mat[0][0] << " " << (mat[0][1] < 0.0f ? "" : " ") << mat[0][1] << " " << (mat[0][2] < 0.0f ? "" : " ") << mat[0][2] << " " << (mat[0][3] < 0.0f ? "" : " ") << mat[0][3] << std::endl;
    std::cout << std::fixed << std::setprecision(1) << " " << (mat[1][0] < 0.0f ? "" : " ") << mat[1][0] << " " << (mat[1][1] < 0.0f ? "" : " ") << mat[1][1] << " " << (mat[1][2] < 0.0f ? "" : " ") << mat[1][2] << " " << (mat[1][3] < 0.0f ? "" : " ") << mat[1][3] << std::endl;
    std::cout << std::fixed << std::setprecision(1) << " " << (mat[2][0] < 0.0f ? "" : " ") << mat[2][0] << " " << (mat[2][1] < 0.0f ? "" : " ") << mat[2][1] << " " << (mat[2][2] < 0.0f ? "" : " ") << mat[2][2] << " " << (mat[2][3] < 0.0f ? "" : " ") << mat[2][3] << std::endl;
    std::cout << std::fixed << std::setprecision(1) << " " << (mat[3][0] < 0.0f ? "" : " ") << mat[3][0] << " " << (mat[3][1] < 0.0f ? "" : " ") << mat[3][1] << " " << (mat[3][2] < 0.0f ? "" : " ") << mat[3][2] << " " << (mat[3][3] < 0.0f ? "" : " ") << mat[3][3] << std::endl;
};

void dfsUtil(Entity entity, std::set<Entity::Id>& explored, std::vector<Entity>& sorted) {
    if (entity.valid()) {
        explored.insert(entity.id());
        Entity parent = entity.component<Transform>()->parent;
        if (explored.find(parent.id()) == explored.end()) dfsUtil(parent, explored, sorted);
        sorted.push_back(entity);
    }
}

std::vector<Entity> topsort(const EntityManager::View<Transform>& entities) {
    std::vector<Entity> sorted;
    std::set<Entity::Id> explored;
    for (Entity entity : entities) {
        if (explored.find(entity.id()) == explored.end()) dfsUtil(entity, explored, sorted);
    }
    return sorted;
}

void TransformSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    std::vector<Entity> entities = topsort(es.entities_with_components<Transform>());
    for (Entity entity : entities) {
        ComponentHandle<Transform> transform = entity.component<Transform>();
        glm::mat4 translationMatrix = glm::translate(transform->localPosition);
        glm::mat4 rotationMatrix = glm::mat4_cast(transform->localRotation);
        glm::mat4 scalingMatrix = glm::scale(transform->localScale);
        glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
        
        glm::mat4 parentTransformMatrix;
        if (transform->parent.valid()) parentTransformMatrix = transform->parent.component<Transform>()->localToWorldMatrix;
        transform->localToWorldMatrix = parentTransformMatrix * (modelMatrix);
    }
};
