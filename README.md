# extended-sketch-interpreter

## Dependencies

- Boost 1.81 (boost.org)

## Installation

```console
cmake -S . -B build
cmake --build build -j16
```

## Running

### Successful parse

```console
./build/src/planner/siwm  benchmarks/gripper/domain.pddl benchmarks/gripper/p-1-0.pddl benchmarks/gripper/success.sketch
```

### Failed parse

```console
./build/src/planner/siwm  benchmarks/gripper/domain.pddl benchmarks/gripper/p-1-0.pddl benchmarks/gripper/fail.sketch
```

### Implementation Details:

- Declaration must come before its definition or reference.
However, no requirement on the order in which definition or reference occurs.
