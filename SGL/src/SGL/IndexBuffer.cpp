#include "sglpch.h"
#include "IndexBuffer.h"

namespace sgl
{
	/*static*/ void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::IndexBuffer()
		: m_IndexCount(0)
	{
		glGenBuffers(1, &m_Id);
	}

	IndexBuffer::IndexBuffer(const GLuint* const data, const GLsizeiptr size)
		: IndexBuffer()
	{
		SetData(data, size);
	}

	IndexBuffer::~IndexBuffer()
	{
		Delete();
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
		: m_Id(std::exchange(other.m_Id, 0))
		, m_IndexCount(std::move(other.m_IndexCount))
	{
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		ReturnIf(this == &other, *this);

		Delete();

		m_Id = std::exchange(other.m_Id, 0);
		m_IndexCount = std::move(other.m_IndexCount);

		return *this;
	}

	GLsizei IndexBuffer::GetIndexCount() const
	{
		return m_IndexCount;
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void IndexBuffer::SetData(const GLuint* const data, const GLsizeiptr size)
	{
		m_IndexCount = static_cast<GLsizei>(size / sizeof(GLuint));

		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void IndexBuffer::Delete() const
	{
		glDeleteBuffers(1, &m_Id);
	}
} // namespace sgl