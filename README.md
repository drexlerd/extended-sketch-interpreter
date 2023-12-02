# Interpreter for Extended Sketches SIW_R* and Module SIW_M

This repository contains an implementation of an interpreter
for extended sketches SIW_R* and for modules SIW_M.

## Dependencies

- Boost 1.81 (boost.org)

## Installation

```console
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j24
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

## Running SIW_M

### Blocks-Clear

```console
./build/src/public/siw_m benchmarks/blocks-4-clear/domain.pddl benchmarks/blocks-4-clear/p-200-0.pddl benchmarks/blocks-4-clear/module.lsp
```

### Blocks-On

```console
./build/src/public/siw_m benchmarks/blocks-4-on/domain.pddl benchmarks/blocks-4-on/p-200-0.pddl benchmarks/blocks-4-on/module.lsp
```

### Blocks-Table

```console
./build/src/public/siw_m benchmarks/blocks-4-ontable/domain.pddl benchmarks/blocks-4-ontable/p-200-0.pddl benchmarks/blocks-4-ontable/module.lsp
```

### Blocks-Tower

```console
./build/src/public/siw_m benchmarks/blocks-4-tower/domain.pddl benchmarks/blocks-4-tower/p-4-0.pddl benchmarks/blocks-4-tower/module.lsp
```

### Hanoi

```console
./build/src/public/siw_m benchmarks/hanoi/domain.pddl benchmarks/hanoi/p10.pddl benchmarks/hanoi/module.lsp
```
