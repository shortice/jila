import click
import os
import platform
import subprocess
import shutil
from typing import Optional
from jila.utils.system import check_dependencies, run_command, find_jila_root

def copy_lua_only(src_dir: str, dst_dir: str) -> None:
    if not os.path.exists(src_dir):
        return
                
    os.makedirs(dst_dir, exist_ok=True)
    
    for root, dirs, files in os.walk(src_dir):
        rel_path = os.path.relpath(root, src_dir)
        target_root = os.path.join(dst_dir, rel_path)
        os.makedirs(target_root, exist_ok=True)
        for file in files:
            if file.endswith('.lua'):
                shutil.copy2(os.path.join(root, file), os.path.join(target_root, file))

@click.command()
@click.option('--commit', help='Target commit or branch to clone.')
@click.option('--dev', is_flag=True, help='Install in developer mode by copying current directory to package.')
def install(commit: Optional[str], dev: bool) -> None:
    """Install Jila by cloning and compiling the repository."""
    click.echo("Checking dependencies...")
    check_dependencies()
    
    repo_url = "https://github.com/shortice/jila"
    engine_root = find_jila_root()
    
    if os.path.exists(engine_root):
        click.echo(f"Cleaning existing Jila installation at {engine_root}...")
        shutil.rmtree(engine_root)
    
    os.makedirs(engine_root, exist_ok=True)
    
    if dev:
        click.echo(f"Developer mode: copying build and examples to {engine_root}...")
        src_cwd = os.getcwd()
        
        # Verify essential folders exist in CWD
        build_src = os.path.join(src_cwd, "build")
        examples_src = os.path.join(src_cwd, "examples")
        
        if not os.path.exists(build_src) or not os.path.exists(examples_src):
            click.echo("Error: Current directory must contain 'build' and 'examples' folders.")
            return

        try:
            # Copy build/app
            target_build_app = os.path.join(engine_root, "build", "app")
            os.makedirs(os.path.dirname(target_build_app), exist_ok=True)
            shutil.copytree(os.path.join(build_src, "app"), target_build_app)
            
            # Copy examples
            shutil.copytree(examples_src, os.path.join(engine_root, "examples"))
            
            # Copy Lua files for LSP (components and external modules)

            copy_lua_only(
                os.path.join(src_cwd, "src", "components"),
                os.path.join(engine_root, "src", "components")
            )
            
            copy_lua_only(
                os.path.join(src_cwd, "src", "external", "lua_modules"),
                os.path.join(engine_root, "src", "external", "lua_modules")
            )

            click.echo("Jila dev components (build/app, examples, and Lua files) installed successfully!")
            return # Skip compilation in dev mode
        except Exception as e:
            click.echo(f"Failed to copy dev components: {e}")
            return
    else:
        click.echo(f"Cloning Jila repository into {engine_root}...")
        clone_cmd = ["git", "clone", "--recursive", repo_url, engine_root]
        try:
            run_command(clone_cmd)
        except Exception as e:
            click.echo(f"Failed to clone repository: {e}")
            return

    if commit:
        click.echo(f"Checking out commit: {commit}...")
        try:
            run_command(["git", "checkout", commit], cwd=engine_root)
            run_command(["git", "submodule", "update", "--init", "--recursive"], cwd=engine_root)
        except Exception as e:
            click.echo(f"Failed to checkout commit {commit}: {e}")
            return

    click.echo("Compiling Jila...")
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
        click.echo(f"Running: {' '.join(cmake_cmd)}")
        run_command(cmake_cmd, cwd=engine_root)
        
        click.echo("Building...")
        build_cmd = ["cmake", "--build", "./build"]
        run_command(build_cmd, cwd=engine_root)
        
        click.echo("Jila installed and compiled successfully!")
    except subprocess.CalledProcessError as e:
        click.echo("Compilation failed. See logs above.")
        pass
    except Exception as e:
        click.echo(f"An unexpected error occurred: {e}")
