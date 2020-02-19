#ifndef LOCOMOTIVE_COMPONENT_H
#define LOCOMOTIVE_COMPONENT_H

#include "locomotive/locomotive.h"

namespace Locomotive {
namespace Component {

    class LOCOMOTIVE_API Component {
        bool enabled: 1;

        bool enabled() const { return enabled; }
        void enabled(bool enabled) { this->enabled = enabled; }
    };
}}

#endif
