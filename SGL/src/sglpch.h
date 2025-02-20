#pragma once

// STL
#include <iostream>
#include <format>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <memory>
#include <functional>
#include <filesystem>
#include <chrono>

// GLEW
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

// STB
#include "stb/stb_image.h"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

// SGL Core
#include "SGL/Core/defines.h"
#include "SGL/Core/utils.h"
#include "SGL/Core/sgl.h"

// Namespaces
namespace fs = std::filesystem;
namespace chrono = std::chrono;