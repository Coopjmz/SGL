#pragma once

#include "Test.h"

namespace sgl
{
	class VertexBuffer;
	class IndexBuffer;
	class VertexArray;
	class Program;
	class Texture;
}

namespace test
{
	class TestTexture2D : public Test
	{
		struct Image
		{
			glm::vec3 Position;
			std::unique_ptr<sgl::Texture> Texture;
		};

	public:
		TestTexture2D(const char* const name, const int windowWidth, const int windowHeight);

		void OnRender(const sgl::Renderer& renderer) final;
		void OnImGuiRender() final;

	private:
		std::unique_ptr<sgl::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<sgl::IndexBuffer> m_IndexBuffer;
		std::unique_ptr<sgl::VertexArray> m_VertexArray;
		std::unique_ptr<sgl::Program> m_Program;

		glm::mat4 m_ProjectionMatrix;
		glm::vec3 m_CameraPosition;

		std::vector<Image> m_Images;
	};
} // namespace test