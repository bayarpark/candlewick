import sys

import setuptools
from pybind11 import get_cmake_dir
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.1.0"

ext_modules = [
    Pybind11Extension(
        "candlewick.psimpl._psimpl",
        ["candlewick/psimpl/bindings.cpp"],
        extra_compile_args=['-O3'],
    ),
]


setup(
    name="candlewick",
    version=__version__,
    author="Bayar Park",
    author_email="bayarpark(at)gmail[dot]com",
    url="https://github.com/bayarpark/candlewick",
    packages=["candlewick", "candlewick.psimpl"],
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.8",
)


