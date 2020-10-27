**NOTE:** All 0.x releases are kind of "alpha-versions" without expectations of interface backward-compatibility.

## Table of Contents
[mdz_string Overview](#mdz_string-Overview)<br>
[mdz_string Advantages](#mdz_string-Advantages)<br>
[Performance Comparison](#performance-comparison)<br>
[mdz_ansi Overview](#mdz_ansi-Overview)<br>
[mdz_wchar Overview](#mdz_wchar-Overview)<br>
[mdz_utf8 Overview](#mdz_utf8-Overview)<br>
[mdz_utf16 Overview](#mdz_utf16-Overview)<br>
[mdz_utf32 Overview](#mdz_utf32-Overview)<br>
[Licensing info](#Licensing-info)<br>
[Credits](#Credits)

## mdz_string Overview

[mdz_string] - is a very lightweight, versatile and speedy C  library developed by [maxdz Software GmbH], supporting ASCII/ANSI, UTF8, UTF16, UTF32, wchar strings. Source code of library is portable, conforms to ANSI C 89/90 Standard.

**Linux** binaries are built against Linux Kernel 2.6.18 - and thus should be compatible with Debian (from ver. 4.0), Ubuntu (from ver. 8.04), Fedora (from ver. 9)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP.<br>
Some CRT functions are inlined in Visual C++ 2015. Therefore if you are using Platform Toolset "v140" or later with *mdz_containers* Static Library - please link also with *"legacy_stdio_definitions.lib"*. It will resolve such functions.

**Android** x86/armeabi-v7a binaries - may be used from Android API level 16 ("Jelly Bean" ver. 4.1.x)<br>
**Android** x86_64/arm64-v8a binaries - may be used from Android API level 21 ("Lollipop" ver. 5.0)

**macOS** binaries - x86_64, from *MacOS X v10.6.0*

[mdz_string]: https://github.com/maxdz-gmbh/mdz_string
[maxdz Software GmbH]: https://maxdz.com/

## mdz_string Advantages

**1. Very high portability:** the whole code conforms to ANSI C 89/90 Standard. Multithreading/asynchronous part is POSIX compatible (under UNIX/Linux).

**2. Very little dependencies:** basically *mdz_containers* functions are only dependend on standard C-library memory-management/access functions. Multithreading part is dependend on POSIX *pthreads* API (under UNIX/Linux) and old process control/synchronization API (from Windows 2000). It means you can use library in your code withouth any further dependencies except standard plattform libraries/APIs.

**3. Very fast:** comparison tables for *mdz_ansi_find()* are here [Performance Comparison](#performance-comparison). There will be more tables/info later.

**4. Flexibilty:** nearly all functions contain not only "left position" but also "right position" parameters to limit processed area from right. "ANSI" string contains more functions than according *STL*, *boost* or *glib* analogs have.

**5. Extended error-checking:** all functions preserve internal error-code pointing the problem. It is possible to use strict error-checking (when all preserved error-codes should be *MDZ_ERROR_NONE*) or "relaxed"-checking - when only returned *mdz_false* will indicate error.

**6. Extended control:** containers do only explicit operations. It means for example, when "insert" function is called with auto-reservation flag set in *mdz_false* - it will return error if there is not enough capacity in container. No implicit reservations will be made.

**7. Attached usage:** containers should not necessarily use dynamically-allocated memory - which may be not available on your embedded system (or if malloc()/free() are forbidden to use in you safety-critical software). Just attach container/data to your statically-allocated memory (similarly to "placement new" in C++) and use all containers functionality.

**8. Unicode support:** UTF-8, UTF-16, UTF-32 are supported.

**9. wchar_t support:** also wchar_t strings are supporte, with 2 and 4 bytes-large *wchar_t* characters.

**10. Endianness-aware containers:** utf16 and utf32 containers are endiannes-aware thus may be used to produce and manipulate strings with pre-defined endianness even if endianness of host differs.

**11. Unicode "surrogate-pairs" awareness:** 2-byte Unicode strings correctly process/distinguish "surrogate-pairs" as 1 Unicode symbol.

**12. Asynchronous execution:** almost all functions can be executed asynchronously

## Performance Comparison

To be added...

## mdz_ansi Overview

Our **ansi** string implementation is on par or faster than corresponding [Glib] functions and significantly faster than [STL] implementations, especially on larger sizes.<br>
(please refer to comparison tables in [Performance Comparison])

**ansi** is implemented in defensive programming manner with strict input parameters checking. It means *mdz_false* or some other error indication will be returned if one or several input parameters are invalid - even if such an invalidity doesn't lead to inconsistence (for example adding or removing 0 items).<br>

Several usage-scenarios are possible:
- low-level - raw C interface, using *mdz_ansi.h* header file
- higher-level - using *MdzAnsi* C++ "wrapper" around *mdz_ansi.h* functions

Please take a look at *"mdz_ansi.h"* file or [mdz_ansi Wiki] site for detailed functions descriptions.

[mdz_ansi Wiki]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_ansi-overview
[Glib]: https://en.wikipedia.org/wiki/GLib
[STL]: https://en.wikipedia.org/wiki/Standard_Template_Library
