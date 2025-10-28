import argparse
import os
from pathlib import Path
import sys
import subprocess
import shutil


def list_implementations():
    print(
        # x86-64 ref implementations
        "ml_dsa_44_ref_x86-64",
        "ml_dsa_65_ref_x86-64",
        "ml_dsa_87_ref_x86-64",
        # x86-64 avx2 implementations
        "ml_dsa_44_avx2_x86-64",
        "ml_dsa_65_avx2_x86-64",
        "ml_dsa_87_avx2_x86-64",
        # arm-m4 ref implementations
        "ml_dsa_44_ref_arm-m4",
        "ml_dsa_65_ref_arm-m4",
        "ml_dsa_87_ref_arm-m4",
        # arm-m4 lowram implementations
        "ml_dsa_44_lowram_arm-m4",
        "ml_dsa_65_lowram_arm-m4",
        "ml_dsa_87_lowram_arm-m4",
        sep=os.linesep,
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

if __name__ == "__main__":
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
