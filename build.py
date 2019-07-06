#!/usr/bin/env python3
import sbuildr
import os
project = sbuildr.Project()

libstest = project.library("stest", sources=["STest.cpp"], libs=["stdc++"])
project.install(libstest, os.path.join("/", "usr", "local", "lib"))
project.install("STest.hpp", os.path.join("/", "usr", "local", "include", "Stealth"))

project.test("macros", sources=["macros.cpp"], libs=["stdc++", libstest])
sbuildr.cli(project, default_profiles=["debug"])
