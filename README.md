
# Redis From Scratch (C++)

## Setup on Linux / WSL

```bash
# Update package list
sudo apt update

# Install dependencies
sudo apt install -y build-essential cmake git gdb net-tools curl
```

## Build

```bash
# Go to project folder
cd redis-from-scratch

# Create build directory and configure
mkdir build && cd build
cmake ..

# Compile
make
```

## Run

```bash
# From project root
./out/bin/server
./out/bin/client
```

## Rebuild After Changes

```bash
cd build
make
```

## Clean Build

```bash
rm -rf build out
mkdir build && cd build
cmake ..
make
```
