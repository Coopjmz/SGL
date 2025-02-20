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

    defines
    {
        "GLEW_STATIC"
    }

    filter "files:vendor/**.cpp"
        flags "NoPCH"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        defines "SGL_DEBUG"
        optimize "Off"
        symbols "On"
        linkoptions "/NODEFAULTLIB:LIBCMT"

    filter "configurations:Release"
        runtime "Release"
        defines "SGL_RELEASE"
        optimize "On"
        symbols "Off"