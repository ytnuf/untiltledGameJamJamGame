# untitledGameJamJamGame

this is a submission for the untitled game jam 104

# how to play

wasd to move

redirect missiles at enemies to get orbs
orbs heal and give you points you can deposit at the base
when you deposit at the base your score increases but
enemies also get faster and see you from much farther

# build process (with Make)

have:
gcc
make

and run
```bash
make
./game
```
untitledGameJamJamGame © 2025 by maningreen is licensed under CC BY-NC-SA 4.0


## Build process (with CMake)

You will need:
- GCC
- CMake
- Make
- [vcpkg](https://github.com/microsoft/vcpkg),
you will need to set the `VCPKG_ROOT` environment variable to the location of your vcpkg install

To build for linux, run this command:
```bash
cmake --workflow --preset linux
```
This will create a linux executable in `build/linux/out`

---
To build for web, you will also need [emscripten](https://emscripten.org/docs/getting_started/downloads.html).
Run this command:
```bash
cmake --workflow --preset web
```
This will create the output in `build/web/out`

You can test the web build locally by running:
```bash
python -m http.server -d build/web/out/
```
And going to `localhost:8000`

---
To build for windows (from a linux host), you will also need mingw.
Run this command:
```bash
cmake --workflow --preset mingw
```
This will create a windows executable in `build/mingw/out`

---
