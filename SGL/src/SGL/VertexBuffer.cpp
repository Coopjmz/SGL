#include "sglpch.h"
#include "VertexBuffer.h"

namespace sgl
{
	/*static*/ void VertexBuffer::Unbind()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::VertexBuffer()
	{
		GLCall(glGenBuffers(1, &m_Id));
	}

	VertexBuffer::VertexBuffer(const GLsizeiptr size)
		: VertexBuffer()
	{
		SetSize(size);
	}

	VertexBuffer::VertexBuffer(const void* const data, const GLsizeiptr size)
		: VertexBuffer()
	{
		SetData(data, size);
	}

	VertexBuffer::~VertexBuffer()
	{
		Delete();
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
		: m_Id(std::exchange(other.m_Id, 0))
	{
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		ReturnIf(this == &other, *this);

		Delete();

		m_Id = std::exchange(other.m_Id, 0);

		return *this;
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
	}

	void VertexBuffer::SetSize(const GLsizeiptr size) const
	{
		Bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	void VertexBuffer::SetData(const void* const data, const GLsizeiptr size) const
	{
		Bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	void VertexBuffer::SetSubData(const void* const data, const GLsizeiptr size, const GLintptr offset /*= 0LL*/) const
	{
		Bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	}

	void VertexBuffer::Delete() const
	{
		GLCall(glDeleteBuffers(1, &m_Id));
	}
} // namespace sgl