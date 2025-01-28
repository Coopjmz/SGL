#include "sglpch.h"
#include "TestTexture2D.h"

#include "SGL/VertexBuffer.h"
#include "SGL/VertexBufferLayout.h"
#include "SGL/IndexBuffer.h"
#include "SGL/VertexArray.h"
#include "SGL/Shader.h"
#include "SGL/Program.h"
#include "SGL/Texture.h"
#include "SGL/Renderer.h"

namespace test
{
	static constexpr float ASPECT_RATIO = 16.f / 10.f;
	static constexpr int IMAGE_HEIGHT = 540;
	static constexpr int IMAGE_WIDTH = static_cast<int>(IMAGE_HEIGHT * ASPECT_RATIO);

	static constexpr GLfloat VERTICES[] =
	{
		-IMAGE_WIDTH / 2.f, -IMAGE_HEIGHT / 2.f, 0.f, 0.f,
		+IMAGE_WIDTH / 2.f, -IMAGE_HEIGHT / 2.f, 1.f, 0.f,
		+IMAGE_WIDTH / 2.f, +IMAGE_HEIGHT / 2.f, 1.f, 1.f,
		-IMAGE_WIDTH / 2.f, +IMAGE_HEIGHT / 2.f, 0.f, 1.f
	};

	static constexpr GLuint INDICES[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	static constexpr const char* VERTEX_SHADER_FILEPATH = "res\\shaders\\texture_2d.vert";
	static constexpr const char* FRAGMENT_SHADER_FILEPATH = "res\\shaders\\texture_2d.frag";
	static constexpr const char* TEXTURE_FILEPATHS[] =
	{
		"res\\textures\\beach.png",
		"res\\textures\\volcano.png"
	};

	TestTexture2D::TestTexture2D(const char* const name, const int windowWidth, const int windowHeight)
		: Test(name)
		, m_VertexBuffer(std::make_unique<sgl::VertexBuffer>(VERTICES, sizeof(VERTICES)))
		, m_IndexBuffer(std::make_unique<sgl::IndexBuffer>(INDICES, sizeof(INDICES)))
		, m_VertexArray(std::make_unique<sgl::VertexArray>())
		, m_Program(std::make_unique<sgl::Program>())
		, m_ProjectionMatrix(glm::ortho(0.f, static_cast<float>(windowWidth), 0.f, static_cast<float>(windowHeight), -1.f, +1.f))
		, m_CameraPosition(0.f, 0.f, 0.f)
	{
		sgl::VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<glm::vec2>();
		vertexBufferLayout.Push<glm::vec2>();

		m_VertexArray->AddVertexBuffer(*m_VertexBuffer, vertexBufferLayout);
		m_VertexArray->SetIndexBuffer(*m_IndexBuffer);

		const auto vertexShader = sgl::Shader::Parse(VERTEX_SHADER_FILEPATH);
		const auto fragmentShader = sgl::Shader::Parse(FRAGMENT_SHADER_FILEPATH);
		if (vertexShader && fragmentShader)
			m_Program->Link(*vertexShader, *fragmentShader);

		const glm::vec3 initialPosition(windowWidth / 2.f, windowHeight / 2.f, 0.f);
		for (const char* const filepath : TEXTURE_FILEPATHS)
			m_Images.push_back({ initialPosition, std::make_unique<sgl::Texture>(filepath) });
		
		for (GLuint i = 0; i < m_Images.size(); ++i)
			m_Images[i].Texture->Bind(i);
	}

	void TestTexture2D::OnRender(const sgl::Renderer& renderer)
	{
		const glm::mat4 viewMatrix = glm::translate(glm::identity<glm::mat4>(), -1.f * m_CameraPosition);
		const glm::mat4 vp = m_ProjectionMatrix * viewMatrix;

		for (GLint i = 0; i < m_Images.size(); ++i)
		{
			const glm::mat4 modelMatrix = glm::translate(glm::identity<glm::mat4>(), m_Images[i].Position);
			const glm::mat4 mvp = vp * modelMatrix;

			m_Program->SetUniform1i("u_Texture", i);
			m_Program->SetUniformMatrix4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_Program);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		for (size_t i = 0; i < m_Images.size(); ++i)
			ImGui::DragFloat2(("Image " + std::to_string(i + 1)).c_str(), glm::value_ptr(m_Images[i].Position));

		ImGui::NewLine();
		ImGui::DragFloat2("Camera", glm::value_ptr(m_CameraPosition));
	}
} // namespace test