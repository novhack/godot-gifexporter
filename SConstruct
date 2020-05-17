#!python
import os, subprocess

opts = Variables([], ARGUMENTS)

# Gets the standard flags CC, CCX, etc.
env = DefaultEnvironment()

# Define our options
opts.Add(EnumVariable('platform', "Compilation platform", '', ['', 'windows', 'x11', 'linux', 'osx']))
opts.Add(EnumVariable('p', "Compilation target, alias for 'platform'", '', ['', 'windows', 'x11', 'linux', 'osx']))
opts.Add(EnumVariable('bits', "Compilation bits architecture", '64', ['32', '64']))
opts.Add(PathVariable('target_name', 'The library name.', 'gifexporter', PathVariable.PathAccept))

# Local dependency paths, adapt them to your setup
godot_headers_path = "godot-cpp/godot_headers/"
cpp_bindings_path = "godot-cpp/"
cpp_library = "libgodot-cpp"

# GifLoader dependencies
gifanim_path = "gifanimcplusplus"

# Updates the environment with the option variables.
opts.Update(env)

target_path = 'bin/'

if env['p'] != '':
    env['platform'] = env['p']

if env['platform'] == '':
    print("No valid target platform selected.")
    quit();

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Check our platform specifics
if env['platform'] == "osx":
    target_path += 'osx/'
    cpp_library += '.osx'
    env.Append(CCFLAGS=['-g', '-O3', '-arch', 'x86_64'])
    env.Append(LINKFLAGS=['-arch', 'x86_64'])

elif env['platform'] in ('x11', 'linux'):
    target_path += 'x11/'
    cpp_library += '.linux'
    env.Append(CCFLAGS=['-fPIC', '-O3', '-std=c++14'])
    env.Append(LINKFLAGS=['-static-libgcc', '-static-libstdc++'])

    if env['bits'] == '32':
        env.Append(CCFLAGS=['-m32'])
        env.Append(LINKFLAGS=['-m32'])

elif env['platform'] == "windows":
    target_path += 'win/'
    cpp_library += '.windows'

    env.Append(CCFLAGS=['-O3', '-std=c++14'])
    env.Append(LINKFLAGS=['-static', '-static-libgcc', '-static-libstdc++'])

    if env['bits'] == '32':
        env['CC'] = 'i686-w64-mingw32-gcc'
        env['CXX'] = 'i686-w64-mingw32-g++'
    else:
        env['CC'] = 'x86_64-w64-mingw32-gcc'
        env['CXX'] = 'x86_64-w64-mingw32-g++'

    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    #env.Append(ENV=os.environ)
    #env.Append(CPPDEFINES=['WIN32', '_WIN32', '_WINDOWS', '_CRT_SECURE_NO_WARNINGS', 'NDEBUG'])
    #env.Append(CCFLAGS=['-W3', '-GR', '-O2', '-EHsc', '-MD'])


cpp_library += '.release'
cpp_library += '.' + env['bits']


# make sure our binding library is properly includes
env.Append(CPPPATH=['.', godot_headers_path, cpp_bindings_path + 'include/', cpp_bindings_path + 'include/core/', cpp_bindings_path + 'include/gen/', gifanim_path])
env.Append(LIBPATH=[cpp_bindings_path + 'bin/'])
env.Append(LIBS=[cpp_library])
print(cpp_library)

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=['src/'])
sources = Glob('src/*.cpp') + Glob('gifanimcplusplus/*.cpp')

library = env.SharedLibrary(target=target_path + env['target_name'] + "." + env['platform'] + "." + env['bits'] , source=sources)

Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
