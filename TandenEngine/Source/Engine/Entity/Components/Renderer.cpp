//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Renderer.h"
#include "../../RenderingSystem/RenderingSystem.h"
#include <iostream>
void Renderer::Update() {

}

void Renderer::Register() {
    RenderingSystem::RegisterRenderer(this);
}