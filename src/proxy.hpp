#pragma once

template<typename T>
struct Proxy {
    Proxy(T* proxy) : proxy(proxy) {}
    T* proxy;
};
