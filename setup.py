#! /usr/bin/env python3

import os
import platform
import re
import subprocess
import sys
from distutils.version import LooseVersion

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, source_dir=""):
        Extension.__init__(self, name, sources=[])
        self.source_dir = os.path.abspath(source_dir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        ext_dir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        if not ext_dir.endswith(os.path.sep):
            ext_dir += os.path.sep

        cmake_args = ["-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=" + ext_dir,
                      "-DPYTHON_EXECUTABLE=" + sys.executable]

        cfg = "Debug" if self.debug else "Release"
        build_args = ["--config", cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), ext_dir)]
            if sys.maxsize > 2 ** 32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j4']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),
                                                              self.distribution.get_version())

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(["cmake", ext.source_dir] + cmake_args,
                              cwd=self.build_temp)
        subprocess.check_call(["cmake", "--build", "."] + build_args,
                              cwd=self.build_temp)


if sys.version_info < (3, 5):
    sys.exit('Sorry, Python < 3.5 is not supported by PyVidarDB.')

setup(
    name="PyVidarDB",
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
