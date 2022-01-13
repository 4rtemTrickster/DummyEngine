#include "DEpch.h"
#include "OpenGLTexture2D.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Dummy
{
    OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& path)
    {
        if(!std::filesystem::exists(path)) DE_CORE_ERROR("Texture file does not exists!"); 
        
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

        DE_CORE_ASSERT(data, "Failed to load image");

        // Reassigning 'cause stb provides only signed integers
        Width = width;
        Height = height;

        GLenum internalFormat = 0, dataFormat = 0;

        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        DE_CORE_ASSERT(internalFormat & dataFormat, "Format is not supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
        glTextureStorage2D(RendererID, 1, internalFormat, Width, Height);

        glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(RendererID, 0, 0, 0, Width, Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, RendererID);
    }
}
