#pragma once
#include "glad/glad.h"
#include "Common/CommonFunLib.h"



class Texture2D {
public:
    Texture2D(const char* path);
    ~Texture2D();

    void Init();

    GLint GetTextureID() const { return mTextureID; }

private:
    GLuint mTextureID = 0;
    unsigned char* mData;
    int mWidth;
    int mHeight;
    int mChannels;
    GLint mSurroundMode = GL_REPEAT;
    GLint mFilterMode = GL_LINEAR;
    bool bIsMipmap = true;

};
