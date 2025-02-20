#include "sglpch.h"
#include "Shader.h"

namespace sgl
{
    /*static*/ std::optional<Shader> Shader::Parse(const std::string& filepath)
    {
        AssertReturnIf(filepath.empty(), {});

        GLenum type = 0;

        const size_t fileExtentionPosition = filepath.rfind('.');
        AssertReturnIf(fileExtentionPosition == std::string::npos, {});

        const std::string fileExtention = filepath.substr(fileExtentionPosition);
        if (fileExtention == ".vert")
            type = GL_VERTEX_SHADER;
        else if (fileExtention == ".tesc")
            type = GL_TESS_CONTROL_SHADER;
        else if (fileExtention == ".tese")
            type = GL_TESS_EVALUATION_SHADER;
        else if (fileExtention == ".geom")
            type = GL_GEOMETRY_SHADER;
        else if (fileExtention == ".frag")
            type = GL_FRAGMENT_SHADER;
        else if (fileExtention == ".comp")
            type = GL_COMPUTE_SHADER;

        AssertReturnIf(type == 0, {});

        const auto source = utils::ReadFile(filepath);
        AssertReturnUnless(source && !source->empty(), {});

        return Shader(type, *source);
    }

    Shader::Shader(const GLenum type)
        : m_Id(glCreateShader(type))
        , m_Type(type)
    {
        SGL_ASSERT(m_Type == GL_VERTEX_SHADER
                || m_Type == GL_TESS_CONTROL_SHADER
                || m_Type == GL_TESS_EVALUATION_SHADER
                || m_Type == GL_GEOMETRY_SHADER
                || m_Type == GL_FRAGMENT_SHADER
                || m_Type == GL_COMPUTE_SHADER);
    }

    Shader::Shader(const GLenum type, const std::string& source)
        : Shader(type)
    {
        Compile(source);
    }

    Shader::~Shader()
    {
        Delete();
    }

    Shader::Shader(Shader&& other) noexcept
        : m_Id(std::exchange(other.m_Id, 0))
        , m_Type(std::move(other.m_Type))
    {
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        ReturnIf(this == &other, *this);

        Delete();
        m_Id = std::exchange(other.m_Id, 0);
        m_Type = std::move(other.m_Type);

        return *this;
    }

    GLuint Shader::GetId() const
    {
        return m_Id;
    }

    GLenum Shader::GetType() const
    {
        return m_Type;
    }

    void Shader::Compile(const std::string& source) const
    {
        AssertReturnIf(source.empty());

        const char* const src = source.c_str();
        glShaderSource(m_Id, 1, &src, nullptr);
        glCompileShader(m_Id);

        GLint compileStatus;
        glGetShaderiv(m_Id, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus == GL_FALSE)
        {
            GLint infoLogLength;
            glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogLength);

            GLchar* const infoLog = static_cast<GLchar*>(alloca(infoLogLength * sizeof(GLchar)));
            glGetShaderInfoLog(m_Id, infoLogLength, &infoLogLength, infoLog);

            SGL_LOG_ERROR("Failed to compile {} shader!\n{}", m_Type == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);

            SGL_ASSERT(false);
        }
    }

    void Shader::Delete() const
    {
        glDeleteShader(m_Id);
    }
} // namespace sgl