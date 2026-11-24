#include "Texture.h"
#include <iostream>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif

#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

Texture::Texture(const std::string& path)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    stbi_set_flip_vertically_on_load(true);

    int w = 0, h = 0, c = 0;

    unsigned char* data =
        stbi_load(path.c_str(), &w, &h, &c, 0);

    if (data)
    {
        GLenum format = GL_RGB;

        if (c == 4)
            format = GL_RGBA;
        else if (c == 1)
            format = GL_RED;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            w,
            h,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        float maxAniso = 1.0f;

        glGetFloatv(
            GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,
            &maxAniso
        );

        if (maxAniso > 1.0f)
        {
            glTexParameterf(
                GL_TEXTURE_2D,
                GL_TEXTURE_MAX_ANISOTROPY_EXT,
                std::min(maxAniso, 16.0f)
            );
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        std::cout << "Texture loaded: "
                  << path << " "
                  << w << "x" << h << std::endl;
    }
    else
    {
        std::cerr << "Texture missing: "
                  << path << std::endl;
    }

    stbi_image_free(data);
}

void Texture::bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}