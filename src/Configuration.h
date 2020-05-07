// configuration inspired from CONSOLEMENU - CONSOLEMENU.org (Benoit Blanchon 2014-2020)

#pragma once

// Small or big machine?
#ifndef FLYINGCOLLECTION_EMBEDDED_MODE
#if defined(ARDUINO)                /* Arduino*/                 \
    || defined(__IAR_SYSTEMS_ICC__) /* IAR Embedded Workbench */ \
    || defined(__XC)                /* MPLAB XC compiler */      \
    || defined(__ARMCC_VERSION)     /* Keil ARM Compiler */      \
    || defined(__AVR)               /* Atmel AVR8/GNU C Compiler */
#define FLYINGCOLLECTION_EMBEDDED_MODE 1
#else
#define FLYINGCOLLECTION_EMBEDDED_MODE 0
#endif
#endif

// Auto enable std::string if the right header is here and no conflicting
// macro is defined
#if !defined(FLYINGCOLLECTION_ENABLE_STD_STRING) && defined(__has_include)
#if __has_include(<string>) && !defined(min) && !defined(max)
#define FLYINGCOLLECTION_ENABLE_STD_STRING 1
#else
#define FLYINGCOLLECTION_ENABLE_STD_STRING 0
#endif
#endif
