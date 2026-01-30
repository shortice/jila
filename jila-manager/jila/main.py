import click
from jila.commands.install import install
from jila.commands.update import update
from jila.commands.create import create
from jila.commands.run import run

@click.group()
@click.version_option()
def cli():
    """Jila Project Manager CLI"""
    pass

cli.add_command(install)
cli.add_command(update)
cli.add_command(create)
cli.add_command(run)

if __name__ == "__main__":
    cli()
