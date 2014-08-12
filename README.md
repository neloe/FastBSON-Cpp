FastBSON-Cpp
============

A BSON library that will hopefully be faster and more robust than the one built into mongo-cxx-driver

Compiling the Documentation
---------------------------

Documentaiton can be compiled using doxygen. To do so, simply download and install doxygen (either from github or the downloader on their website).

Once doxygen is installed, make a directory called doxygen in the main directory and cd into it.

`mkdir doxygen && cd doxygen`

Clone this repository using `git clone git@github.com:Lumate/FastBSON-Cpp.git .` and checkout the gh-pages branch using `git checkout gh-pages`. If it complains, you may need to pull additional branchs with `git branch -va` and then rerun the checkout.

Once this is done, cd up a directory (into the FastBSON directory) and run `doxygen docs/Doxyfile` to generate the new documenatation. Once generated, cd back into the doxygen folder and commit and push to the gh-pages branch.

Documentation is located here: http://lumate.github.io/FastBSON-Cpp/html/index.html

Note: You must go to /html/index.html in your browser because doxygen is configured to do both latex and html documentation.

Further information may be found here: rickfoosusa.blogspot.com/2011/10/howto-use-doxygen-with-github.html


Build Instructions
------------------

This software uses CMake as it's build system; as such out of source builds are preferred.

You should create a build directory in the source directory and cd to it.

To prepare for release (from the build directory) : `cmake .. && make fastbson`

To run code coverage: `cmake .. -DCMAKE_BUILD_TYPE=Debug && make bson_coverage`

To generate Cobertura xml output for code coverage: `cmake .. -DCMAKE_BUILD_TYPE=Debug && make bson_cobertura`


Prerequisites
-------------

This software requires the following programs to compile (install as appropriate for your operating system): bison, flex, lcov, cmake, a C++11 compliant compiler (clang 3.X+, g++ 4.7+)

=======


