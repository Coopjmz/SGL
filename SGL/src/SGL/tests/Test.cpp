#include "sglpch.h"
#include "Test.h"

namespace test
{
	Test::Test(const char* const name)
		: m_Name(name)
	{
	}

	const char* Test::GetName() const
	{
		return m_Name;
	}
} // namespace test