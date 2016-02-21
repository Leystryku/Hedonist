solution "Hedonist"
   language "C++"
   location "project"
   

   configuration "vs*" -- speed shit
   buildoptions({"/Ox", "/Qpar", "/Qfast_transcendentals", "/MP"})

   flags { "OptimizeSpeed", "Unicode", "EnableSSE", "EnableSSE2", "StaticRuntime" }

   vpaths {
      ["Header Files/*"] = "src/**.h",
      ["Source Files/*"] = "src/**.cpp",
   }

   kind "ConsoleApp"

   configurations { "Debug", "Release" }

   files { "src/**.h", "src/**.cpp" }
   includedirs { "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include" }
   libdirs {"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86", "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64"}
   
   -- A project defines one build target
   project "Hedonist"
      targetname "Hedonist"

      configuration "Debug"
      	targetdir "build/debug"
		defines { "DEBUG" }
         flags { "Unicode", "EnableSSE", "EnableSSE2", "StaticRuntime" }

      configuration "Release"
      	targetdir "build/release"
         defines { "NDEBUG" }
         flags { "Symbols", "Unicode", "EnableSSE", "EnableSSE2", "StaticRuntime" }
