# PoolsideGUI
Cross-platform GUI software for surface control unit

Documentation is here: https://github.com/hidronautics/PoolsideGUI_docs

## Requirements:
 - Ubuntu 20.04 and greater
 - Qt 6.4.2
 - SFML lib
 ```
 sudo apt-get install libsfml-dev
 ```

## Development in Clion

Press **Ctrl+Alt+S** to open **Settings**.

Go to **Build, Execution, Deployment**, then to **CMake**

Add to **CMake options**:

```
-DCMAKE_PREFIX_PATH=PATH_TO_YOUR_QT_INSTALLATION/QT_VERSION/COMPILER/lib/cmake
```

## Development in VS Code

- Instal **C/C++ Extension Pack** (https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- Add to *.vscode/settings.json*
```
    "cmake.configureArgs": [
        "-DCMAKE_PREFIX_PATH=/home/*username*/Qt/6.4.2/gcc_64/lib/cmake"
    ],
```
