# About

This contains a small C library implementing generic vectors (i.e dynamic arrays), and some code to test and benchmark it.

To use this in another project, simply copy the ``` Vectors.h ``` and ``` VectorsImpl.h ``` files and refer to the documentation found in the first header.


## Testing

Compile with ``` make ```.

Run with ``` time ./test.exe ```.


## Evolutions

- Add min(), max() functions based on an optional macro for inequality. Add a sort() function too?
- Try using a stack located vector (underlying array still in the heap).
- Try passing const structs as args in functions.
