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

[mdz_string] - is a very lightweight, versatile and speedy C  library, supporting ASCII/ANSI, UTF8, UTF16, UTF32, wchar strings. Source code of library is portable, conforms to ANSI C 89/90 Standard.

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
