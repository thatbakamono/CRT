#pragma once

#include <filesystem>
#include <fstream>

[[nodiscard]] std::string readToString(const std::filesystem::path& path) {
    std::ifstream fileStream(path);
    std::string result;

    fileStream.seekg(0, std::ios::end);
    result.resize(fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);
    fileStream.read(result.data(), result.size());

    return result;
}
