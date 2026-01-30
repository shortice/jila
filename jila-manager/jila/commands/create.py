import click
import os
import shutil
import json
from jila.utils.system import is_jila_installed, find_jila_root

@click.command()
@click.argument('name')
def create(name: str) -> None:
    """Create a new Jila project from empty_app template."""
    installed, result = is_jila_installed()
    if not installed:
        click.echo(result)
        return
        
    root = result # This is find_jila_root() result
    project_dir = os.path.join(os.getcwd(), name)
    
    if os.path.exists(project_dir):
        click.echo(f"Error: Folder '{name}' already exists. Please choose a different name.")
        return
        
    template_dir = os.path.join(root, "examples", "empty_app")
    if not os.path.exists(template_dir):
        click.echo(f"Error: Template directory not found at {template_dir}")
        return
        
    try:
        click.echo(f"Creating project '{name}'...")
        shutil.copytree(template_dir, project_dir)
        
        # Create .luarc.json for Lua LSP
        lua_components_path = os.path.join(root, "src", "components")
        lua_modules_path = os.path.join(root, "src", "external", "lua_modules")
        
        luarc_content = {
            "$schema": "https://raw.githubusercontent.com/LuaLS/vscode-lua/master/setting/schema.json",
            "runtime.version": "LuaJIT",
            "workspace.library": [
                lua_components_path.replace("\\", "/"),
                lua_modules_path.replace("\\", "/")
            ]
        }
        
        with open(os.path.join(project_dir, ".luarc.json"), 'w') as f:
            json.dump(luarc_content, f, indent=2)
            
        click.echo(f"Project '{name}' created successfully with .luarc.json.")
        click.echo(f"You can now run it using: jila run {name}")
    except Exception as e:
        click.echo(f"Failed to create project: {e}")
