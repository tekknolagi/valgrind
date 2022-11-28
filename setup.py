from distutils.core import setup, Extension

valgrind = Extension(
    "valgrind",
    include_dirs=["valgrind"],
    sources=["valgrind.c"],
)

setup(
    name="valgrind",
    version="0.0.0",
    description="Control callgrind instrumentation from Python.",
    author="Max Bernstein",
    author_email="python@bernsteinbear.com",
    url="https://github.com/tekknolagi/valgrind",
    long_description="",
    ext_modules=[valgrind],
)
