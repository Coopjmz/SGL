project "SGL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir (BinDir)
    objdir (ObjDir)

    pchheader "sglpch.h"
    pchsource "src/sglpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/glm/**.hpp",
        "vendor/glm/**.inl",
        "vendor/stb/**.h",
        "vendor/stb/**.cpp",
        "vendor/imgui/**.h",
        "vendor/imgui/**.cpp"
    }

    includedirs
    {
        "src",
        "vendor",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.GLFW}"
    }

    libdirs
    {
        "%{LibDir.GLEW}",
        "%{LibDir.GLFW}"
    }

    links
    {
        "glfw3_mt",
        "glew32s",
        "opengl32"
    }

    linkoptions "/NODEFAULTLIB:LIBCMT"

    defines "GLEW_STATIC"

    filter "files:vendor/**.cpp"
        flags "NoPCH"

    filter "system:windows"
        systemversion "latest"
        defines "SGL_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        runtime "Debug"
        defines "SGL_DEBUG"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        defines "SGL_RELEASE"
        optimize "on"