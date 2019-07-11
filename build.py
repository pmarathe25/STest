#!/usr/bin/env python3
import sbuildr
project = sbuildr.Project(version="0.1.0")

libstest = project.library("stest", sources=["STest.cpp"], libs=["stdc++"])
project.install(libstest, "/usr/local/lib")
project.install("STest.hpp", "/usr/local/include/Stealth")

for source in glob.iglob("tests/*.cpp"):
    project.test(source.split('.')[0], sources=[source], libs=["stdc++", libstest])

sbuildr.cli(project, default_profiles=["debug"])
