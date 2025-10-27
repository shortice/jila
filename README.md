# jila

Experimental framework for creating Lua application.
Built on SDL3 + DearImGui and other libs (see in src/external).

WIP.

Note:
I tested this only on Linux and Android(in release code only, because
mobile platforms need embed lua code inside on shared lib).

Maybe able work on other platforms then supporting LuaJit/SDL.

# How build?

Clone this repo and all submodules. 
Execute
```sh
cmake ./src -B ./build
cmake --build ./build
```

And yes. First configure maybe raising error for leveldb package.
Dont worry, execute again:
```sh
cmake ./src -B ./build
```

Then build:
```sh
cmake --build ./build
```

And run example app:
```
./build/main ./examples/sample_app
```

Some documentation soon. Sorry!
For Android build please wait when i push some code on separate
repository jila-android.

And this lib contains two fonts:
Font Awesome 6 and JetBrains Mono.

# License

MIT.

