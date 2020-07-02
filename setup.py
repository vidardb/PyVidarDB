#! /usr/bin/env python3

import os
import subprocess
import sys

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, source_dir=""):
        Extension.__init__(self, name, sources=[])
        self.source_dir = os.path.abspath(source_dir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        ext_dir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = ["-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=" + ext_dir,
                      "-DPYTHON_EXECUTABLE=" + sys.executable]

        cfg = "Debug" if self.debug else "Release"
        build_args = ["--config", cfg]

        cmake_args += ["-DCMAKE_BUILD_TYPE=" + cfg]
        build_args += ["--", "-j4"]

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(["cmake", ext.source_dir] + cmake_args,
                              cwd=self.build_temp)
        print(cmake_args)
        subprocess.check_call(["cmake", "--build", "."] + build_args,
                              cwd=self.build_temp)


setup(
    name="pyvidardb",
    version="0.0.1",
    author="VidarDB Team",
    author_email="info@vidardb.com",
    long_description="Python Wrapper for VidarDB",
    packages=find_packages("src"),
    package_dir={"": "src"},
    ext_modules=[CMakeExtension("pyvidardb/pyvidardb")],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)
