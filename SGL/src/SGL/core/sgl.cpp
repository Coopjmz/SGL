#include "sglpch.h"
#include "sgl.h"

namespace sgl
{
    void ClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool LogCall(const char* const function, const char* const file, const int line)
    {
        bool hasNoErrors = true;

        while (const GLenum error = glGetError())
        {
            hasNoErrors = false;

            const char* errorMessage;
            switch (error)
            {
            case GL_INVALID_ENUM:
                errorMessage = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorMessage = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorMessage = "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                errorMessage = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                errorMessage = "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                errorMessage = "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorMessage = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                errorMessage = "ERROR";
            }

            std::cerr << "[OpenGL Error] " << file << '(' << line << "): " << errorMessage << " - " << function << std::endl;
        }

        return hasNoErrors;
    }

    GLuint GetMaxVertexAttributes()
    {
        static GLuint maxVertexAttributes = 0;
        ReturnUnless(maxVertexAttributes == 0, maxVertexAttributes);

        GLCall(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, reinterpret_cast<GLint*>(&maxVertexAttributes)));
        return maxVertexAttributes;
    }

    GLuint GetTextureSlotCount()
    {
        static GLuint textureSlotCount = 0;
        ReturnUnless(textureSlotCount == 0, textureSlotCount);

        GLCall(glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, reinterpret_cast<GLint*>(&textureSlotCount)));
        return textureSlotCount;
    }
} // namespace sgl