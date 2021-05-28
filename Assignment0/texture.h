#pragma once

#include <glad/glad.h>

#include <functional>
#include <iostream>

class Texture {
public:
    unsigned int id;
    Texture(const char* texturePath, int internalFormat, std::function<void()> config);
    ~Texture();
};