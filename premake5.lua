workspace "CADExchangerTest"
    architecture "x86_64"
    startproject "CADExchangerTest"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    configurations
    {
        "Debug",
        "Release"
    }


project "CurvesLib"
    location "CurvesLib"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "%{prj.name}/src/pch.cpp"

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "CurvesLib/src",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "_USE_MATH_DEFINES"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/CADExchangerTest")
    }

    filter "system:windows"
    systemversion "latest"
    defines
    {
        "CL_PLATFORM_WINDOWS",
        "CL_BUILD_DLL"
    }

    filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

    filter "configurations:Release"
    runtime "Release"
    optimize "on"

    

project "CADExchangerTest"
    location "CADExchangerTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/include/**.h"
    }

    includedirs
    {
        "CurvesLib/include",
        "CurvesLib/src"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    links
    {
        "CurvesLib"
    }

    filter "system:windows"
    systemversion "latest"
    defines
    {
        "CL_PLATFORM_WINDOWS",
    }

    filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

    filter "configurations:Release"
    runtime "Release"
    optimize "on"
