workspace "sysme"
	configurations {"Release", "Debug"}

project "sysme"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs {"include/", "src/"}
	files {"src/main.cpp", "src/**.cpp", "src/**.c", "include/**.h", "include/**.hpp", "src/**.h", "src/**.hpp"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "Size"