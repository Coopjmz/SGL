#pragma once

namespace sgl
{
	class VertexArray;
	class Program;
}

namespace sgl
{
	class Renderer
	{
	public:
		Renderer() = default;

		void EnableBlending() const;
		void DisableBlending() const;

		void SetClearColor(const glm::vec4& clearColor) const;

		void Clear() const;
		void Draw(const VertexArray& vertexArray, const Program& program) const;
	};
} // namespace sgl