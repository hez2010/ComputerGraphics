#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texturePath, int internalFormat, std::function<void()> config)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    config();

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}
