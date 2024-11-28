import atexit
import argparse
import git
import subprocess
import sys

@atexit.register
def cleanup():
    """Revert ml_dsa_65/ref back to its original state."""
    print("Reverting ml_dsa_65/ref back to original state.",
          file=sys.stderr)
    repo.git.checkout("HEAD", "ml_dsa_65/ref")


def percent_change(old, new):
    return ((old - new) / old) * 100


def parse_bench_output(output):
    output_parsed = {}

    output = output.splitlines()[1:]

    keygen_output = output[0].split(",")
    output_parsed["keygen_median"] = int(keygen_output[1])
    output_parsed["keygen_average"] = int(keygen_output[2])

    sign_output = output[1].split(",")
    output_parsed["sign_median"] = int(sign_output[1])
    output_parsed["sign_average"] = int(sign_output[2])

    verify_output = output[2].split(",")
    output_parsed["verify_median"] = int(verify_output[1])
    output_parsed["verify_average"] = int(verify_output[2])

    return output_parsed


def shell(command, expect=0, cwd=None):
    completed = subprocess.run(command, cwd=cwd, capture_output=True)

    if completed.returncode != expect:
        print(completed.stderr.decode("utf-8"))
        raise Exception("Error {}. Expected {}.".format(completed.returncode, expect))

    return completed.stdout.decode("utf-8")


parser = argparse.ArgumentParser(
    prog="compare_performance.py",
    description="Compare the difference in the performance of a specified implementation between two repository commits.",
)

parser.add_argument(
    "--old", help="the commit whose performance is to be used as the baseline."
)
parser.add_argument(
    "--new",
    help="the commit whose performance we want to measure relative to the baseline. If left empty, measure the current state of the code.",
    default="HEAD",
)
args = parser.parse_args()

repo = git.Repo(".")

if repo.is_dirty(path="ml_dsa_65/ref"):
    sys.exit("Cannot proceed: you have uncommitted changes in ml_dsa_65/ref.")

# Now measure the old performance
repo.git.checkout(args.old, "ml_dsa_65/ref")

shell(["make", "bench.o"])

old = shell(["./bench.o"])
old = parse_bench_output(old)

# Measure new performance
repo.git.checkout(args.new, "ml_dsa_65/ref")

shell(["make", "bench.o"])

new = shell(["./bench.o"])
new = parse_bench_output(new)

# Now compute some statistics
print(
    "Key-generation: % change in median: {}".format(
        percent_change(old["keygen_median"], new["keygen_median"])
    )
)
print(
    "Signing: % change in median: {}".format(
        percent_change(old["sign_median"], new["sign_median"])
    )
)
print(
    "Verification: % change in median: {}".format(
        percent_change(old["verify_median"], new["verify_median"])
    )
)
