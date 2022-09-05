//
// Created by Danny Le on 2022-08-27.
//

#ifndef SPINNING_RAT_TEXTURE_HPP
#define SPINNING_RAT_TEXTURE_HPP

#pragma once

class Texture
{
public:
    Texture(const char* path);

    unsigned int GetTextureID() const { return TextureID; }

private:
    unsigned int TextureID;
};

#endif //SPINNING_RAT_TEXTURE_HPP
