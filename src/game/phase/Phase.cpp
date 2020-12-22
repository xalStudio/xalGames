#include "Phase.hpp"

namespace xal { namespace game { namespace phase {
    Phase::Phase(const std::filesystem::path& luaFilePath)
        : m_luaFilePath { luaFilePath }
    { }
} } }