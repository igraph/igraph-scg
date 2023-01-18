Spectral coarse graining methods for graphs
===========================================

This repo contains the spectral coarse graining routines from igraph 0.9. These
routines were removed from igraph 0.10.0 due to their numerical instability
in unit tests and due to the fact that none of the current developers are
familiar enough with the topic to be able to sort out the unit tests. If you
are interested in helping out, [let us
know](https://github.com/igraph/igraph-sch/issues/new)!

The contents of this repo are unmaintained; we aim to keep on ensuring that the
library compiles with the most recent version of igraph, and we try to fix bugs
if you find one, but no new features will be added.

Instructions
------------

The following commnds should be enough if you have a working igraph
installation that does _not_ contain the spectral coarse graining routines any
more! This applies to igraph versions 0.10 and later.

*Official igraph 0.9 releases will not work as these releases still contain the
spectral coarse graining functions so the two libraries will conflict with each
other.*

Assuming that you have installed the appropriate version of igraph in
a system-wide location, you can configure and build this project like this:

```sh
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
```

If you have installed igraph in a non-standard location, you need to tell CMake
where to look for it:

```sh
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/path/where/igraph/is/installed ..
cmake --build .
cmake --install .
```

CMake builds a static library by default; if you need a shared library,
pass `-DBUILD_SHARED_LIBS=ON` as an argument to `cmake`.

You can also use this project as a subproject in another CMake project.

Documentation
-------------

The documentation of the various functions are to be found in the source files.
We do not build a separate HTML documentation for this library at the moment.
If you are interested in helping out and making this repo Doxygen-compatible,
let us know.

Questions, comments?
--------------------

Feel free to [open an issue](https://github.com/igraph/igraph-scg/issues/new)
if you think you have found a bug in this library, or if you think you can
help us out with fixing the numerical instabilities of the unit tests. Note
that the instabilities appear only with certain BLAS implementations on certain
platforms, so if they work for you, it does not mean they are okay in general.

If you have general questions about the SCG methods, try asking around in the
[igraph Discourse group](https://igraph.discourse.group), but note that none of
the current maintainers of igraph are familiar with spectral coarse graining,
so chances are that you will need to wait for someone else to answer your
questions.
