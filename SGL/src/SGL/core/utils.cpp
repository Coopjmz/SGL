#include "sglpch.h"
#include "utils.h"

namespace sgl::utils
{
	std::optional<std::string> ReadFile(const std::string& filepath)
	{
		AssertReturnIf(filepath.empty(), {});

		std::ifstream file(filepath);
		AssertReturnUnless(file.is_open(), {});

		return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}

	std::vector<std::string> GetAllFilesInDirectory(const std::string& dirpath, const bool includeSubdirectories)
	{
		AssertReturnIf(dirpath.empty(), {});
		AssertReturnUnless(fs::exists(dirpath), {});

		std::vector<std::string> filepaths;

		if (includeSubdirectories)
		{
			for (const auto& entry : fs::recursive_directory_iterator(dirpath))
			{
				ContinueIf(entry.is_directory());
				filepaths.push_back(entry.path().string());
			}
		}
		else
		{
			for (const auto& entry : fs::directory_iterator(dirpath))
			{
				ContinueIf(entry.is_directory());
				filepaths.push_back(entry.path().string());
			}
		}

		return filepaths;
	}
} // namespace sgl::utils