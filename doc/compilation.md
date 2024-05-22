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
- Navigate to project directory
- Run:
```bash
cmake -G "Visual Studio 17" CMakeLists.txt
cmake --build .
```
> Note: This command uses as generator Visual Studio 2022. You can change the generator as you please, but I will not be documenting other generators in this tutorial. 

### Run:

```bash
.\bin\Arcman
```
> Note: For technical reasons, run the executable from the root of the project, otherwise the assets are not going to load.

## Linux

## Debian based (Debian, Ubuntu, Mint...)

### Install tools:

- Install the necesarry tools using the command:
```bash
sudo apt install cmake g++ git
```

### Compile:

- Open a terminal
- Clone the repository using:
```bash
git clone git@gitlab-etu.ing.he-arc.ch:isc/2023-24/niveau-1/1242.2-langagecpp/isc1cd/cpp_filrouge_iscc_arsenescu.git
```
- Navigate to project directory
- Run:
```bash
cmake -S . -B build
cmake --build build
```

### Run

```bash
build/bin/Arcman
```
> Note: For technical reasons, run the executable from the root of the project, otherwise the assets are not going to load.

## Arch based (Arch Linux, Manjaro, EndeavourOS...)

## Red Hat based (Fedora, openSUSE, Red Hat Entreprise...)
