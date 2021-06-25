#ifndef __LIBACM_HPP
#define __LIBACM_HPP

extern "C" {
    #include "libacm.h"
}
#include <istream>

ACMStream acm_open_stream(const std::istream& input, int force_channels = -1);

#endif

