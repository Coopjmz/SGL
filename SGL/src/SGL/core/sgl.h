#pragma once

#define GLCall(function) do { sgl::ClearError(); function; SGL_ASSERT(sgl::LogCall(#function, __FILE__, __LINE__)); } while(false)

namespace sgl
{
	void ClearError();
	bool LogCall(const char* const function, const char* const file, const int line);

	GLuint GetMaxVertexAttributes();
	GLuint GetTextureSlotCount();
} // namespace sgl