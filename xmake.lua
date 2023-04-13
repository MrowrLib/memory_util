set_languages("c++20")
add_rules("mode.debug")
set_toolchains("msvc")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("string_format", "_Log_", "spdlog")

target("memory_util")
    set_kind("headeronly")
    add_headerfiles("include/memory_util")
    add_includedirs("include", {public = true})
    add_packages("string_format", "_Log_", {public = true})

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_deps("memory_util")
    add_packages("spdlog")
