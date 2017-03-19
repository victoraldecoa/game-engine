//
//  EngineGLFWInitializer.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineGLFWInitializer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int EngineGLFWInitializer::initialize(function<void (float dt)> updateCallback) {
    
    glfwSetErrorCallback(errorCallback);

    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "GameEngine", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (!window) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetKeyCallback(window, keyCallback);
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }
    
    glfwSwapInterval(1);
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        
        double time = glfwGetTime();
        updateCallback(time - lastTime);
        lastTime = time;
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}
