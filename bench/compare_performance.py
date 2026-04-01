import argparse
import os
import re
import subprocess
import sys


BENCH_DIR = os.path.dirname(os.path.abspath(__file__))
METRICS = ("keygen", "sign", "verify")
STATISTICS = ("median", "average")
LABELS = {
    "keygen": "Keygen",
    "sign": "Sign",
    "verify": "Verify",
}
ANSI_RESET = "\033[0m"
ANSI_BOLD = "\033[1m"
ANSI_RED = "\033[31m"
ANSI_GREEN = "\033[32m"
ANSI_YELLOW = "\033[33m"
ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")


def shell(command, cwd=None, expect=0):
    completed = subprocess.run(command, cwd=cwd, capture_output=True, text=True)

    if completed.returncode != expect:
        if completed.stdout:
            print(completed.stdout, file=sys.stderr, end="")
        if completed.stderr:
            print(completed.stderr, file=sys.stderr, end="")
        raise RuntimeError(
            f"Command {command!r} failed with exit code {completed.returncode}, expected {expect}."
        )

    return completed.stdout


def parse_bench_output(output):
    parsed = {}
    lines = [line.strip() for line in output.splitlines() if line.strip()]

    if len(lines) < 4:
        raise ValueError(f"Unexpected benchmark output:\n{output}")

    for line in lines[1:4]:
        name, median, average = [field.strip() for field in line.split(",")]
        lowered = name.lower()

        if "key" in lowered:
            metric = "keygen"
        elif "sign" in lowered:
            metric = "sign"
        elif "verif" in lowered:
            metric = "verify"
        else:
            raise ValueError(f"Could not identify benchmark line: {line}")

        parsed[f"{metric}_median"] = int(median)
        parsed[f"{metric}_average"] = int(average)

    checksum_line = next(
        (line for line in lines[4:] if line.lower().startswith("checksum,")),
        None,
    )
    if checksum_line is None:
        raise ValueError(f"Missing checksum line in benchmark output:\n{output}")

    _, checksum = [field.strip() for field in checksum_line.split(",", 1)]
    parsed["checksum"] = checksum

    return parsed


def percent_change(reference, candidate):
    if reference == 0:
        return 0.0
    return ((candidate - reference) / reference) * 100.0


def format_signed_int(value):
    return f"{value:+,}"


def format_percent(value):
    sign = "+" if value > 0 else ""
    return f"{sign}{value:.2f}%"


def wants_color(mode):
    if mode == "always":
        return True
    if mode == "never":
        return False
    return sys.stdout.isatty()


def colorize(text, color, enabled):
    if not enabled:
        return text
    return f"{color}{text}{ANSI_RESET}"


def colorize_percent(text, enabled):
    try:
        numeric = float(text.replace("%", ""))
    except ValueError:
        return text

    if numeric < 0:
        return colorize(text, ANSI_GREEN, enabled)
    if numeric > 0:
        return colorize(text, ANSI_RED, enabled)
    return colorize(text, ANSI_YELLOW, enabled)


def strip_ansi(text):
    return ANSI_RE.sub("", text)


def visible_len(text):
    return len(strip_ansi(text))


def pad_visible(text, width):
    return text + " " * max(0, width - visible_len(text))


def align_decimal_columns(rows, indices):
    aligned = [list(row) for row in rows]

    for index in indices:
        left_width = 0
        right_width = 0

        for row in aligned:
            cell = str(row[index])
            dot = cell.find(".")
            if dot == -1:
                left, right = cell, ""
            else:
                left, right = cell[:dot], cell[dot + 1 :]
            left_width = max(left_width, len(left))
            right_width = max(right_width, len(right))

        for row in aligned:
            cell = str(row[index])
            dot = cell.find(".")
            if dot == -1:
                left, right = cell, ""
            else:
                left, right = cell[:dot], cell[dot + 1 :]

            if right_width:
                row[index] = f"{left:>{left_width}}.{right:<{right_width}}"
            else:
                row[index] = f"{left:>{left_width}}"

    return aligned


def render_table(title, headers, rows):
    widths = [visible_len(header) for header in headers]
    string_rows = [[str(cell) for cell in row] for row in rows]

    for row in string_rows:
        for index, cell in enumerate(row):
            widths[index] = max(widths[index], visible_len(cell))

    def border(char="-"):
        return "+" + "+".join(char * (width + 2) for width in widths) + "+"

    def render_row(row):
        cells = [f" {pad_visible(cell, widths[index])} " for index, cell in enumerate(row)]
        return "|" + "|".join(cells) + "|"

    lines = [title, border(), render_row(headers), border("=")]
    lines.extend(render_row(row) for row in string_rows)
    lines.append(border())
    return "\n".join(lines)


def render_markdown_table(title, headers, rows):
    lines = [f"### {title}"]
    lines.append("| " + " | ".join(headers) + " |")
    lines.append("| " + " | ".join("---" for _ in headers) + " |")
    for row in rows:
        lines.append("| " + " | ".join(str(cell) for cell in row) + " |")
    return "\n".join(lines)


def build_and_run(target, binary):
    print(f"Measuring {binary}...", file=sys.stderr)
    shell(["make", target], cwd=BENCH_DIR)
    return parse_bench_output(shell([f"./{binary}"], cwd=BENCH_DIR))


def build_summary_rows(jasmin_results, native_results):
    rows = []

    for metric in METRICS:
        for statistic in STATISTICS:
            jasmin_value = jasmin_results[f"{metric}_{statistic}"]
            native_value = native_results[f"{metric}_{statistic}"]
            delta = jasmin_value - native_value
            percent = percent_change(native_value, jasmin_value)
            rows.append(
                [
                    LABELS[metric],
                    statistic.capitalize(),
                    f"{jasmin_value:,}",
                    f"{native_value:,}",
                    format_signed_int(delta),
                    format_percent(percent),
                ]
            )

    rows = align_decimal_columns(rows, [5])
    return ["Operation", "Statistic", "Jasmin", "mldsa-native", "Delta", "Delta %"], rows


def decorate_rows(rows, color_enabled):
    decorated = []
    for row in rows:
        decorated_row = list(row)
        if len(decorated_row) >= 6:
            decorated_row[5] = colorize_percent(decorated_row[5], color_enabled)
        elif len(decorated_row) >= 3:
            decorated_row[1] = colorize_percent(decorated_row[1], color_enabled)
            decorated_row[2] = colorize_percent(decorated_row[2], color_enabled)
        decorated.append(decorated_row)
    return decorated


def main():
    parser = argparse.ArgumentParser(
        prog="compare_performance.py",
        description="Compare bench_jasmin against bench_mldsa_native_65.",
    )
    parser.add_argument(
        "--markdown",
        action="store_true",
        help="Render output as Markdown tables.",
    )
    parser.add_argument(
        "--color",
        choices=("auto", "always", "never"),
        default="auto",
        help="Control ANSI colors for terminal output.",
    )
    args = parser.parse_args()

    jasmin_results = build_and_run("bench_jasmin", "bench_jasmin")
    native_results = build_and_run("bench_mldsa_native_65", "bench_mldsa_native_65")

    if jasmin_results["checksum"] != native_results["checksum"]:
        raise RuntimeError(
            "Benchmark checksum mismatch: "
            f"Jasmin={jasmin_results['checksum']} "
            f"mldsa-native={native_results['checksum']}"
        )

    summary_headers, summary_rows = build_summary_rows(jasmin_results, native_results)
    color_enabled = wants_color(args.color) and not args.markdown
    summary_title = "Raw Benchmark Results"

    if color_enabled:
        summary_title = colorize(summary_title, ANSI_BOLD, True)

    decorated_summary_rows = decorate_rows(summary_rows, color_enabled)

    print()
    if args.markdown:
        print(render_markdown_table(summary_title, summary_headers, summary_rows))
    else:
        print(render_table(summary_title, summary_headers, decorated_summary_rows))


if __name__ == "__main__":
    main()
