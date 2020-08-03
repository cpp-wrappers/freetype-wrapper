#include <string>
#include <vector>
#include <filesystem>
#include <utility>
#include <set>
#include "cxx_exec/gcc_like_driver.hpp"
#include "clap/gnu_clap.hpp"
#include "cxx_exec/ext/build/configuration.hpp"
#include "cxx_exec/environment.hpp"
#include "cxx_exec/ar.hpp"

using namespace std;
using namespace filesystem;

inline void log(auto v) {
    cout<<"[freetype-wrapper] "<<v<<"\n";
    cout.flush();
}

void exec(vector<string> args) {
    log("start");
    gnu::clap clap;

    string config_name;
    path ft_lib;
    path ft_include;
    clap.required_option("configuration", [&](string_view arg) {
        config_name = arg;
    });
    clap.required_option("ft-lib", [&](string_view arg) {
        ft_lib = arg;
    });
    clap.required_option("ft-include", [&](string_view arg) {
        ft_include = arg;
    });
    clap.parse(args.begin(), args.end());

    auto& conf = get_configuration(config_name);

    auto cc = environment::cxx_compile_command_builder();
    cc.std(gcc_like_driver::cxx20);
    cc.include("include").include(ft_include);
    cc.out_type(gcc_like_driver::object_file);
    conf.apply(cc);

    path build_conf{path{"build"}/conf.name};
    path objects_p{build_conf/"objects"};
    create_directories(objects_p);

    vector<path> objects;
    path lib{build_conf/"libfreetype-wrapper.a"};

    for(auto de : directory_iterator{"src"}) {
        path p{de};
        if(p.extension() != ".cpp")
            continue;

        path in{p};
        path out{objects_p/in.filename().replace_extension(".o")};

        cc.input(in);
        cc.out(out);
        log("compile "+in.string());
        environment::execute(cc);
        cc.clear_inputs();
        objects.push_back(out);
    }

    if(exists(lib)) remove(lib);

    environment::execute(
        ar::insert().verbose()
        .thin()
        .to_archive(lib)
        .create_if_not_exists()
        .members(objects.begin(), objects.end())
        .member(ft_lib)
    );

    log("done");
}