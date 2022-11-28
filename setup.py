from distutils.core import setup, Extension

valgrind = Extension(
    "valgrind",
    sources=["valgrind.c"],
)

setup(
    name="valgrind",
    version="0.0",
    description="Control callgrind instrumentation from Python.",
    author="Max Bernstein",
    author_email="max@bernsteinbear.com",
    url="https://github.com/tekknolagi/valgrind",
    long_description="",
    ext_modules=[valgrind],
)
