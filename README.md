**NOTE:** All 0.x releases are kind of "alpha-versions" without expectations of interface backward-compatibility.

## Table of Contents
[mdz_ansi Overview](#mdz_ansi-Overview)<br>
[mdz_ansi Advantages](#mdz_ansi-Advantages)<br>
[Performance Comparison](#performance-comparison)<br>
[mdz_ansi Overview](#mdz_ansi-Overview)<br>
[Licensing info](#Licensing-info)<br>
[Credits](#Credits)

## mdz_ansi Overview
Wiki: [mdz_ansi Wiki]<br>
file: *"mdz_ansi.h"*

Please take a look at *"mdz_nsi.h"* file or [mdz_ansi Wiki] site for detailed functions descriptions.

[mdz_ascii Wiki]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi-overview

[mdz_ansi] - is a very lightweight, versatile and speedy C  library for handling 1-byte (ASCII/ANSI) strings, developed by [maxdz Software GmbH]. Source code of library is highly-portable, conforms to ANSI C 89/90 Standard.

Only shared/dynamically loaded libraries (*.so* and *.dll* files with import libraries) are available for evaluation testing purposes. Static libraries are covered by our commercial licenses.

**Linux** binaries are built against Linux Kernel 2.6.18 - and thus should be compatible with Debian (from ver. 4.0), Ubuntu (from ver. 8.04), Fedora (from ver. 9)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP.<br>

**Android** x86/armeabi-v7a binaries - may be used from Android API level 16 ("Jelly Bean" ver. 4.1.x)<br>
**Android** x86_64/arm64-v8a binaries - may be used from Android API level 21 ("Lollipop" ver. 5.0)

**macOS** binaries - x86_64, from *MacOS X v10.6.0*

[mdz_ansi]: https://github.com/maxdz-gmbh/mdz_ansi
[maxdz Software GmbH]: https://maxdz.com/

## mdz_ansi Advantages

**1. Very high portability:** the whole code conforms to ANSI C 89/90 Standard. Multithreading/asynchronous part is POSIX compatible (under UNIX/Linux).

**2. Very little dependencies:** basically *mdz_containers* functions are only dependend on standard C-library memory-management/access functions. Multithreading part is dependend on POSIX *pthreads* API (under UNIX/Linux) and old process control/synchronization API (from Windows 2000). It means you can use library in your code withouth any further dependencies except standard plattform libraries/APIs.

**3. Very fast:** comparison tables for *mdz_ansi_find()*, *mdz_ansi_firstOf()* are here [Performance Comparison](#performance-comparison). There will be more tables/info later.

**4. Flexibilty:** nearly all functions contain "left position" and "right position" parameters, to limit processed area from left and right. "ANSI" string contains more functions than according *STL*, *boost* or *glib* analogs have.

**5. Extended error-checking:** all functions preserve internal error-code pointing the problem. It is possible to use strict error-checking (when all preserved error-codes should be *MDZ_ERROR_NONE*) or "relaxed"-checking - when only returned *mdz_false* will indicate error.

**6. Extended control:** containers do only explicit operations. It means for example, when "insert" function is called with auto-reservation flag set in *mdz_false* - it will return error if there is not enough capacity in container. No implicit reservations will be made.

**7. Attached usage:** containers should not necessarily use dynamically-allocated memory - which may be not available on your embedded system (or if malloc()/free() are forbidden to use in you safety-critical software). Just attach container/data to your statically-allocated memory and use all containers functionality.

**8. Asynchronous execution:** almost all functions can be executed asynchronously

## Performance Comparison

Performance comparison tables for *[mdz_ansi_find]*() give an idea about *mdz_ansi* library overall performance on different platforms compared to STL and standard C library. Modern implementationsof STL and standard C library are pretty fast, using optimized versions of memory-access functions.

Following tests are executed:

- Test *1/100M*": Find 1 byte - in the end of 100M bytes long string<br>
- Test *5/100M*": Find 5 bytes long string - in the end of 100M bytes long string<br>
- Test *10/100M*": Find 10 bytes long string - in the end of 100M bytes long string<br>
- Test *100/100M*": Find 100 bytes long string - in the end of 100M bytes long string<br>
- Test *1K/100M*": Find 1K bytes long string - in the end of 100M bytes long string<br>
- Test *500K/1M*": Find 500K bytes long string - in the end of 1M bytes long string<br>
- Test *100M-100/100M*": Find "100M minus 100" bytes long string - in the end of 100M bytes long string<br>
- Test *100M/100M*": Find 100M bytes long string - in 100M bytes long string<br>

**Windows 10 (64-bit)** on *Intel i5-6600 @ 3.30GHz (4 cores/4 threads)*<br>

**Monotone test** : "long string" and "string to find" are both filled with '1's; on the last position of both strings is '2'

monotone = MDZ_FIND_MONOTONE method<br>
clib = MDZ_FIND_CLIB method (standard C library)<br>
brute = MDZ_FIND_BRUTE method<br>
bmh = MDZ_FIND_BMH method

- VC++ toolset v140 (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi, monotone | mdz_ansi, clib | mdz_ansi, brute |  mdz_ansi, bmh |std::string.find() | clib (strstr())|
| :---:| ---: | ---: | ---: | ---: | ---: | ---: |
| 1/100M| 70,351 |  |  |  | 162,681 | 70,579 |
| 5/100M| 407,668 | 460,052 | 3,045,869 | 781,655 | 3,381,061 | 482,075 |
| 10/100M| 1,334,782 | 707,712 | 4,394,022 | 780,128 | 4,206,329 | 731,395 |
| 100/100M| 1,333,516 | 10,914,646 | 15,779,350 | 781,370 | 15,652,407 | 11,253,026 |
| 1K/100M| 1,332,838 | 70,179,989 | 139,398,637 | 781,439 | 139,808,212 | 75,808,535 |
| 500K/1M| 13,202 | 166,409,422 | 323,375,345 | 9,411 | 324,276,637 | 178,302,908 |
| 100M-100/100M| 1,262,919 | 10,884,012 | 14,182,350 | 1,066,737 | 14,150,110 | 10,383,086 |
| 100M/100M| 117,970 | |  |  | 144,573 | 114,565 |

- MinGW/gcc toolset (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi, monotone | mdz_ansi, clib | mdz_ansi, brute |  mdz_ansi, bmh |
| :---:| ---: | ---: | ---: | ---: |
| 1/100M| 148,067 |  |  |  |
| 5/100M| 534,070 | 1,599,882 | 6,825,862 | 784,326 |
| 10/100M| 551,404 | 3,635,378 | 7,898,385 | 783,832 |
| 100/100M| 550,701 | 32,447,796 | 20,451,496 | 786,006 |
| 1K/100M| 551,213 | 348,052,489 | 117,762,194 | 784,335 |
| 500K/1M| 7,851 | 814,620,053 | 246,574,213 | 6,263 |
| 100M-100/100M| 997,729 | 33,028,357 | 11,705,985| 456,680 |
| 100M/100M| 328,564 | |  |  |

[mdz_ansi_find]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi_find_async

## mdz_ansi Overview

Our **ansi** string implementation is on par or faster than corresponding [Glib] functions and significantly faster than [STL] implementations, especially on larger sizes.<br>
(please refer to comparison tables in [Performance Comparison])

**ansi** is implemented with strict input parameters checking. It means *mdz_false* or some other error indication will be returned if one or several input parameters are invalid - even if such an invalidity doesn't lead to inconsistence (for example adding or removing 0 items).<br>

**Test license generation:** - use [mdz_ansi Test License] page for generating test license. With this license you are able to test *mdz_ansi* library during next 14 days.
Test license data should be used in *mdz_ansi_init()* call for library initialization.

**NOTE:** All 0.x releases are kind of "beta-versions" and can be used 1) only with test-license (during test period of 14 days, with necessity to re-generate license for the next 14 days test period) and 2) without expectations of interface backward-compatibility.

Several usage-scenarios are possible:
- low-level - raw C interface, using *mdz_ansi.h* header file
- higher-level - using *MdzAnsi* C++ "wrapper" around *mdz_ansi.h* functions

[mdz_ansi Wiki]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi-overview
[Glib]: https://en.wikipedia.org/wiki/GLib
[STL]: https://en.wikipedia.org/wiki/Standard_Template_Library
[Performance Comparison]: #performance-comparison
[mdz_ansi Test License]: https://maxdz.com/mdz_ansi_testlicense.php

#### Code Example (low-level use)

*mdz_ansi_init()* with license information should be called for library initialization before any subsequent calls:

```
#include <mdz_ansi.h>

int main(int argc, char* argv[])
{
  /* mdz_ansi library initialization using test info retrieved after license generation (see "Test license generation" above) */
  
  mdz_bool bRet = mdz_ansi_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  ...
}
```

[mdz_ansi_create]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi_create
[mdz_ansi_destroy]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi_destroy

After library initialization call *[mdz_ansi_create]*() for **ansi** creation. There should be also symmetric *[mdz_ansi_destroy]*() call for every create, otherwise allocated for **ansi** memory remains occupied:

```
#include <mdz_ansi.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_ansi_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
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
#include <mdz_ansi.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_ansi_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
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
#include <MdzAnsi.h>

int main(int argc, char* argv[])
{
  mdz_ansi_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
  MdzAnsi oAnsi; // initialize ansi-string

  bool bRet = oAnsi.reserveAndInit(5, 'a'); // "aaaaa" after this call
  
  bRet = oAnsi.insertAndReserve(0, 'b'); // "baaaaa" after this call
  
  bRet = oAnsi.appendAndReserve("cde"); // "baaaaacde" after this call
  
  ...
}
```

## Licensing info

Use of **mdz_ansi** library is regulated by license agreement in *LICENSE.txt*

Basically private non-commercial "test" usage is unrestricted. Commercial usage of library (incl. its source code) will be regulated by according license agreement.

## Credits
[Maksym Dzyubenko] - library implementation, porting on platforms, participation in unit-tests and performance-tests<br>
[Diana Pukhlitska] - participation in unit-tests (VC++, Windows) and performance-tests (VC++, Windows)<br>
[Oleksiy Dzyubenko] - participation in unit-tests (VC++, Windows)

[Diana Pukhlitska]: https://github.com/PukhlitskaDi
[Oleksiy Dzyubenko]: https://github.com/dzyubenko
[Maksym Dzyubenko]: https://github.com/mdzyubenko
