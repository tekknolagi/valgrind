from distutils.core import setup, Extension

callgrind = Extension(
    "callgrind",
    sources=["callgrind.c"],
)

setup(
    name="callgrind",
    version="0.0",
    description="Control callgrind instrumentation from Python.",
    author="Max Bernstein",
    author_email="max@bernsteinbear.com",
    url="https://github.com/tekknolagi/callgrind",
    long_description="",
    ext_modules=[callgrind],
)
