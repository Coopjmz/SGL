#include "sglpch.h"
#include "VertexBufferLayout.h"

namespace sgl
{
	// VertexBufferLayoutElement
	VertexBufferLayoutElement::VertexBufferLayoutElement(const GLint count, const GLenum type, const GLboolean normalized)
		: Count(count)
		, Type(type)
		, Normalized(normalized)
	{
	}

	GLsizei VertexBufferLayoutElement::GetSize() const
	{
		switch (Type)
		{
		case GL_BYTE:
			return Count * sizeof(GLbyte);
		case GL_UNSIGNED_BYTE:
			return Count * sizeof(GLubyte);
		case GL_SHORT:
			return Count * sizeof(GLshort);
		case GL_UNSIGNED_SHORT:
			return Count * sizeof(GLushort);
		case GL_INT:
			return Count * sizeof(GLint);
		case GL_UNSIGNED_INT:
			return Count * sizeof(GLuint);
		case GL_FLOAT:
			return Count * sizeof(GLfloat);
		}

		SGL_ASSERT(false);
		return 0;
	}

	// VertexBufferLayout
	VertexBufferLayout::VertexBufferLayout()
		: m_Stride(0)
	{
	}

	GLsizei VertexBufferLayout::GetStride() const
	{
		return m_Stride;
	}

	const std::vector<VertexBufferLayoutElement>& VertexBufferLayout::GetElements() const
	{
		return m_Elements;
	}
} // namespace sgl