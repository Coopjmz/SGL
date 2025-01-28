#pragma once

namespace sgl
{
	class IndexBuffer
	{
	public:
		static void Unbind();

	public:
		IndexBuffer();
		IndexBuffer(const GLuint* const data, const GLsizeiptr size);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		GLsizei GetIndexCount() const;

		void Bind() const;

		void SetData(const GLuint* const data, const GLsizeiptr size);

	private:
		void Delete() const;

	private:
		GLuint m_Id;
		GLsizei m_IndexCount;
	};
} // namespace sgl