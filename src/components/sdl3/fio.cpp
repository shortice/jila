#include "components/sdl3/fio.hpp"
#include "misc.hpp"

namespace Jila {

IOStream _SDL_IO_Open(
    std::string_view path,
    std::string_view mode
) {
    SDL_IOStream* s = SDL_IOFromFile(
        path.data(), mode.data()
    );

    return MakeSafeMemory<SDL_IOStream>(
        s,
        [](SDL_IOStream* s) {
            if (s) SDL_CloseIO(s);
        }
    );
}

size_t _SDL_IO_Write(
    IOStream stream,
    std::string_view data
) {
    return SDL_WriteIO(stream.get(), data.data(), data.size());
}

std::string _SDL_IO_Read(IOStream stream, size_t size) {
    std::string buffer(size, '\0');
    size_t nr = SDL_ReadIO(stream.get(), buffer.data(), size);
    buffer.resize(nr);
    return buffer;
}

long long _SDL_IO_Seek(
    IOStream stream, 
    long long offset, 
    int whence
) {
    return SDL_SeekIO(stream.get(), offset, (SDL_IOWhence)whence);
}

long long _SDL_IO_Tell(IOStream stream) {
    return SDL_TellIO(stream.get());
}

long long _SDL_IO_GetSize(IOStream stream) {
    return SDL_GetIOSize(stream.get());
}

void bindSdlFio(sol::state* state) {
    state->set_function("Jila_IO_Open", &_SDL_IO_Open);
    state->set_function("Jila_IO_Write", &_SDL_IO_Write);
    state->set_function("Jila_IO_Read", &_SDL_IO_Read);
    state->set_function("Jila_IO_Seek", &_SDL_IO_Seek);
    state->set_function("Jila_IO_Tell", &_SDL_IO_Tell);
    state->set_function("Jila_IO_GetSize", &_SDL_IO_GetSize);

    state->new_enum("Jila_IO_Whence",
        "SET", SDL_IO_SEEK_SET,
        "CUR", SDL_IO_SEEK_CUR,
        "END", SDL_IO_SEEK_END
    );
}

}
