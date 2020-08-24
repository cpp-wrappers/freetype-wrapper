#include <string>
#include <vector>
#include <filesystem>
#include <utility>
#include <set>
#include "gcc_like_driver.hpp"
#include "clap/gnu_clap.hpp"
#include "build/configuration.hpp"
#include "environment.hpp"
#include "build/build.hpp"
#include <ranges>

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
    clap.value("configuration", config_name);

    path ft_lib, ft_include;
    clap.value("ft-lib", ft_lib).value("ft-include", ft_include);

    path ft_build, ft_src;
    clap.value("ft-build", ft_build).value("ft-src", ft_src);
    clap.parse(args);

    if(not ft_build.empty() and not ft_src.empty()) {
        environment::execute(
            "cd "+ft_build.string()+
            " && "+
            "cxx-exec build.cpp --exec=build -- "+
            "--configuration="+config_name+" "+
            "--ft-src="+ft_src.string()
        );

        ft_include = ft_src/"include";
        ft_lib = ft_build/"build"/config_name/"libfreetype.a";
    }

    auto& conf = configuration::by_name(config_name);

    auto cc = environment::cxx_compile_command_builder();
    cc.std(gcc_like_driver::cxx20);
    cc.include("include").include(ft_include);
    conf.apply(cc);

    path build_conf{path{"build"}/conf.name()};
    path build_objects{build_conf/"objects"};
	
	source_set::from_dir("src", ".cpp")
		.compile_to_objects(build_objects, cc)
		.to_thin_static_lib(build_conf, "freetype-wrapper");

    log("done");
}