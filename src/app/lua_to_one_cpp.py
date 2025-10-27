from glob import glob
from jinja2 import Template

TPL = """
#include "app/jila_app.hpp"

namespace LuaApplication {

std::vector<const char*> modules {
{{modules}}
};

std::vector<const char*> GetCode() {
    return modules;
}

}
"""


tpl = Template(
    TPL
)

sources = []

for i in glob("./app/*.lua"):
    with open(i) as fp:
        sources.append(f'R"(\n{fp.read()}\n)"')

with open("result.hpp", "w+") as fp:
    fp.write(
        tpl.render(
            modules=','.join(sources)
        )
    )
