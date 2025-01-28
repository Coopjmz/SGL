#pragma once

namespace sgl
{
	class VertexBuffer
	{
	public:
		static void Unbind();

	public:
		VertexBuffer();
		VertexBuffer(const GLsizeiptr size);
		VertexBuffer(const void* const data, const GLsizeiptr size);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		void Bind() const;

		void SetSize(const GLsizeiptr size) const;
		void SetData(const void* const data, const GLsizeiptr size) const;
		void SetSubData(const void* const data, const GLsizeiptr size, const GLintptr offset = 0LL) const;

	private:
		void Delete() const;

	private:
		GLuint m_Id;
	};
} // namespace sgl