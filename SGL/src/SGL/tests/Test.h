#pragma once

namespace sgl
{
	class Renderer;
}

namespace test
{
	class Test
	{
	public:
		Test(const char* const name);
		virtual ~Test() = default;

		Test(const Test&) = delete;
		Test& operator=(const Test&) = delete;
		Test(Test&&) = delete;
		Test& operator=(Test&&) = delete;

		virtual void OnUpdate(const float dt) {}
		virtual void OnRender(const sgl::Renderer& renderer) {}
		virtual void OnImGuiRender() {}

		const char* GetName() const;

	private:
		const char* const m_Name;
	};
} // namespace test