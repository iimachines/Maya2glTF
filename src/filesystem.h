#pragma once

//#ifdef _MSC_VER
//#	include <filesystem>
//#else
//#	include <filesystem.hpp>
//#endif

// For now, we use the same filesystem stub on all systems...
// Get rid of this as soon as std::filesystem is widespread!
#include <filesystem.hpp>

using namespace std::filesystem;
