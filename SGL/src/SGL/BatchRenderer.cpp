#include "sglpch.h"
#include "BatchRenderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

namespace
{
	constexpr uint32_t VERTICES_PER_QUAD = 4;
	constexpr uint32_t INDICES_PER_QUAD = 6;

	constexpr size_t MAX_QUAD_COUNT = 1000;
	constexpr size_t MAX_VERTEX_COUNT = MAX_QUAD_COUNT * VERTICES_PER_QUAD;
	constexpr size_t MAX_INDEX_COUNT = MAX_QUAD_COUNT * INDICES_PER_QUAD;
	constexpr size_t MAX_TEXTURES = 32;

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexIndex;

		static sgl::VertexBufferLayout GenerateVertexBufferLayout()
		{
			sgl::VertexBufferLayout vertexBufferLayout;
			vertexBufferLayout.Push<decltype(Position)>();
			vertexBufferLayout.Push<decltype(Color)>();
			vertexBufferLayout.Push<decltype(TexCoords)>();
			vertexBufferLayout.Push<decltype(TexIndex)>();
			return vertexBufferLayout;
		}
	};

	struct BatchRendererData
	{
		sgl::VertexBuffer* VertexBuffer = nullptr;
		sgl::IndexBuffer* IndexBuffer = nullptr;
		sgl::VertexArray* VertexArray = nullptr;

		sgl::Texture* WhiteTexture = nullptr;
		GLuint WhiteTextureSlot = 0;

		uint32_t IndexCount = 0;

		Vertex* QuadBuffer = nullptr;
		Vertex* QuadBufferPtr = nullptr;

		std::array<sgl::Texture*, MAX_TEXTURES> TextureSlots = {};
		uint32_t TextureSlotIndex = 1;

		sgl::BatchRenderer::Stats Stats;
	};

	BatchRendererData s_Data;
} // namespace

namespace sgl
{
	void BatchRenderer::Init()
	{
		s_Data.QuadBuffer = new Vertex[MAX_QUAD_COUNT];

		GLuint indices[MAX_INDEX_COUNT];
		GLuint offset = 0;
		for (size_t i = 0; i < MAX_INDEX_COUNT; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		s_Data.VertexBuffer = new VertexBuffer(MAX_VERTEX_COUNT * sizeof(Vertex));
		s_Data.IndexBuffer = new IndexBuffer(indices, sizeof(indices));
		s_Data.VertexArray = new VertexArray();

		s_Data.VertexArray->AddVertexBuffer(*s_Data.VertexBuffer, Vertex::GenerateVertexBufferLayout());
		s_Data.VertexArray->SetIndexBuffer(*s_Data.IndexBuffer);

		static constexpr uint32_t WHITE_COLOR = 0xffffffff;
		s_Data.WhiteTexture = new Texture(WHITE_COLOR);

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		for (size_t i = 0; i < MAX_TEXTURES; ++i)
			s_Data.TextureSlots[i] = nullptr;
	}

	void BatchRenderer::Shutdown()
	{
		delete s_Data.VertexBuffer;
		delete s_Data.IndexBuffer;
		delete s_Data.VertexArray;

		for (size_t i = 0; i < MAX_TEXTURES; ++i)
			delete s_Data.TextureSlots[i];

		delete[] s_Data.QuadBuffer;
	}

	void BatchRenderer::BeginBatch()
	{
		s_Data.QuadBufferPtr = s_Data.QuadBuffer;
	}

	void BatchRenderer::EndBatch()
	{
		const GLsizeiptr size = reinterpret_cast<uint8_t*>(s_Data.QuadBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.QuadBuffer);
		s_Data.VertexBuffer->SetSubData(s_Data.QuadBuffer, size);
	}

	void BatchRenderer::Flush()
	{
		for (size_t i = 0; i < s_Data.TextureSlotIndex; ++i)
			s_Data.TextureSlots[i]->Bind(static_cast<GLuint>(i));

		s_Data.VertexArray->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr));
		++s_Data.Stats.DrawCount;

		s_Data.IndexCount = 0;
		s_Data.TextureSlotIndex = 1;
	}

	void BatchRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (s_Data.IndexCount >= MAX_INDEX_COUNT)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		float textureIndex = 0.f;

		s_Data.QuadBufferPtr->Position = { position.x , position.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.f, 0.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.QuadBufferPtr->Position = { position.x + size.x , position.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.f, 0.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.f, 1.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.f, 1.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;
	}

	void BatchRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const GLuint textureId)
	{
		if (s_Data.IndexCount >= MAX_INDEX_COUNT || s_Data.TextureSlotIndex > 31)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i)
		{
			if (s_Data.TextureSlots[i])
			{

			}
		}

		static constexpr glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
		float textureIndex = static_cast<float>(textureId);

		s_Data.QuadBufferPtr->Position = { position.x , position.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.f, 0.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.QuadBufferPtr->Position = { position.x + size.x , position.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.f, 0.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.f, 1.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.f };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.f, 1.f };
		s_Data.QuadBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadBufferPtr;

		s_Data.IndexCount += 6;
		++s_Data.Stats.QuadCount;
	}

	const BatchRenderer::Stats& BatchRenderer::GetStats()
	{
		return s_Data.Stats;
	}

	void BatchRenderer::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Stats));
	}
} // namespace sgl