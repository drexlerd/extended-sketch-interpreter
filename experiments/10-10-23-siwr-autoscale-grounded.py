#! /usr/bin/env python

import os
import platform

from pathlib import Path
from downward import suites
from downward.reports.absolute import AbsoluteReport
from lab.environments import BaselSlurmEnvironment, LocalEnvironment
from lab.experiment import Experiment
from lab.reports import Attribute, geometric_mean

import project


# Create custom report class with suitable info and error attributes.
class BaseReport(AbsoluteReport):
    INFO_ATTRIBUTES = ["time_limit", "memory_limit"]
    ERROR_ATTRIBUTES = [
        "domain",
        "problem",
        "algorithm",
        "unexplained_errors",
        "error",
        "node",
    ]


DIR = Path(__file__).resolve().parent
SIWR_PATH = DIR.parent / "build" / "src" / "public" / "siwr"
BENCHMARKS_DIR = Path(os.environ["BENCHMARKS_PDDL_AUTOSCALE"])
SKETCHES_DIR = Path(os.environ["BENCHMARKS_SKETCHES_KR2021"])
TIME_LIMIT = 1800
MEMORY_LIMIT = 8000
ENABLE_GROUNDING = "true"

if project.REMOTE:
    ENV = project.TetralithEnvironment(
        email="dominik.drexler@liu.se",
        extra_options="#SBATCH --account=naiss2023-22-782",
        memory_per_cpu="8G")
    SUITE = ["barman", "childsnack", "driverlog", "floortile", "grid", "grid-no-exchange", "tpp"]
else:
    ENV = LocalEnvironment(processes=2)
    SUITE = ["barman:p03.pddl", "childsnack:p01.pddl", "driverlog:p01.pddl", "floortile:p01.pddl", "grid:p01.pddl", "grid-no-exchange:p01.pddl", "tpp:p01.pddl"]
    TIME_LIMIT = 60

ATTRIBUTES = [
    "run_dir",
    "error",
    Attribute("coverage", absolute=True, min_wins=False, scale="linear"),
    Attribute("generated"),
    Attribute("expanded"),
    Attribute("pruned"),
    Attribute("effective_width"),
    Attribute("width_average"),
    Attribute("width_maximum"),
    Attribute("search_exhausted_without_solution"),

    Attribute("successor_time"),
    Attribute("apply_time"),
    Attribute("grounding_time"),
    Attribute("goal_time"),
    Attribute("search_time"),
    Attribute("total_time"),
    Attribute("plan_length"),
]




# Create a new experiment.
exp = Experiment(environment=ENV)
exp.add_parser("iw-parser.py")
exp.add_parser("serialized-search-parser.py")

exp.add_resource("siwr", SIWR_PATH)

for task in suites.build_suite(BENCHMARKS_DIR, SUITE):
    for arity in range(0,3):
        sketch_filename = SKETCHES_DIR / task.domain / f"width_{arity}" / "sketch_str.txt"
        if task.domain == "grid-no-exchange":
            sketch_filename = SKETCHES_DIR / "grid" / f"width_{arity}" / "sketch_str.txt"
        if not sketch_filename.is_file(): continue
        run = exp.add_run()
        run.add_resource("domain", task.domain_file, symlink=True)
        run.add_resource("problem", task.problem_file, symlink=True)
        run.add_resource("sketch", sketch_filename, symlink=True)
        # 'ff' binary has to be on the PATH.
        # We could also use exp.add_resource().
        run.add_command(
            "run-planner",
            [SIWR_PATH, "{domain}", "{problem}", str(arity), sketch_filename, ENABLE_GROUNDING],
            time_limit=TIME_LIMIT,
            memory_limit=MEMORY_LIMIT,
        )
        # AbsoluteReport needs the following properties:
        # 'domain', 'problem', 'algorithm', 'coverage'.
        run.set_property("domain", task.domain)
        run.set_property("problem", task.problem)
        run.set_property("algorithm", f"siwr_{arity}")
        # BaseReport needs the following properties:
        # 'time_limit', 'memory_limit'.
        run.set_property("time_limit", TIME_LIMIT)
        run.set_property("memory_limit", MEMORY_LIMIT)
        # Every run has to have a unique id in the form of a list.
        # The algorithm name is only really needed when there are
        # multiple algorithms.
        run.set_property("id", [f"siwr_{arity}", task.domain, task.problem])

# Add step that writes experiment files to disk.
exp.add_step("build", exp.build)

# Add step that executes all runs.
exp.add_step("start", exp.start_runs)

exp.add_parse_again_step()

# Add step that collects properties from run directories and
# writes them to *-eval/properties.
exp.add_fetcher(name="fetch")

# Make a report.
exp.add_report(BaseReport(attributes=ATTRIBUTES), outfile="report.html")

# Parse the commandline and run the specified steps.
exp.run_steps()