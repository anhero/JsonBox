This is a JSON C++ library. It can write and read JSON files with ease and speed. It uses code from our RedBox engine (https://bitbucket.org/anhero/redbox) and will soon be integrated in it.

This library is aimed at mostly internal use for the RedBox engine. It's not designed be used to write easy-to-read JSON files. It follows the JSON standards (except it doesn't read UTF-16 and UTF-32, only UTF-8)

Things it does:
 * Parse standard UTF-8 JSON files.
 * Write standard JSON files in UTF-8.
 * Uses STL streams for JSON input and output.
 * JSON arrays and objects are actually classes that inherit from a deque (for arrays) and a map (for objects).
 * Can output JSON with or without indentation.
 * Can output JSON and escape all string special characters or only the characters that HAVE to be escaped.
 * Continues reading a JSON file even when their are unwanted characters, it simply ignores the nonsense characters.

Things it doesn't do: 
 * Read UTF-16 or UTF-32 JSON files.
 * Keep the order of the members in objects (it's not required by the JSON specification, so I did it the simpler way)
 * Parse Unicode characters in strings that are described with two consecutive \u escape sequences, it will interpret it as 2 unicode characters.
 * The error messages aren't always very clear.
 
This library isn't what I would call typesafe. It's "typesafe" when you use it from the outside, but internally, it isn't. I can see the library going crazy if it's used in a multi-threaded program, it wasn't designed for multi-threading.

The Value type has a small memory footprint because it uses a union of different pointer types and an enum to know which type of data the value points to with its union of pointers.

HOW TO BUILD
To build the library by itself, you can use cmake. The simple way is to use the command "cmake ./" while being in the directory containing the CMakeLists.txt.

Or

You can simply copy the include and source files in your project. The library only depends on the STL and nothing else special, so it should build on pretty much anything.
