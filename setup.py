from distutils.core import setup, Extension

valgrind = Extension(
    "valgrind",
    sources=["valgrind.c"],
)

with open("README.md", "r") as f:
    long_description = f.read()

setup(
    name="valgrind",
    version="0.0.0",
    description="Control callgrind instrumentation from Python.",
    author="Max Bernstein",
    author_email="python@bernsteinbear.com",
    url="https://github.com/tekknolagi/valgrind",
    long_description=long_description,
    long_description_content_type="text/markdown",
    ext_modules=[valgrind],
)
