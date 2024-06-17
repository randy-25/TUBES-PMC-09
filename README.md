# TUBES PMC KELOMPOK 09
- Randy Revaldo Pratama (13222012)
- Wilbert Jay Hydro (13222024)
- Kenny Aprian Duallo (13222030)
- Muhammad Al-Faaris (13220033)
- Amelia Dina Savitri (18322006)


## Deskripsi

Tugas besar ini adalah tugas besar membuat sebuah aplikasi manajemen data kesehatan Klinik - X, menggunakan bahasa pemrograman C dan menggunakan GUI dari library GTK-4

## Prerequisites

Bebeberapa komponen yang dibutuhkan untuk melakukan build aplikasi
- CMake (version 3.10 or higher)
- A C compiler (e.g., GCC, Clang, or MSVC)
- Make

## Installation Instructions

### Linux

#### Ubuntu/Debian-based distributions

1. **Update your package lists:**
    ```sh
    sudo apt update
    ```

2. **Install GTK 4 and its dependencies:**
    ```sh
    sudo apt install libgtk-4-dev
    ```

3. **Install pkg-config (if not already installed):**
    ```sh
    sudo apt install pkg-config
    ```

#### Fedora-based distributions

1. **Update your package lists:**
    ```sh
    sudo dnf check-update
    ```

2. **Install GTK 4 and its dependencies:**
    ```sh
    sudo dnf install gtk4-devel
    ```

3. **Install pkg-config (if not already installed):**
    ```sh
    sudo dnf install pkg-config
    ```

### macOS

1. **Install Homebrew** (if not already installed):
    ```sh
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

2. **Install GTK 4 using Homebrew:**
    ```sh
    brew install gtk4
    ```

3. **Ensure pkg-config is installed:**
    ```sh
    brew install pkg-config
    ```

### Windows

#### Using MSYS2

1. **Download and install MSYS2 from [msys2.org](https://www.msys2.org/). Add to the environment variables too.**

2. **Update the package database and core system packages:**
    ```sh
    pacman -Syu
    ```

3. **Close and reopen the MSYS2 terminal, then run the update command again:**
    ```sh
    pacman -Syu
    ```

4. **Install GCC (if there are no C Compiler at the moment) GTK 4 and its dependencies:**
    ```sh
    pacman -S mingw-w64-ucrt-x86_64-gcc
    ```
    ```sh
    pacman -S mingw-w64-x86_64-gtk4
    ```

5. **Install pkg-config and other necessary development tools:**
    ```sh
    pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-pkg-config
    ```

## Building the Project

After installing the required dependencies, you can build the project using the following steps:

### Using CMAKE
1. **Navigate to the project directory:**
    ```sh
    cd path/to/this/project
    ```

2. **Create a build directory:**
    ```sh
    mkdir build
    cd build
    ```

3. **Generate the build system files using CMake:**
    ```sh
    cmake ..
    ```
    
    **Or on windows using MSYS Makefiles Generator**
    ```sh
    cmake -G "MSYS Makefiles" ..
    ```

4. **Build the project:**
    ```sh
    cmake --build .
    ```

## Using make (only windows)
 ```sh
    Make
```

The compiled executable will be placed in the project’s root directory alongside `main.c`.