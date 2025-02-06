#include "sglpch.h"
#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Program.h"

namespace sgl
{
	void Renderer::EnableBlending() const
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::DisableBlending() const
	{
		glDisable(GL_BLEND);
	}

	void Renderer::SetClearColor(const glm::vec4& clearColor) const
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& vertexArray, const Program& program) const
	{
		vertexArray.Bind();
		program.Bind();

		const auto* const indexBuffer = vertexArray.GetIndexBuffer();
		AssertReturnUnless(indexBuffer);

		glDrawElements(GL_TRIANGLES, indexBuffer->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}
} // namespace sgl