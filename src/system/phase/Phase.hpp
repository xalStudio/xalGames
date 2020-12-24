#pragma once

#include <memory>

namespace xal { namespace system { namespace session { class Room; } } }

namespace xal { namespace system { namespace phase {
    class Phase {
    public:
        Phase() = default;

        virtual void run(xal::system::session::Room* room) = 0;
    };
} } }