workspace "sysme"
	configurations {"Release", "Debug"}

project "sysme"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	files {"main.cpp"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"