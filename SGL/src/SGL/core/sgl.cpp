#include "sglpch.h"
#include "sgl.h"

#ifdef SGL_DEBUG
#	define GL_LOG_ERROR(fmt, ...) do { std::cerr << "[OpenGL Error] " << std::format(fmt, __VA_ARGS__) << std::endl; } while(false)
#else
#	define GL_LOG_ERROR(fmt, ...)
#endif

namespace
{
    void APIENTRY glErrorCallback(
        const GLenum source,
        const GLenum type,
        const GLuint id,
        const GLenum severity,
        const GLsizei length,
        const GLchar* const message,
        const void* const userParam
    )
    {
        // Ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        const char* sourceText = nullptr;
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:             sourceText = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceText = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceText = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceText = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     sourceText = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           sourceText = "Other"; break;
        }

        const char* typeText = nullptr;
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:               typeText = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeText = "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeText = "Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         typeText = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeText = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              typeText = "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          typeText = "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           typeText = "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               typeText = "Other"; break;
        }

        const char* severityText = nullptr;
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:         severityText = "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severityText = "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severityText = "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityText = "Notification"; break;
        }

        GL_LOG_ERROR("Id: {}\nMessage: {}\nSource: {}\nType: {}\nSeverity: {}",
            id, message, sourceText, typeText, severityText);
    }
} // namespace

namespace sgl
{
    void EnableGlDebugOutput()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glErrorCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    GLuint GetMaxVertexAttributes()
    {
        static GLuint maxVertexAttributes = 0;
        ReturnUnless(maxVertexAttributes == 0, maxVertexAttributes);

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, reinterpret_cast<GLint*>(&maxVertexAttributes));
        return maxVertexAttributes;
    }

    GLuint GetTextureSlotCount()
    {
        static GLuint textureSlotCount = 0;
        ReturnUnless(textureSlotCount == 0, textureSlotCount);

        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, reinterpret_cast<GLint*>(&textureSlotCount));
        return textureSlotCount;
    }
} // namespace sgl