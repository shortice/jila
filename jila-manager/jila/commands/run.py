import click
import os
import platform
import subprocess
import sys
from jila.utils.system import is_jila_installed

@click.command()
@click.argument('path', type=click.Path(exists=True, file_okay=False, dir_okay=True))
def run(path: str) -> None:
    """Run a Jila application from the specified folder."""
    installed, result = is_jila_installed()
    if not installed:
        click.echo(result)
        return
        
    root = result
    is_windows = platform.system() == "Windows"
    binary_name = "main.exe" if is_windows else "main"
    binary_path = os.path.abspath(os.path.join(root, "build", "app", binary_name))
    
    # Absolute path of the project to run
    app_path = os.path.abspath(path)
    
    click.echo(f"Starting Jila application from: {app_path}")
    
    try:
        # Run the binary with the path as argument
        # Redirect output and error directly to system streams
        result = subprocess.run(
            [binary_path, app_path],
            cwd=app_path,
            stdout=sys.stdout,
            stderr=sys.stderr,
            text=True,
            check=False # We handle exit code manually below if needed, or just let it be
        )
        
        if result.returncode != 0:
            click.echo(f"Application exited with code {result.returncode}")
            
    except Exception as e:
        click.echo(f"Failed to run application: {e}")
