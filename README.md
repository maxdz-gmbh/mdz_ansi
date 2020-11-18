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

Only shared/dynamically loaded libraries (*.so* and *.dll* files with import libraries) are available for evaluation testing purposes. Static libraries are covered by our commercial licenses.

**Linux** binaries are built against Linux Kernel 2.6.18 - and thus should be compatible with Debian (from ver. 4.0), Ubuntu (from ver. 8.04), Fedora (from ver. 9)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP.<br>

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

**9. wchar_t support:** also wchar_t strings are supported, with 2 and 4 bytes-large *wchar_t* characters.

**10. Endianness-aware containers:** utf16 and utf32 containers are endiannes-aware thus may be used to produce and manipulate strings with pre-defined endianness even if endianness of host differs.

**11. Unicode "surrogate-pairs" awareness:** 2-byte Unicode strings correctly process/distinguish "surrogate-pairs" as 1 Unicode symbol.

**12. Asynchronous execution:** almost all functions can be executed asynchronously

## Performance Comparison

To be added...

## mdz_ansi Overview
Wiki: [mdz_ansi Wiki]<br>
file: *"mdz_ansi.h"*

Please take a look at *"mdz_asni.h"* file or [mdz_ansi Wiki] site for detailed functions descriptions.

[mdz_ascii Wiki]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_ascii-overview

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
[Performance Comparison]: #performance-comparison

#### Code Example (low-level use)

*mdz_string_init()* with license information should be called for library initialization before any subsequent calls:

```
#include <mdz_string.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  ...
}
```

[mdz_ansi_create]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_ansi_create
[mdz_ansi_destroy]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_ansi_destroy

After library initialization call *[mdz_ansi_create]*() for **ansi** creation. There should be also symmetric *[mdz_ansi_destroy]*() call for every create, otherwise allocated for **ansi** memory remains occupied:

```
#include <mdz_string.h>
#include <mdz_ansi.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
  // initialize pAnsi
  
  mdz_Ansi* pAnsi = mdz_ansi_create(0); // create ansi-string
  ...
  ...
  // use pAnsi
  ...
  ...
  // destroy pAnsi
  
  mdz_ansi_destroy(&pAnsi); // after this pAnsi should be NULL
  
  ...
}
```

Use *mdz_Ansi** pointer for subsequent library calls:

```
#include <mdz_string.h>
#include <mdz_ansi.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
  mdz_Ansi* pAnsi = mdz_ansi_create(0); // create ansi-string

  // reserve 5 elements, set them into 'a'. After this Capacity of string is 6 (includes terminating 0) and Size is 5.
  
  bRet = mdz_ansi_reserveAndInit(pAnsi, 5, 'a'); // "aaaaa" after this call
  
  // insert 'b' in front position with auto-reservation if necessary
  
  bRet = mdz_ansi_insert(pAnsi, 0, "b", 1, mdz_true); // "baaaaa" after this call
  
  // append string with "cde" with auto-reservation if necessary
  
  bRet = mdz_ansi_insert(pAnsi, pAnsi->m_nSize - 1, "cde", 3, mdz_true); // "baaaaacde" after this call
  
  ...
  
  mdz_ansi_destroy(&pAnsi);
  
  ...
}
```

#### Code Example (higher-level use)

This is an example above using *MdzAnsi* C++ "wrapper":

```
#include <mdz_string.h>
#include <MdzAnsi.h>

int main(int argc, char* argv[])
{
  mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
  MdzAnsi oAnsi; // initialize ansi-string

  bool bRet = oAnsi.reserveAndInit(5, 'a'); // "aaaaa" after this call
  
  bRet = oAnsi.insertAndReserve(0, 'b'); // "baaaaa" after this call
  
  bRet = oAnsi.appendAndReserve("cde"); // "baaaaacde" after this call
  
  ...
}
```

## mdz_wchar Overview
Wiki: [mdz_wchar Wiki]<br>
file: *"mdz_wchar.h"*

Please take a look at *"mdz_wchar.h"* file or [mdz_wchar Wiki] site for detailed functions descriptions.

[mdz_wchar Wiki]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_wchar-overview

## mdz_utf8 Overview
Wiki: [mdz_utf8 Wiki]<br>
file: *"mdz_utf8.h"*

Please take a look at *"mdz_utf8.h"* file or [mdz_utf8 Wiki] site for detailed functions descriptions.

[mdz_utf8 Wiki]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_utf8-overview

## mdz_utf16 Overview
Wiki: [mdz_utf16 Wiki]<br>
file: *"mdz_utf16.h"*

Please take a look at *"mdz_utf16.h"* file or [mdz_utf16 Wiki] site for detailed functions descriptions.

[mdz_utf16 Wiki]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_utf16-overview

## mdz_utf32 Overview
Wiki: [mdz_utf32 Wiki]<br>
file: *"mdz_utf32.h"*

Please take a look at *"mdz_utf32.h"* file or [mdz_utf32 Wiki] site for detailed functions descriptions.

[mdz_utf32 Wiki]: https://github.com/maxdz-gmbh/mdz_containers/wiki/mdz_utf32-overview

## Licensing info

Use of **mdz_containers** library is regulated by license agreement in *LICENSE.txt*

Basically private non-commercial "test" usage is unrestricted. Commercial usage of library (incl. its source code) will be regulated by according license agreement.

## Credits
[Maksym Dzyubenko] - library implementation, porting on platforms, participation in unit-tests and performance-tests<br>
[Diana Pukhlitska] - participation in unit-tests (VC++, Windows) and performance-tests (VC++, Windows)<br>
[Oleksiy Dzyubenko] - participation in unit-tests (VC++, Windows)

[Diana Pukhlitska]: https://github.com/PukhlitskaDi
[Oleksiy Dzyubenko]: https://github.com/dzyubenko
[Maksym Dzyubenko]: https://github.com/mdzyubenko
