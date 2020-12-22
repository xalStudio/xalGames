#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace xal { namespace game { namespace phase {
    class Phase {
    public:
        Phase(const std::filesystem::path& luaFilePath);

    protected:
        std::filesystem::path m_luaFilePath;

        sol::state m_luaState;
    };
} } }