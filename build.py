#!/usr/bin/env python3
import sbuildr
import sbuildr.dependencies.builders as builders
import sbuildr.dependencies.fetchers as fetchers

import glob
import os

stdlib = sbuildr.Library("stdc++")
project = sbuildr.Project()

slog = sbuildr.dependencies.Dependency(fetchers.GitFetcher("https://github.com/pmarathe25/SLog", tag="v0.2.1"), builders.SBuildrBuilder())
libstest = project.library("stest", sources=["STest.cpp"], libs=[stdlib])

# Need stream overloads from the SLog header
project.interfaces(["STest.hpp"], depends=[slog])

for source in glob.iglob("tests/*.cpp"):
    project.test(os.path.basename(source).split('.')[0], sources=[source], libs=[stdlib, libstest])

project.export()
