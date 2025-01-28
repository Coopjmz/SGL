#pragma once

// STL
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <memory>
#include <functional>
#include <filesystem>
#include <chrono>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// STB
#include <stb/stb_image.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

// SGL Core
#include <SGL/core/defines.h>
#include <SGL/core/utils.h>
#include <SGL/core/sgl.h>

// Namespaces
namespace fs = std::filesystem;
namespace chrono = std::chrono;