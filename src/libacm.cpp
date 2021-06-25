#include "libacm.hpp"
#include <stdexcept>
#include <cstdio>

constexpr int C_FAILURE = -1;
constexpr int C_SUCCESS = 0;

static int _read_stream(void* ptr, int size, int n, void* arg) noexcept
{
    auto stream = static_cast<std::istream*>(arg);
    auto count = stream->readsome(
        reinterpret_cast<char*>(ptr), 
        size * n
    );

    return count / size;
}

static int _close_stream([[maybe_unused]] void* arg) noexcept
{
    return C_SUCCESS;
}

static int _seek_stream(void* arg, int offset, int origin) noexcept
{
    using std::ios;
    auto stream = static_cast<std::istream*>(arg);

    ios::seekdir dir;
    switch( origin )
    {
        case SEEK_CUR: dir = ios::cur; break;
        case SEEK_SET: dir = ios::beg; break;
        case SEEK_END: dir = ios::end; break;
        default: return C_FAILURE;
    }

    stream->seekg(offset, dir);
    if( not stream )
        return C_FAILURE;
    return C_SUCCESS;
}

static int _get_stream_length(void* arg)
{
    auto stream = static_cast<std::istream*>(arg);
    auto pos = stream->tellg();
    if(pos < 0)
        return C_FAILURE;

    stream->seekg(0, std::ios::end);
    if( not stream )
        return C_FAILURE;

    auto len = stream->tellg();
    stream->seekg(pos);

    return len;
}

ACMStream acm_open_stream(std::istream& input, int force_channels)
{
    if( !input )
        throw std::runtime_error("libacm: invalid input stream");

    ACMStream acm;
    auto* acm_ptr = &acm;
    auto io = acm_io_callbacks{
        .read_func = _read_stream,
        .seek_func = _seek_stream,
        .close_func = _close_stream,
        .get_length_func = _get_stream_length,
    };

    auto res = acm_open_decoder(&acm_ptr, &input, io, force_channels);
    if( res < 0 )
        throw std::runtime_error("libacm: failed to open decoder");

    return acm;
}
