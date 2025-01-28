#include "sglpch.h"
#include "TestBatchRendering.h"

#include "SGL/VertexBuffer.h"
#include "SGL/VertexBufferLayout.h"
#include "SGL/IndexBuffer.h"
#include "SGL/VertexArray.h"
#include "SGL/Shader.h"
#include "SGL/Program.h"
#include "SGL/Texture.h"
#include "SGL/Renderer.h"

namespace
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;

		static sgl::VertexBufferLayout GenerateVertexBufferLayout()
		{
			sgl::VertexBufferLayout vertexBufferLayout;
			vertexBufferLayout.Push<decltype(Position)>();
			vertexBufferLayout.Push<decltype(Color)>();
			vertexBufferLayout.Push<decltype(TexCoord)>();
			vertexBufferLayout.Push<decltype(TexIndex)>();
			return vertexBufferLayout;
		}
	};
} // namespace

namespace test
{
	static constexpr GLuint INDICES[] =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	static constexpr const char* VERTEX_SHADER_FILEPATH = "res\\shaders\\batch_rendering.vert";
	static constexpr const char* FRAGMENT_SHADER_FILEPATH = "res\\shaders\\batch_rendering.frag";
	static constexpr const char* TEXTURE_FILEPATHS[] =
	{
		"res\\textures\\box.png",
		"res\\textures\\chest.png"
	};

	static std::array<Vertex, 4> CreateQuad(const glm::vec2 position, const glm::vec2 size, const float textureIndex)
	{
		Vertex v0, v1, v2, v3;

		v0.Position = { position.x - size.x / 2.f, position.y - size.y / 2.f, 0.f };
		v1.Position = { position.x + size.x / 2.f, position.y - size.y / 2.f, 0.f };
		v2.Position = { position.x + size.x / 2.f, position.y + size.y / 2.f, 0.f };
		v3.Position = { position.x - size.x / 2.f, position.y + size.y / 2.f, 0.f };

		v0.Color = { 0.18f, 0.6f, 0.96f, 1.f };
		v1.Color = { 0.18f, 0.6f, 0.96f, 1.f };
		v2.Color = { 0.18f, 0.6f, 0.96f, 1.f };
		v3.Color = { 0.18f, 0.6f, 0.96f, 1.f };

		v0.TexCoord = { 0.f, 0.f };
		v1.TexCoord = { 1.f, 0.f };
		v2.TexCoord = { 1.f, 1.f };
		v3.TexCoord = { 0.f, 1.f };

		v0.TexIndex = textureIndex;
		v1.TexIndex = textureIndex;
		v2.TexIndex = textureIndex;
		v3.TexIndex = textureIndex;

		return { v0, v1, v2, v3 };
	}

	TestBatchRendering::TestBatchRendering(const char* const name, const int windowWidth, const int windowHeight)
		: Test(name)
		, m_VertexBuffer(std::make_unique<sgl::VertexBuffer>(1000 * sizeof(Vertex)))
		, m_IndexBuffer(std::make_unique<sgl::IndexBuffer>(INDICES, sizeof(INDICES)))
		, m_VertexArray(std::make_unique<sgl::VertexArray>())
		, m_Program(std::make_unique<sgl::Program>())
		, m_ProjectionMatrix(glm::ortho(0.f, static_cast<float>(windowWidth), 0.f, static_cast<float>(windowHeight), -1.f, +1.f))
		, m_CameraPosition(0.f, 0.f, 0.f)
		, m_QuadPositions{ {windowWidth / 2.f - 400.f, windowHeight / 2.f}, {windowWidth / 2.f + 400.f, windowHeight / 2.f} }
	{
		m_VertexArray->AddVertexBuffer(*m_VertexBuffer, Vertex::GenerateVertexBufferLayout());
		m_VertexArray->SetIndexBuffer(*m_IndexBuffer);

		const auto vertexShader = sgl::Shader::Parse(VERTEX_SHADER_FILEPATH);
		const auto fragmentShader = sgl::Shader::Parse(FRAGMENT_SHADER_FILEPATH);
		if (vertexShader && fragmentShader)
			m_Program->Link(*vertexShader, *fragmentShader);

		for (const char* const filepath : TEXTURE_FILEPATHS)
			m_Textures.push_back(std::make_unique<sgl::Texture>(filepath));

		std::vector<GLint> samplers;
		samplers.reserve(m_Textures.size());
		for (GLuint i = 0; i < m_Textures.size(); ++i)
		{
			m_Textures[i]->Bind(i);
			samplers.push_back(i);
		}

		m_Program->SetUniform1iv("u_Textures", static_cast<GLsizei>(samplers.size()), samplers.data());
	}

	void TestBatchRendering::OnUpdate(const float dt)
	{
		const auto quad0 = CreateQuad(m_QuadPositions[0], {400.f, 400.f}, 0.f);
		const auto quad1 = CreateQuad(m_QuadPositions[1], { 400.f, 400.f }, 1.f);

		Vertex vertices[8];
		memcpy(vertices, quad0.data(), quad0.size() * sizeof(Vertex));
		memcpy(vertices + quad0.size(), quad1.data(), quad1.size() * sizeof(Vertex));

		m_VertexBuffer->SetSubData(vertices, sizeof(vertices));
	}

	void TestBatchRendering::OnRender(const sgl::Renderer& renderer)
	{
		const glm::mat4 viewMatrix = glm::translate(glm::identity<glm::mat4>(), -1.f * m_CameraPosition);
		const glm::mat4 modelMatrix = glm::identity<glm::mat4>();
		const glm::mat4 mvp = m_ProjectionMatrix * viewMatrix * modelMatrix;

		m_Program->SetUniformMatrix4f("u_MVP", mvp);
		renderer.Draw(*m_VertexArray, *m_Program);
	}

	void TestBatchRendering::OnImGuiRender()
	{
		ImGui::DragFloat2("Quad 1", glm::value_ptr(m_QuadPositions[0]));
		ImGui::DragFloat2("Quad 2", glm::value_ptr(m_QuadPositions[1]));

		ImGui::NewLine();
		ImGui::DragFloat2("Camera", glm::value_ptr(m_CameraPosition));
	}
} // namespace test