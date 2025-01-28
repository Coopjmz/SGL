#pragma once

#include "Test.h"

namespace test
{
	class TestMenu : public Test
	{
	public:
		TestMenu(const char* const name);
		~TestMenu() final;

		void OnImGuiRender() final;

		bool IsCurrentTestSelf() const;
		Test* GetCurrentTest() const;

		void SetCurrentTestToSelf();

		template <typename T, typename... Args>
		void RegisterTest(const char* const name, Args&&... args);

	private:
		Test* m_CurrentTest;
		std::vector<std::pair<const char*, std::function<Test* ()>>> m_Tests;
	};

	template <typename T, typename... Args>
	inline void TestMenu::RegisterTest(const char* const name, Args&&... args)
	{
		std::cout << "Registering test: " << name << std::endl;
		m_Tests.push_back({ name, [name, &args...]() { return new T(name, std::forward<Args>(args)...); } });
	}
} // namespace test