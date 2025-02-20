workspace "SGL"
    architecture "x86_64"
    startproject "SGL"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

BuildDir = "%{wks.location}/build"
OutDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
BinDir = "%{BuildDir}/bin/%{OutDir}"
ObjDir = "%{BuildDir}/obj/%{OutDir}"

ExternalDir = "%{wks.location}/external"

IncludeDir = {}
IncludeDir["GLEW"] = "%{ExternalDir}/glew/include"
IncludeDir["GLFW"] = "%{ExternalDir}/glfw/include"

LibDir = {}
LibDir["GLEW"] = "%{ExternalDir}/glew/lib"
LibDir["GLFW"] = "%{ExternalDir}/glfw/lib"

include "SGL"