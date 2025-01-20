#include "TextureManager.h"
#include <iostream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> // Include stb_image for image loading

namespace fs = std::filesystem;

std::vector<Texture> TextureManager::textures;

void TextureManager::initialize() {
    std::string textureFolder = "C:/path/to/texture";
    for (const auto& entry : fs::directory_iterator(textureFolder)) {
        if (entry.path().extension() == ".png") {
            std::string filename = entry.path().stem().string();
            std::string filePath = entry.path().string();
            if (!textureExists(filename)) {
                GLuint textureID = loadTexture(filePath);
                if (textureID != 0) {
                    textures.push_back({ filename, filePath, textureID });
                }
                else {
                    std::cerr << "Failed to load texture: " << filePath << std::endl;
                }
            }
            else {
                std::cerr << "Duplicate texture name detected: " << filename << std::endl;
            }
        }
    }
}

GLuint TextureManager::loadTexture(const std::string& filePath) {
    GLuint textureID;
    glGenTextures(1, &textureID); // Generate OpenGL texture ID
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture for configuration

    int width, height, channels;
    // Load the image using stb_image
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (imageData) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

        // Load image data into OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(imageData); // Free the image memory
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
    }
    else {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        stbi_image_free(imageData);
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }

    return textureID;
}

const Texture* TextureManager::getTexture(const std::string& name) {
    for (const Texture& texture : textures) {
        if (texture.name == name) {
            return &texture;
        }
    }

    std::cerr << "Texture not found: " << name << std::endl;
    return nullptr;
}

bool TextureManager::textureExists(const std::string& name) {
    for (const Texture& texture : textures) {
        if (texture.name == name) {
            return true;
        }
    }
    return false;
}

void TextureManager::cleanup() {
    for (const Texture& texture : textures) {
        glDeleteTextures(1, &texture.id);
    }
    textures.clear();
}
