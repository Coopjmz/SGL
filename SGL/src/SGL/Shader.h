#pragma once

namespace sgl
{
	class Shader
	{
	public:
		static std::optional<Shader> Parse(const std::string& filepath);

	public:
		Shader(const GLenum type);
		Shader(const GLenum type, const std::string& source);
		~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;

		GLuint GetId() const;
		GLenum GetType() const;

		void Compile(const std::string& source) const;

	private:
		void Delete() const;

	private:
		GLuint m_Id;
		GLenum m_Type;
	};
} // namespace sgl