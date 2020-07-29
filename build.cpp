#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <utility>
#include <fstream>
#include <optional>
#include "cxx_exec/clang_driver.hpp"
#include "clap/gnu_clap.hpp"

using namespace std;
using namespace filesystem;

void exec(vector<string> args) {

    path objects_p{"build/freetype2/object"};
    create_directories(objects_p);

    {
        struct module {string clazz; string name;};

        vector<module> modules {
            {"FT_Driver_ClassRec", "tt_driver_class"},
            {"FT_Module_Class", "sfnt_module_class"}
        };

        ofstream modules_s{"build/freetype2/modules.h"};
        modules_s << "#pragma once\n\n";
        for(auto m : modules)
            modules_s << "FT_USE_MODULE( "+m.clazz+", "+m.name+" )\n";
    }

    {
        struct option {
            bool define;
            string name;
            optional<string> value;
            option(const char* name, const char* value):define{true},name{name},value{value}{}
            option(bool define, string name):define{define},name{name}{}
        };

        vector<option> options {
            {"FT_RENDER_POOL_SIZE", "16384L"},
            {"FT_MAX_MODULES", "32"},
            {false, "FT_CONFIG_OPTION_USE_MODULE_ERRORS"},
            {"T1_MAX_CHARSTRINGS_OPERANDS", "256"},
            {"T1_MAX_SUBRS_CALLS", "16"}
        };

        ofstream options_s{"build/freetype2/options.h"};
        options_s << "#pragma once\n\n#include <ft2build.h>\n\n";
        for(auto o : options) {
            options_s << "#" << (o.define?"define":"undef") << " "+o.name;
            if(o.value)
                options_s << "  "+*o.value;
            options_s << "\n";
        }
    }

    vector<string> srcs {
        "base/ftsystem",
        "base/ftinit",
        "base/ftdebug",
        "base/ftbase",
        "base/ftbbox",
        "base/ftglyph",
        "base/ftbitmap",
        "sfnt/sfnt",
        "truetype/truetype",
        "psnames/psnames"
    };
    
    clang::driver::executor comp{"clang", clang::driver::lang_stds::c17};

    comp.include_path("freetype2/include");
    comp.include_path("build/freetype2");
    comp.args.push_back("-c");
    comp.args.push_back("-DFT_CONFIG_MODULES_H=\"<modules.h>\"");
    comp.args.push_back("-DFT_CONFIG_OPTIONS_H=\"<options.h>\"");
    comp.args.push_back("-DFT2_BUILD_LIBRARY");

    for(auto src : srcs) {
        comp.input_file("freetype2/src/"+src+".c");
        comp.output = objects_p/(src+".o");
        create_directories((objects_p/src).remove_filename());
        comp.execute();
        comp.input_files.clear();
        command_executor{"ar", {"-rcv", "build/freetype2/libfreetype.a", comp.output->string()}}.execute();
    }
}