--[[

Notes:
* keep in mind that solution-wide settings should be defined
  before ever mentioning configuration-specific settings because
  the indentation in this file is for humans (not premake), and
  premake might infer conditionals when walking the graph of 
  solutions/configurations/projects -Geoff

--]]

solution "Helium"

	location "Premake"
	
    platforms
    {
		"x32",
		"x64"
	}

	configurations
	{
		"Debug",
		"Debug Unicode",
		"Release",
		"Release Unicode"
	}

--[[
	Iterate through our platforms and configurations and set them up with appropriate
	target directories (that have both the configuration and platform built into them)
--]]
	for i, platform in ipairs( platforms() ) do
		for j, config in ipairs( configurations() ) do
			configuration( { config, platform } )
				targetdir ( "Bin/" .. config .. "/" .. platform )
		end
	end
			
	flags
	{
		"NoMinimalRebuild"
	}
	
	includedirs
	{
		"."
	}
	
	configuration "windows"
		defines
		{
			"WIN32=1",
		}

	configuration "Debug*"
		defines
		{
			"_DEBUG",
			"DEBUG"
		}
		flags
		{
			"Symbols"
		}

	configuration "Release*"
		defines
		{
			"NDEBUG"
		}
		flags
		{
			"Symbols",
			"Optimize"
		}

	configuration "*Unicode"
		defines
		{
			"UNICODE=1"
		}
		flags
		{
			"Unicode"
		}
		    
	project "Platform"
		kind "SharedLib"
		language "C++"
		files { "Platform/*.h", "Platform/*.cpp" }

		configuration "windows"
			files{ "Platform/Windows/*.h", "Platform/Windows/*.cpp" }
			links { "ws2_32" }

		configuration "macosx"
			files{ "Platform/POSIX/*.h", "Platform/POSIX/*.cpp" }
			
		configuration "linux"
			files{ "Platform/POSIX/*.h", "Platform/POSIX/*.cpp" }
			
		configuration "bsd"
			files{ "Platform/POSIX/*.h", "Platform/POSIX/*.cpp" }

	project "Foundation"
		kind "SharedLib"
		language "C++"
		files { "Foundation/**.h", "Foundation/**.cpp" }
		links { "Platform" }

	project "Core"
		kind "SharedLib"
		language "C++"
		files { "Core/**.h", "Core/**.cpp" }
		links { "Foundation", "Platform" }

	project "Pipeline"
		kind "SharedLib"
		language "C++"
		files { "Pipeline/**.h", "Pipeline/**.cpp" }
		links { "Foundation", "Platform" }

	project "Editor"
		kind "ConsoleApp"
		language "C++"
		files { "Editor/**.h", "Editor/**.cpp" }
		links { "Pipeline", "Core", "Foundation", "Platform" }
