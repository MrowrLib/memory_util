set_languages("c++23")
add_rules("mode.debug")
set_toolchains("msvc")

add_repositories("MrowrLib https://github.com/MrowrLib/package-repo.git")
add_requires("StringFormatting")

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_packages("StringFormatting")
