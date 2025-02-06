#include "sglpch.h"
#include "Texture.h"

namespace sgl
{
	Texture::Texture()
		: m_Slot(-1)
		, m_Width(0)
		, m_Height(0)
	{
		glGenTextures(1, &m_Id);
	}

	Texture::Texture(const uint32_t color)
		: Texture()
	{
		SetColor(color);
	}

	Texture::Texture(const std::string& filepath)
		: Texture()
	{
		Load(filepath);
	}

	Texture::~Texture()
	{
		Delete();
	}

	Texture::Texture(Texture&& other) noexcept
		: m_Id(std::exchange(other.m_Id, 0))
		, m_Slot(std::move(other.m_Slot))
		, m_Width(std::move(other.m_Width))
		, m_Height(std::move(other.m_Height))
	{
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		ReturnIf(this == &other, *this);

		Delete();

		m_Id = std::exchange(other.m_Id, 0);
		m_Slot = std::move(other.m_Slot);
		m_Width = std::move(other.m_Width);
		m_Height = std::move(other.m_Height);

		return *this;
	}

	GLint Texture::GetSlot() const
	{
		return m_Slot;
	}

	int Texture::GetWidth() const
	{
		return m_Width;
	}

	int Texture::GetHeight() const
	{
		return m_Height;
	}

	bool Texture::IsBound() const
	{
		return m_Slot >= 0;
	}

	void Texture::Bind(const GLuint slot)
	{
		AssertReturnUnless(slot < sgl::GetTextureSlotCount());
		ReturnIf(m_Slot == slot);

		if (IsBound())
			Unbind();

		m_Slot = slot;

		MakeActive();
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void Texture::Unbind()
	{
		ReturnUnless(IsBound());

		MakeActive();
		glBindTexture(GL_TEXTURE_2D, 0);

		m_Slot = -1;
	}

	void Texture::SetColor(const uint32_t color)
	{
		Bind(sgl::GetTextureSlotCount() - 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
		Unbind();
	}

	void Texture::Load(const std::string& filepath)
	{
		AssertReturnIf(filepath.empty());

		stbi_set_flip_vertically_on_load(1);

		int channels;
		void* const data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &channels, 4);

		const bool isBound = IsBound();
		if (!isBound)
			Bind(sgl::GetTextureSlotCount() - 1);
		else
			MakeActive();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		if (!isBound)
			Unbind();

		ReturnUnless(data);
		stbi_image_free(data);
	}

	void Texture::MakeActive() const
	{
		glActiveTexture(GL_TEXTURE0 + m_Slot);
	}

	void Texture::Delete() const
	{
		glDeleteTextures(1, &m_Id);
	}
} // namespace sgl