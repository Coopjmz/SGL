#pragma once

namespace sgl
{
	struct VertexBufferLayoutElement
	{
		GLint Count;
		GLenum Type;
		GLboolean Normalized;

		VertexBufferLayoutElement(const GLint count, const GLenum type, const GLboolean normalized);

		GLsizei GetSize() const;
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();

		GLsizei GetStride() const;
		const std::vector<VertexBufferLayoutElement>& GetElements() const;

		template <typename T>
		void Push(const GLboolean normalized = GL_FALSE);

	private:
		GLsizei m_Stride;
		std::vector<VertexBufferLayoutElement> m_Elements;
	};

	template <>
	inline void VertexBufferLayout::Push<GLbyte>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_BYTE, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<GLubyte>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_UNSIGNED_BYTE, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<GLshort>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_SHORT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<GLushort>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_UNSIGNED_SHORT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<GLint>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<GLuint>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_UNSIGNED_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<GLfloat>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(1, GL_FLOAT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::ivec2>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(2, GL_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::ivec3>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(3, GL_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::ivec4>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(4, GL_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::uvec2>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(2, GL_UNSIGNED_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::uvec3>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(3, GL_UNSIGNED_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::uvec4>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(4, GL_UNSIGNED_INT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::vec2>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(2, GL_FLOAT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::vec3>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(3, GL_FLOAT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}

	template <>
	inline void VertexBufferLayout::Push<glm::vec4>(const GLboolean normalized)
	{
		AssertReturnUnless(m_Elements.size() < sgl::GetMaxVertexAttributes());
		m_Elements.emplace_back(4, GL_FLOAT, normalized);
		m_Stride += m_Elements.back().GetSize();
	}
} // namespace sgl