#pragma once

namespace sgl
{
	class Texture
	{
	public:
		Texture();
		Texture(const uint32_t color);
		Texture(const std::string& filepath);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		GLint GetSlot() const;

		int GetWidth() const;
		int GetHeight() const;

		bool IsBound() const;
		void Bind(const GLuint slot);
		void Unbind();

		void SetColor(const uint32_t color);
		void Load(const std::string& filepath);

	private:
		void MakeActive() const;

		void Delete() const;

	private:
		GLuint m_Id;
		GLint m_Slot;

		int m_Width;
		int m_Height;
	};
} // namespace sgl