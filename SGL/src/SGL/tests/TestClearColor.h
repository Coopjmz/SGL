#pragma once

#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor(const char* const name);

		void OnRender(const sgl::Renderer& renderer) final;
		void OnImGuiRender() final;

	private:
		glm::vec4 m_ClearColor;
	};
} // namespace test