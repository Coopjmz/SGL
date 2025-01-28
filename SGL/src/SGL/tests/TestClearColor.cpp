#include "sglpch.h"
#include "TestClearColor.h"

#include "SGL/Renderer.h"

namespace test
{
	TestClearColor::TestClearColor(const char* const name)
		: Test(name)
		, m_ClearColor(0.2f, 0.3f, 0.8f, 1.0f)
	{
	}

	void TestClearColor::OnRender(const sgl::Renderer& renderer)
	{
		renderer.SetClearColor(m_ClearColor);
		renderer.Clear();
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", &m_ClearColor.r);
	}
} // namespace test