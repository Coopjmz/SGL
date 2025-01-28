#include "sglpch.h"
#include "VertexArray.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

namespace sgl
{
	/*static*/ void VertexArray::Unbind()
	{
		GLCall(glBindVertexArray(0));
	}

	VertexArray::VertexArray()
		: m_IndexBuffer(nullptr)
	{
		GLCall(glGenVertexArrays(1, &m_Id));
	}

	VertexArray::~VertexArray()
	{
		Delete();
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		: m_Id(std::exchange(other.m_Id, 0))
		, m_IndexBuffer(std::move(other.m_IndexBuffer))
	{
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		ReturnIf(this == &other, *this);

		Delete();

		m_Id = std::exchange(other.m_Id, 0);
		m_IndexBuffer = std::move(other.m_IndexBuffer);

		return *this;
	}

	const IndexBuffer* VertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_Id));
	}

	void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout) const
	{
		Bind();
		vertexBuffer.Bind();

		GLsizei offset = 0;
		const auto& elements = vertexBufferLayout.GetElements();
		for (GLuint i = 0; i < elements.size(); ++i)
		{
			const auto& element = elements[i];

			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.Count, element.Type, element.Normalized,
				vertexBufferLayout.GetStride(), reinterpret_cast<const void*>(offset)));

			offset += element.GetSize();
		}
	}

	void VertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
	{
		Bind();
		indexBuffer.Bind();

		m_IndexBuffer = &indexBuffer;
	}

	void VertexArray::Delete() const
	{
		GLCall(glDeleteVertexArrays(1, &m_Id));
	}
} // namespace sgl