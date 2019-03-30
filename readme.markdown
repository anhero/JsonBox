<!-- -*- markdown -*- -->
# Json Box

[JSON](http://json.org/) (JavaScript Object Notation) is a lightweight data-interchange format.

Json Box is a C++ library used to read and write JSON with ease and speed.

Things it does:
* Follows the standards established on [http://json.org/](http://json.org/)
* Read and write JSON in UTF-8
* Uses the STL streams for input and output
* Generated JSON can be indented and pretty or compact and hard-to-read
* Does not crash when the JSON input contains errors, it simply tries to interpret as much as it can

Things it does not do:
* Read JSON in UTF-16 or UTF-32
* Keep the order of the members in objects (the standard doesn't require keeping the order)
* Write useful error messages when the JSON input contains errors

The library wasn't designed with multi-threading in mind.

The class reference can be found [here](http://anhero.github.com/JsonBox).

Android
===

```
mkdir build
cd build && mkdir armeabi-v7a
cd armeabi-v7a
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=<android_ndk> \
        -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_static \ 
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \ 
        -DCMAKE_INSTALL_PREFIX=<android_ndk>/sources/third_party/JsonBox ../..
make install
```

You should replace <android_ndk> with the actual folder.
