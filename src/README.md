### Running the program

*Note: all paths are relative to the root folder*

#### Dependencies

* SFML >= 2.3
* CMake >= 2.8.8

------------------------------------------------------------------------------------------------------

1. Create a new folder anywhere, this guide will use `src/build/`.
    - The naming convention is not too important
2. Run the following command (<path> should be direct to the `src/` folder):
```
cmake ..
```
3. And the compile the project with the following command:
```
make
```
4. Now you have an executable named `qlearn` under `src/build/qlearn/`
    - This can be executed in a Unix shell by running `./qlearn/qlearn`, given that you are in the `src/build/` folder.
    - *Note:* not running the program in the build folder might result in font issues
    - Possible parameters for the executable are: `<amount> <precision> <bone_amount>`
    - The arguments creates `<amount>` amount of extra worms with precision of `<precision>` and bone amount of `<bone_amount>`
