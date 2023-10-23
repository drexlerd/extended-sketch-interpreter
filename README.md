## Installation

1. Clone
```console
git clone git@github.com:drexlerd/Lifted-Novelty-Search.git
```
2. Build planners
```console
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build -j24
```

## Running the planners

### Breadth-first search
```console
./build/src/public/brfs <domain:str> <problem:str>
```

### Iterative width search
```console
./build/src/public/iw <domain:str> <problem:str> <arity:int>
```

### Serialized iterative width search
```console
./build/src/public/siw <domain:str> <problem:str> <arity:int>
```

### Iterative width with sketches search
```console
./build/src/public/iwr <domain:str> <problem:str> <arity:int> <sketch:str>
```

### Serialized iterative width with sketches search
```console
./build/src/public/siwr <domain:str> <problem:str> <arity:int> <sketch:str>
```


## Running the experiments

1. Create python3 virtual environment
```console
python3 -m venv --prompt liw .venv
```
2. Activate virtual environment
```console
source .venv/bin/activate
```
3. Install python packages (needed for experimental code)
```console
pip install -r requirements.txt
```
4. Export environment variables
```console
export BENCHMARKS_PDDL_DOWNWARD="<path/to/benchmarks/pddl/downward>"
export BENCHMARKS_PDDL_AUTOSCALE="<path/to/benchmarks/pddl/downward>"
export BENCHMARKS_SKETCHES_KR2021="<path/to/benchmarks/sketches/kr2021>"
```
