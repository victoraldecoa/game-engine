//
//  Application.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Application.h"

#include <entityx/deps/Dependencies.h>
#include "Transform.h"
#include "TransformSystem.h"
#include "ShaderManager.h"

using namespace entityx;

Application::Application() {
    systems.add<deps::Dependency<Parent, Transform, Position, Rotation, Scale>>();
    systems.add<deps::Dependency<Transform, Position, Rotation, Scale, Parent>>();
    systems.add<TransformSystem>();
    systems.configure();
    
    shaderManager = new ShaderManager();
Application::~Application() {
    delete shaderManager;
}

void Application::update(TimeDelta dt) {
    systems.update_all(dt);
}