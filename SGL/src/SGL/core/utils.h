#pragma once

namespace sgl::utils
{
	std::optional<std::string> ReadFile(const std::string& filepath);
	std::vector<std::string> GetAllFilesInDirectory(const std::string& dirpath, const bool includeSubdirectories = false);
} // namespace sgl::utils