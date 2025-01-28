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
	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering(const char* const name, const int windowWidth, const int windowHeight);

		void OnUpdate(const float dt) final;
		void OnRender(const sgl::Renderer& renderer) final;
		void OnImGuiRender() final;

	private:
		std::unique_ptr<sgl::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<sgl::IndexBuffer> m_IndexBuffer;
		std::unique_ptr<sgl::VertexArray> m_VertexArray;
		std::unique_ptr<sgl::Program> m_Program;

		std::vector<std::unique_ptr<sgl::Texture>> m_Textures;

		glm::mat4 m_ProjectionMatrix;
		glm::vec3 m_CameraPosition;

		glm::vec2 m_QuadPositions[2];
	};
}