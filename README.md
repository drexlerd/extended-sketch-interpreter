# Interpreter for Extended Sketches SIW_R* and Module SIW_M

This repository contains an implementation of an interpreter
for extended sketches SIW_R* and for modules SIW_M.

## Getting Started

### Installing the Dependencies

The interpreter depends on a fraction of [Boost's](boost.org) header-only libraries (Fusion, Spirit x3).
We provide a CMake Superbuild project that takes care of downloading, building, and installing all dependencies.

```console
# Configure dependencies
cmake -S dependencies -B dependencies/build -DCMAKE_INSTALL_PREFIX=dependencies/installs
# Build and install dependencies
cmake --build dependencies/build -j16
```

### Installation the Interpreter

```console
# Configure with installation prefixes of all dependencies
cmake -S . -B build -DCMAKE_PREFIX_PATH=${PWD}/dependencies/installs
# Build
cmake --build build -j16
# Install (optional)
cmake --install build --prefix=<path/to/installation-directory>
```

## Running SIW_R

### Blocks-clear

```console
./build/src/public/siw_r benchmarks/blocks-4-clear/domain.pddl benchmarks/blocks-4-clear/p-200-0.pddl benchmarks/blocks-4-clear/sketch.lsp
```

### Blocks 4 on

```console
./build/src/public/siw_r benchmarks/blocks-4-on/domain.pddl benchmarks/blocks-4-on/p-200-0.pddl benchmarks/blocks-4-on/sketch.lsp
```

```console
./build/src/public/siw_r benchmarks/blocks-4-on/domain.pddl benchmarks/blocks-4-on/p-200-0.pddl benchmarks/blocks-4-on/sketch_icaps2024.lsp
```

## Running SIW_M

### Blocks-Clear

```console
./build/src/public/siw_m benchmarks/blocks-4-clear/domain.pddl benchmarks/blocks-4-clear/p-200-0.pddl benchmarks/blocks-4-clear/module.lsp
```

### Blocks-On

```console
./build/src/public/siw_m benchmarks/blocks-4-on/domain.pddl benchmarks/blocks-4-on/p-200-0.pddl benchmarks/blocks-4-on/module.lsp
```

```console
./build/src/public/siw_m benchmarks/blocks-4-on/domain.pddl benchmarks/blocks-4-on/p-200-0.pddl benchmarks/blocks-4-on/module_icaps2024.lsp
```

### Blocks-Table

```console
./build/src/public/siw_m benchmarks/blocks-4-ontable/domain.pddl benchmarks/blocks-4-ontable/p-200-0.pddl benchmarks/blocks-4-ontable/module.lsp
```

### Blocks-Tower

```console
./build/src/public/siw_m benchmarks/blocks-4-tower/domain.pddl benchmarks/blocks-4-tower/p-4-0.pddl benchmarks/blocks-4-tower/module_icaps2024.lsp
```

### Blocks

```console
./build/src/public/siw_m benchmarks/blocks-4/domain.pddl benchmarks/blocks-4/p-6-0.pddl benchmarks/blocks-4/module_icaps2024.lsp
```

### Hanoi

```console
./build/src/public/siw_m benchmarks/hanoi/domain.pddl benchmarks/hanoi/p10.pddl benchmarks/hanoi/module.lsp
```
