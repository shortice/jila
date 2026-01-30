import subprocess
import sys
import shutil
import os
import platform
from typing import List, Optional, Tuple, Union

def run_command(command: List[str], cwd: Optional[str] = None, capture_output: bool = False, shell: bool = False) -> subprocess.CompletedProcess:
    """Runs a shell command and returns the result."""
    try:
        if capture_output:
            result = subprocess.run(
                command,
                cwd=cwd,
                capture_output=True,
                text=True,
                shell=shell,
                check=True
            )
            return result
        else:
            # Output directly to system stdout/stderr
            result = subprocess.run(
                command,
                cwd=cwd,
                stdout=sys.stdout,
                stderr=sys.stderr,
                text=True,
                shell=shell,
                check=True
            )
            return result
    except subprocess.CalledProcessError as e:
        if capture_output:
            print(f"Error executing command: {e}")
            if e.stdout:
                print(f"Stdout: {e.stdout}")
            if e.stderr:
                print(f"Stderr: {e.stderr}")
        raise e

def check_dependencies() -> bool:
    """Checks if cmake, git, and clang/clang-cl are installed."""
    deps = ["cmake", "git"]
    missing = []
    
    for dep in deps:
        if not shutil.which(dep):
            missing.append(dep)
            
    is_windows = platform.system() == "Windows"
    if is_windows:
        if not shutil.which("clang-cl") and not shutil.which("clang"):
            missing.append("clang-cl / clang (LLVM)")
    else:
        if not shutil.which("clang") and not shutil.which("clang++"):
            missing.append("clang / clang++")
            
    if missing:
        print(f"Missing dependencies: {', '.join(missing)}")
        sys.exit(1)
    return True

def find_jila_root() -> str:
    """Returns the path to the Jila repository stored inside the package."""
    # The root is inside the 'jila' package folder
    package_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    return os.path.join(package_root, "engine")

def is_jila_installed() -> Tuple[bool, str]:
    """Checks if Jila is cloned and compiled in the internal build folder."""
    root = find_jila_root()
    if not os.path.exists(root):
        return False, "Jila engine is not installed. Please run 'jila install' first."
        
    build_dir = os.path.join(root, "build")
    if not os.path.exists(build_dir):
        return False, "Build directory not found. Please run 'jila install' to compile."
        
    # Check for binary
    is_windows = platform.system() == "Windows"
    binary_name = "main.exe" if is_windows else "main"
    binary_path = os.path.join(build_dir, "app", binary_name)
    
    if not os.path.exists(binary_path):
        return False, f"Jila binary not found at {binary_path}. Please run 'jila install' or 'jila update'."
        
    return True, root
