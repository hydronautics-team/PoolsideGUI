# PoolsideGUI
GUI software for surface control unit

Documentation is here: https://github.com/hidronautics/PoolsideGUI_docs

## Requirements: 
 - Ubuntu 20.04 and greater
 - Qt 5.12 and greater (except versions 6.0 and 6.1)
 - HIDAPI lib (https://github.com/libusb/hidapi)
 - SFML lib

## Install and run on UNIX:

```
./install_dependencies.sh
```

Install binary path $source_dir/install/bin/PoolsideGUI

**If you want to recompile project, run:**

```
./compile_PoolsideGUI.sh
```

## Development in Clion

Press **Ctrl+Alt+S** to open **Settings**. 

Go to **Build, Execution, Deployment**, then to **CMake**

Add to **CMake options**:

```
-DCMAKE_PREFIX_PATH=PATH_TO_YOUR_QT_INSTALLATION/QT_VERSION/COMPILER/lib/cmake
```

Then go to **Run->Edit Configurations** and add to **Environmental variables**:

```
LD_LIBRARY_PATH=PATH_TO_YOUR_QT_INSTALLATION/QT_VERSION/COMPILER/lib
```
