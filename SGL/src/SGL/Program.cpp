#include "sglpch.h"
#include "Program.h"

#include "Shader.h"

namespace sgl
{
    /*static*/ void Program::Unbind()
    {
        GLCall(glUseProgram(0));
    }

    Program::Program()
        : m_Id(glCreateProgram())
    {
    }

    Program::Program(const Shader& vertexShader, const Shader& fragmentShader)
        : Program()
    {
        Link(vertexShader, fragmentShader);
    }

    Program::~Program()
    {
        Delete();
    }

    Program::Program(Program&& other) noexcept
        : m_Id(std::exchange(other.m_Id, 0))
        , m_UniformLocationCache(std::move(other.m_UniformLocationCache))
    {
    }

    Program& Program::operator=(Program&& other) noexcept
    {
        ReturnIf(this == &other, *this);

        Delete();

        m_Id = std::exchange(other.m_Id, 0);
        m_UniformLocationCache = std::move(other.m_UniformLocationCache);

        return *this;
    }

    void Program::Bind() const
    {
        GLCall(glUseProgram(m_Id));
    }

    void Program::Link(const Shader& vertexShader, const Shader& fragmentShader) const
    {
        AssertReturnUnless(vertexShader.GetType() == GL_VERTEX_SHADER && fragmentShader.GetType() == GL_FRAGMENT_SHADER);

        GLCall(glAttachShader(m_Id, vertexShader.GetId()));
        GLCall(glAttachShader(m_Id, fragmentShader.GetId()));

        GLCall(glLinkProgram(m_Id));

        GLCall(glDetachShader(m_Id, vertexShader.GetId()));
        GLCall(glDetachShader(m_Id, fragmentShader.GetId()));

        GLint linkStatus;
        GLCall(glGetProgramiv(m_Id, GL_LINK_STATUS, &linkStatus));
        if (linkStatus == GL_FALSE)
        {
            GLint infoLogLength;
            GLCall(glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogLength));

            GLchar* const infoLog = static_cast<GLchar*>(alloca(infoLogLength * sizeof(GLchar)));
            GLCall(glGetProgramInfoLog(m_Id, infoLogLength, &infoLogLength, infoLog));

            std::cerr << "Failed to link program!\n" << infoLog << std::endl;

            ASSERT(false);
            return;
        }

        GLCall(glValidateProgram(m_Id));

        GLint validateStatus;
        GLCall(glGetProgramiv(m_Id, GL_VALIDATE_STATUS, &validateStatus));
        if (validateStatus == GL_FALSE)
        {
            GLint infoLogLength;
            GLCall(glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogLength));

            GLchar* const infoLog = static_cast<GLchar*>(alloca(infoLogLength * sizeof(GLchar)));
            GLCall(glGetProgramInfoLog(m_Id, infoLogLength, &infoLogLength, infoLog));

            std::cerr << "Failed to validate program!\n" << infoLog << std::endl;

            ASSERT(false);
            return;
        }

        m_UniformLocationCache.clear();
    }

    void Program::SetUniform1i(const std::string& name, const GLint v0) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform1i(GetUniformLocation(name), v0));
    }

    void Program::SetUniform2i(const std::string& name, const GLint v0, const GLint v1) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform2i(GetUniformLocation(name), v0, v1));
    }

    void Program::SetUniform3i(const std::string& name, const GLint v0, const GLint v1, const GLint v2) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform3i(GetUniformLocation(name), v0, v1, v2));
    }

    void Program::SetUniform4i(const std::string& name, const GLint v0, const GLint v1, const GLint v2, const GLint v3) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform4i(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Program::SetUniform1ui(const std::string& name, const GLuint v0) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform1ui(GetUniformLocation(name), v0));
    }

    void Program::SetUniform2ui(const std::string& name, const GLuint v0, const GLuint v1) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform2ui(GetUniformLocation(name), v0, v1));
    }

    void Program::SetUniform3ui(const std::string& name, const GLuint v0, const GLuint v1, const GLuint v2) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform3ui(GetUniformLocation(name), v0, v1, v2));
    }

    void Program::SetUniform4ui(const std::string& name, const GLuint v0, const GLuint v1, const GLuint v2, const GLuint v3) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Program::SetUniform1f(const std::string& name, const GLfloat v0) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform1f(GetUniformLocation(name), v0));
    }

    void Program::SetUniform2f(const std::string& name, const GLfloat v0, const GLfloat v1) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
    }

    void Program::SetUniform3f(const std::string& name, const GLfloat v0, const GLfloat v1, const GLfloat v2) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
    }

    void Program::SetUniform4f(const std::string& name, const GLfloat v0, const GLfloat v1, const GLfloat v2, const GLfloat v3) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Program::SetUniform1iv(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform1iv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform2iv(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform2iv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform3iv(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform3iv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform4iv(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform4iv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform1uiv(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform1uiv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform2uiv(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform2uiv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform3uiv(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform3uiv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform4uiv(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform4uiv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform1fv(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform1fv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform2fv(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform2fv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform3fv(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform3fv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniform4fv(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniform4fv(GetUniformLocation(name), count, value));
    }

    void Program::SetUniformMatrix2f(const std::string& name, const glm::mat2& matrix) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    void Program::SetUniformMatrix3f(const std::string& name, const glm::mat3& matrix) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    void Program::SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix) const
    {
        AssertReturnIf(name.empty());
        Bind();
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    GLint Program::GetUniformLocation(const std::string& name) const
    {
        AssertReturnIf(name.empty(), -1);

        const auto it = m_UniformLocationCache.find(name);
        if (it != m_UniformLocationCache.end())
            return it->second;

        const GLint uniformLocation = glGetUniformLocation(m_Id, name.c_str());
        if (uniformLocation == -1)
            std::cerr << "[OpenGL Warning] Uniform '" << name << "' does not exist!" << std::endl;

        m_UniformLocationCache[name] = uniformLocation;
        return uniformLocation;
    }

    void Program::Delete() const
    {
        GLCall(glDeleteProgram(m_Id));
    }
}