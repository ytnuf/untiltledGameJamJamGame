# untitledGameJamJamGame

this is a submission for the untitled game jam 104


# how to play

wasd to move

- redirect missiles at enemies to kill them
- when enemies die they drop orbs, pick them up to heal and gain stored score
- deposit stored score at the base, the base randomly spawns on the planet
- sometimes when you pick up an orb you'll get a power up, use it as best you can
- slowly enemies will spawn more and more, and shoot faster and faster, live as long as you can
and deposit as much as you can


# build process (with Make)

you need:
- gcc
- make

to build
```bash
make
```
to run
```
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
