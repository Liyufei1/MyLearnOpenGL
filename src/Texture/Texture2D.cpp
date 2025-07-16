#include "Texture2D.h"
#include "Common/CommonFunLib.h"
#include "stb/stb.h"
#include <string>

Texture2D::Texture2D(const char* path){
    glGenTextures(1, &mTextureID);
    stbi_set_flip_vertically_on_load(true);
    mData = stbi_load(path, &mWidth, &mHeight, &mChannels, 0);
    if (!mData){
        lyf::PrintError(std::string("Texture2D::LoadTexture2D failed to load texture at path: ") + path);
    }else {
        lyf::Print(std::string("Texture2D::Load success :: " )+ path);
        lyf::Print(std::string("Length: ") + std::to_string(mWidth) + " Height: " + std::to_string(mHeight) + " Channels: " + std::to_string(mChannels)  + " ID: " + std::to_string(mTextureID));
    }
}
Texture2D::~Texture2D(){
    stbi_image_free(mData);
}


void Texture2D::Init(){
    if (!mData) return;
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mSurroundMode);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mSurroundMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMode);

    switch (mChannels) {
    default:
    case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
        break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    lyf::Print(std::string("Texture2D::Init success " )+ " ID: " + std::to_string(mTextureID));
}
