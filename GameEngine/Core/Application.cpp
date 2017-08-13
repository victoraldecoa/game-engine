//
//  Application.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Application.h"

using namespace entityx;

Application::Application() {
    systems.configure();
}

void Application::update(TimeDelta dt) {
    systems.update_all(dt);
}
