#!/usr/bin/env python3
import sbuildr
project = sbuildr.Project()

libstest = project.library("stest", sources=["STest.cpp"], libs=["stdc++"])
project.install(libstest, "/usr/local/lib")
project.install("STest.hpp", "/usr/local/include/Stealth")

project.test("macros", sources=["macros.cpp"], libs=["stdc++", libstest])
sbuildr.cli(project, default_profiles=["debug"])
