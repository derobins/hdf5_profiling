This directory contains two quick programs for profiling the H5Dread() API
call. The intent is to investigate the call graph for future thread-safety
improvements, not measure performance.

1) A small python program (create.py) which creates a test file. You'll need
   h5py to run it.

usage: create.py [-h] [-c] [-F] file

Create a test file for H5Dread() profiling.

positional arguments:
  file        The name of the file.

optional arguments:
  -h, --help  show this help message and exit
  -c          Create a chunked dataset.
  -F          Use the latest file format

2) A small C program (reader.c) which reads the data in the dataset contained
   in the test file. This is instrumented to use callgrind to profile just
   the H5Dread() API call and you'll have to have valgrind installed to build
   it. You'll also want kcachegrind installed to view the output.

To build:

   path/to/h5cc -o reader reader.c

To profile:

   valgrind --tool=callgrind ./reader

This will create a file with the name callgrind.out.####. Load that in
kcachegrind to see the call graph.
   
