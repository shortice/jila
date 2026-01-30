import click
import os
import platform
import subprocess
from typing import Optional
from jila.utils.system import check_dependencies, run_command, find_jila_root

@click.command()
@click.option('--commit', help='Target commit or branch to update to.')
def update(commit: Optional[str]) -> None:
    """Update Jila by pulling latest changes and recompiling."""
    check_dependencies()
    
    root = find_jila_root()
    if not root:
        click.echo("Jila repository not found. Please run 'jila install' first.")
        return

    click.echo(f"Updating Jila in {root}...")
    
    try:
        # Update repository
        if commit:
            run_command(["git", "fetch", "--all"], cwd=root)
            run_command(["git", "checkout", commit], cwd=root)
        else:
            run_command(["git", "pull", "--recursive"], cwd=root)
        
        run_command(["git", "submodule", "update", "--init", "--recursive"], cwd=root)
    except Exception as e:
        click.echo(f"Failed to update git repository: {e}")
        return

    click.echo("Recompiling Jila...")
    is_windows = platform.system() == "Windows"
    
    if is_windows:
        cmake_cmd = [
            "cmake", "./src", "-B", "./build",
            "-DJILA_ALL=ON",
            "-DSDLMIXER_VENDORED=OFF",
            "-DSDLIMAGE_VENDORED=OFF",
            "-DCMAKE_CXX_COMPILER=clang-cl",
            "-DCMAKE_C_COMPILER=clang-cl",
            "-G", "Ninja"
        ]
    else:
        cmake_cmd = [
            "cmake", "./src", "-B", "./build",
            "-DJILA_ALL=ON",
            "-DSDLMIXER_VENDORED=OFF",
            "-DSDLIMAGE_VENDORED=OFF",
            "-DCMAKE_CXX_COMPILER=clang++",
            "-DCMAKE_C_COMPILER=clang"
        ]

    try:
        run_command(cmake_cmd, cwd=root)
        run_command(["cmake", "--build", "./build"], cwd=root)
        click.echo("Jila updated and recompiled successfully!")
    except subprocess.CalledProcessError as e:
        click.echo("Compilation failed. See logs above.")
    except Exception as e:
        click.echo(f"An unexpected error occurred: {e}")
