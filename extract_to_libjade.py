import argparse
import os
from pathlib import Path
import sys
import subprocess
import shutil


def list_implementations():
    for architecture in ["x86-64", "arm-m4"]:
        for implementation in ["ref", "avx2", "lowram"]:
            if architecture == "x86-64" and implementation == "lowram":
                continue
            if architecture == "arm-m4" and implementation == "avx2":
                continue
            for parameter_set in ["44", "65", "87"]:
                print(
                    "ml_dsa_{}_{}_{}".format(
                        parameter_set, implementation, architecture
                    )
                )


def generate_unified_source_file(implementation, target_dir):
    target_dir = Path(target_dir)

    if not target_dir.is_dir():
        sys.exit("Specified target directory does not exist: {}".format(target_dir))

    _, _, parameter_set, implementation_type, architecture = implementation.split("_")

    impl_root = Path(architecture, implementation_type)
    common_dir = impl_root / "common"
    ml_dsa_jazz = impl_root / "ml_dsa_{}".format(parameter_set) / "ml_dsa.jazz"

    target_file = target_dir / "sig.jazz"

    with open(target_file, "w") as f:
        subprocess.run(
            [
                "jasminc",
                "-I",
                "Common={}".format(common_dir),
                "-arch={}".format(architecture),
                "-ptyping",
                "-until_typing",
                ml_dsa_jazz,
            ],
            stdout=f,
            text=True,
        )

    api_h = impl_root / "ml_dsa_{}".format(parameter_set) / "api.h"
    shutil.copy(api_h, target_dir)


def main():
    parser = argparse.ArgumentParser(
        description="List all ML-DSA implementations in this directory and, for a specified implementation, extract a unified jazz file that can be compiled by Jasmin to an assembly file."
    )

    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument(
        "--list-implementations",
        action="store_true",
        help="List all available ML-DSA implementations and exit.",
    )
    group.add_argument(
        "--generate-implementation",
        nargs=2,
        metavar=("NAME", "TARGET_DIR"),
        help="Generate the specified implementation into the target directory.",
    )

    args = parser.parse_args()

    if args.list_implementations:
        list_implementations()

    elif args.generate_implementation:
        impl_name, target_dir = args.generate_implementation
        generate_unified_source_file(impl_name, target_dir)


if __name__ == "__main__":
    main()
