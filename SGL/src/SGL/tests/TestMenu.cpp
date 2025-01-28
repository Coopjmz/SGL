#include "sglpch.h"
#include "TestMenu.h"

namespace test
{
	TestMenu::TestMenu(const char* const name)
		: Test(name)
		, m_CurrentTest(this)
	{
	}

	TestMenu::~TestMenu()
	{
		ReturnIf(IsCurrentTestSelf());
		delete m_CurrentTest;
	}

	void TestMenu::OnImGuiRender()
	{
		for (const auto& test : m_Tests)
		{
			if (ImGui::Button(test.first))
				m_CurrentTest = test.second();
		}
	}

	bool TestMenu::IsCurrentTestSelf() const
	{
		return m_CurrentTest == this;
	}

	Test* TestMenu::GetCurrentTest() const
	{
		return m_CurrentTest;
	}

	void TestMenu::SetCurrentTestToSelf()
	{
		ReturnIf(IsCurrentTestSelf());

		delete m_CurrentTest;
		m_CurrentTest = this;
	}
} // namespace test