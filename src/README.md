### Running the program

*Note: all paths are relative to the root folder*

#### Dependencies

* SFML >= 2.3

------------------------------------------------------------------------------------------------------

1. Create a folder named `src/build/` if it does not already exist.
    - The naming convention is not too important, as long as it does not clash with anything existing.
2. Run the command:
```
cmake ..
```
3. Build the project by simply running:
```
make
```
4. Now you have a executable named `qlearn` under `src/build/qlearn/`
    - This can be executed in a Unix shell by typing `./qlearn/qlearn`, given that you are in the `src/build/` folder.
