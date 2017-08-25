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

using namespace entityx;
using namespace glm;

void logMat4(mat4& mat) {
    std::cout << "<mat4> " << &mat << std::endl;
    std::cout << mat[0][0] << mat[0][1] << mat[0][2] << mat[0][3] << std::endl;
    std::cout << mat[1][0] << mat[1][1] << mat[1][2] << mat[1][3] << std::endl;
    std::cout << mat[2][0] << mat[2][1] << mat[2][2] << mat[2][3] << std::endl;
    std::cout << mat[3][0] << mat[3][1] << mat[3][2] << mat[3][3] << std::endl;
};

void TransformSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    std::cout << "TransformSystem" << std::endl;
    es.each<Transform>([dt] (Entity entity, Transform &transform) {
        glm::mat4 translationMatrix = glm::translate(transform.localPosition);
        glm::mat4 rotationMatrix = glm::mat4_cast(transform.localRotation);
        glm::mat4 scalingMatrix = glm::scale(transform.localScale);
        glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
        
        glm::mat4 parentTransformMatrix;
        if (transform.parent.valid()) parentTransformMatrix = transform.parent.component<Transform>()->localToWorldMatrix;
        transform.localToWorldMatrix = parentTransformMatrix * (modelMatrix);
        
        std::cout << "Entity:" << &entity << std::endl;
        if (transform.parent.valid()) std::cout << "Parent:" << &transform.parent << std::endl;
        std::cout << "Composing matrices:" << std::endl;
        logMat4(translationMatrix);
        logMat4(rotationMatrix);
        logMat4(scalingMatrix);
        
        std::cout << std::endl << "Model matrix:" << std::endl;
        logMat4(modelMatrix);
        
        std::cout << std::endl << "Local to world matrix:" << std::endl;
        logMat4(transform.localToWorldMatrix);
        
        std::cout << std::endl;
    });
};