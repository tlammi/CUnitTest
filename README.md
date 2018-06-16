CUnitTest
=======

This is a simple unit test library for C. The currently the library uses pthreads
to implement concurrence. Currently the library is compiled only as a static lib.

# Building
Simply type 'make' in the project directory. This will produce 'libcunittest.a'
file into the root.

# Usage

Example:
```c

void test_func1(void){
  CUnitTest_assert(1 == 0);
}

int main(){
  CUnitTest_addTestSet("my test set a");
  // Note: currently test functions can be added only into the latest set
  CUnitTest_addTestFunc("my test set a", test_func1);

  CUnitTest_execute();
}
```
