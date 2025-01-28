#pragma once

namespace sgl
{
	class Shader;
}

namespace sgl
{
	class Program
	{
	public:
		static void Unbind();

	public:
		Program();
		Program(const Shader& vertexShader, const Shader& fragmentShader);
		~Program();

		Program(const Program&) = delete;
		Program& operator=(const Program&) = delete;
		Program(Program&& other) noexcept;
		Program& operator=(Program&& other) noexcept;

		void Bind() const;

		void Link(const Shader& vertexShader, const Shader& fragmentShader) const;

		void SetUniform1i(const std::string& name, const GLint v0) const;
		void SetUniform2i(const std::string& name, const GLint v0, const GLint v1) const;
		void SetUniform3i(const std::string& name, const GLint v0, const GLint v1, const GLint v2) const;
		void SetUniform4i(const std::string& name, const GLint v0, const GLint v1, const GLint v2, const GLint v3) const;

		void SetUniform1ui(const std::string& name, const GLuint v0) const;
		void SetUniform2ui(const std::string& name, const GLuint v0, const GLuint v1) const;
		void SetUniform3ui(const std::string& name, const GLuint v0, const GLuint v1, const GLuint v2) const;
		void SetUniform4ui(const std::string& name, const GLuint v0, const GLuint v1, const GLuint v2, const GLuint v3) const;

		void SetUniform1f(const std::string& name, const GLfloat v0) const;
		void SetUniform2f(const std::string& name, const GLfloat v0, const GLfloat v1) const;
		void SetUniform3f(const std::string& name, const GLfloat v0, const GLfloat v1, const GLfloat v2) const;
		void SetUniform4f(const std::string& name, const GLfloat v0, const GLfloat v1, const GLfloat v2, const GLfloat v3) const;

		void SetUniform1iv(const std::string& name, const GLsizei count, const GLint* const value) const;
		void SetUniform2iv(const std::string& name, const GLsizei count, const GLint* const value) const;
		void SetUniform3iv(const std::string& name, const GLsizei count, const GLint* const value) const;
		void SetUniform4iv(const std::string& name, const GLsizei count, const GLint* const value) const;

		void SetUniform1uiv(const std::string& name, const GLsizei count, const GLuint* const value) const;
		void SetUniform2uiv(const std::string& name, const GLsizei count, const GLuint* const value) const;
		void SetUniform3uiv(const std::string& name, const GLsizei count, const GLuint* const value) const;
		void SetUniform4uiv(const std::string& name, const GLsizei count, const GLuint* const value) const;

		void SetUniform1fv(const std::string& name, const GLsizei count, const GLfloat* const value) const;
		void SetUniform2fv(const std::string& name, const GLsizei count, const GLfloat* const value) const;
		void SetUniform3fv(const std::string& name, const GLsizei count, const GLfloat* const value) const;
		void SetUniform4fv(const std::string& name, const GLsizei count, const GLfloat* const value) const;

		void SetUniformMatrix2f(const std::string& name, const glm::mat2& matrix) const;
		void SetUniformMatrix3f(const std::string& name, const glm::mat3& matrix) const;
		void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix) const;

	private:
		GLint GetUniformLocation(const std::string& name) const;

		void Delete() const;

	private:
		GLuint m_Id;

		mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
	};
} // namespace sgl