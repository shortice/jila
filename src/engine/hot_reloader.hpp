#ifndef JILA_RELEASE
#pragma once

#include "efsw/efsw.hpp"

namespace Jila {

class UpdateListener : public efsw::FileWatchListener {
public:
    void handleFileAction(
        efsw::WatchID watchid, const std::string &dir,
        const std::string &filename, efsw::Action action,
        std::string oldFilename) override;
};

}
#endif
