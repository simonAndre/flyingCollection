
#pragma once

#include "version.h"
#include "Configuration.h"

#define FLYINGCOLLECTION_DO_CONCAT(A, B) A##B
#define FLYINGCOLLECTION_CONCAT2(A, B) FLYINGCOLLECTION_DO_CONCAT(A, B)
#define FLYINGCOLLECTION_CONCAT4(A, B, C, D) \
  FLYINGCOLLECTION_CONCAT2(FLYINGCOLLECTION_CONCAT2(A, B), FLYINGCOLLECTION_CONCAT2(C, D))

#define FLYINGCOLLECTION_NAMESPACE                                                      \
  FLYINGCOLLECTION_CONCAT4(                                                             \
      flyingCollection, FLYINGCOLLECTION_VERSION_MAJOR, FLYINGCOLLECTION_VERSION_MINOR, \
      FLYINGCOLLECTION_VERSION_REVISION)
