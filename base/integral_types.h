// Copyright 2010 Google Inc. All Rights Reserved.
//
// Basic integer type definitions for various platforms
//
// This code is compiled directly on many platforms, including client
// platforms like Windows, Mac, and embedded systems.  Before making
// any changes here, make sure that you're not breaking any platforms.
//

#ifndef BASE_INTEGRAL_TYPES_H_
#define BASE_INTEGRAL_TYPES_H_

#include <cstdint>

// These typedefs are also defined in base/google.swig. In the
// SWIG environment, we use those definitions and avoid duplicate
// definitions here with an ifdef. The definitions should be the
// same in both files, and ideally be only defined in this file.
#ifndef SWIG
// Standard typedefs
// All Google2 code is compiled with -funsigned-char to make "char"
// unsigned.  Google2 code therefore doesn't need a "uchar" type.
typedef signed char         schar;
typedef signed char         int8;
typedef short               int16;
typedef int32_t             int32;
#ifdef _MSC_VER
typedef __int64             int64;
#else
typedef int64_t          int64;
#endif /* _MSC_VER */

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef uint64_t uint64;

// A type to represent a Unicode code-point value. As of Unicode 4.0,
// such values require up to 21 bits.
// (For type-checking on pointers, make this explicitly signed,
// and it should always be the signed version of whatever int32 is.)
typedef signed int         char32;

//  A type to represent a natural machine word (for e.g. efficiently
// scanning through memory for checksums or index searching). Don't use
// this for storing normal integers. Ideally this would be just
// unsigned int, but our 64-bit architectures use the LP64 model
// (http://www.opengroup.org/public/tech/aspen/lp64_wp.htm), hence
// their ints are only 32 bits. We want to use the same fundamental
// type on all archs if possible to preserve *printf() compatability.
typedef unsigned long      uword_t;

#endif /* SWIG */

// long long macros to be used because gcc and vc++ use different suffixes,
// and different size specifiers in format strings
#undef GG_LONGLONG
#undef GG_ULONGLONG
#undef GG_LL_FORMAT

#ifdef _MSC_VER     /* if Visual C++ */

// VC++ long long suffixes
#define GG_LONGLONG(x) x##I64
#define GG_ULONGLONG(x) x##UI64

// Length modifier in printf format string for int64's (e.g. within %d)
#define GG_LL_FORMAT "I64"  // As in printf("%I64d", ...)
#define GG_LL_FORMAT_W L"I64"

#else   /* not Visual C++ */

#define GG_LONGLONG(x) x##LL
#define GG_ULONGLONG(x) x##ULL
#define GG_LL_FORMAT "ll"  // As in "%lld". Note that "q" is poor form also.
#define GG_LL_FORMAT_W L"ll"

#endif  // _MSC_VER


static constexpr uint8  kuint8max  = (( uint8) 0xFF);
static constexpr uint16 kuint16max = ((uint16) 0xFFFF);
static constexpr uint32 kuint32max = ((uint32) 0xFFFFFFFF);
static constexpr uint64 kuint64max = ((uint64) GG_LONGLONG(0xFFFFFFFFFFFFFFFF));
static constexpr  int8  kint8min   = ((  int8) ~0x7F);
static constexpr  int8  kint8max   = ((  int8) 0x7F);
static constexpr  int16 kint16min  = (( int16) ~0x7FFF);
static constexpr  int16 kint16max  = (( int16) 0x7FFF);
static constexpr  int32 kint32min  = (( int32) ~0x7FFFFFFF);
static constexpr  int32 kint32max  = (( int32) 0x7FFFFFFF);
static constexpr  int64 kint64min  = (( int64) GG_LONGLONG(~0x7FFFFFFFFFFFFFFF));
static constexpr  int64 kint64max  = (( int64) GG_LONGLONG(0x7FFFFFFFFFFFFFFF));

typedef uint64 Fprint;
static const Fprint kIllegalFprint = 0;
// static const Fprint kMaxFprint = GG_ULONGLONG(0xFFFFFFFFFFFFFFFF);

#define DECLARE_POD(TypeName) typedef int Dummy_Type_For_DECLARE_POD

enum Ownership {
  DO_NOT_TAKE_OWNERSHIP,
  TAKE_OWNERSHIP
};

namespace base {
constexpr unsigned _CACHE_LINE_SIZE  = 64;
}  // namespace base

#define CACHE_LINE_PAD(x) (::base::_CACHE_LINE_SIZE - (x) % ::base::_CACHE_LINE_SIZE)

#endif  // BASE_INTEGRAL_TYPES_H_
