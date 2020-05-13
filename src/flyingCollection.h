
#pragma once

#ifdef __cplusplus

#include "version.h"
#include "Configuration.h"
#include "Namespace.h"
#include "SanPair.hpp"
#include "SanCodedStr.h"
#include "JsonStream.h"

#else

#error flyingCollection requires a C++ compiler, please change file extension to .cc or .cpp

#endif

namespace flyingCollection
{
    using FLYINGCOLLECTION_NAMESPACE::JsonStream;
    using FLYINGCOLLECTION_NAMESPACE::SanCodedStr;
    using FLYINGCOLLECTION_NAMESPACE::SanPair;
} // namespace flyingCollection
