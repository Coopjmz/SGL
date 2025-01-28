#pragma once

namespace sgl
{
	class VertexBuffer;
	class VertexBufferLayout;
	class IndexBuffer;
}

namespace sgl
{
	class VertexArray
	{
	public:
		static void Unbind();

	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		const IndexBuffer* GetIndexBuffer() const;

		void Bind() const;

		void AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout) const;
		void SetIndexBuffer(const IndexBuffer& indexBuffer);

	private:
		void Delete() const;

	private:
		GLuint m_Id;

		const IndexBuffer* m_IndexBuffer;
	};
} // namespace sgl