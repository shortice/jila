#pragma once

#include <memory>
#include <string>

namespace Jila {

/*
Safe pointer for Lua <-> C++ calling.
*/
template<typename T>
std::shared_ptr<T>
MakeSafeMemory(T* mem, void deleter(T*)) {
	return std::shared_ptr<T>(
	    mem,
		deleter
	);
}

void CriticalError(std::string func);

}