# Compilation

## Prerequisites

Before compiling, make sure the following tools are installed:

- **CMake** (3.16 or higher)
- **Git**
- A **C++** compatible compiler (e.g., GCC, Clang)

## Windows

### Install tools:

- Download and install [CMake](https://cmake.org)
- Install [Visual Studio](https://visualstudio.microsoft.com/downloads/) with C++ support or [MingGW](https://www.mingw-w64.org/)
- Install [Git](https://git-scm.com/download/win)

### Compile

- Open Command Prompt (or PowerShell)
- Clone the repository using:
```bash
git clone git@gitlab-etu.ing.he-arc.ch:isc/2023-24/niveau-1/1242.2-langagecpp/isc1cd/cpp_filrouge_iscc_arsenescu.git
```
- Navigate to project directory and run the installer script:
```batch
.\install.bat
```
> Note: This script uses Visual Studio as generator for CMake. You can change the generator as you please, but I will not be documenting other generators in this tutorial. 

### Run:

To execute, you can either launch the executable from the File Explorer (following the path below), or launch the program from the command line:

```batch
.\build\bin\Release\Arcman.exe
```
> Note: For technical reasons, run the executable from the root of the project, otherwise the assets are not going to load.

## Linux

### Install tools:

Install the necesarry tools using the command:

- Debian/Ubuntu:

```bash
sudo apt install cmake build-essential git libsfml-dev
```

- Arch Linux:

```bash
sudo pacman -S cmake base-devel git sfml
```

### Compile:

- Open a terminal
- Clone the repository using:

```bash
git clone git@gitlab-etu.ing.he-arc.ch:isc/2023-24/niveau-1/1242.2-langagecpp/isc1cd/cpp_filrouge_iscc_arsenescu.git
```
- Navigate to project directory and run the install script:

```bash
./install.sh
```

### Run

```bash
build/bin/Arcman
```
> Note: For technical reasons, run the executable from the root of the project, otherwise the assets are not going to load.

