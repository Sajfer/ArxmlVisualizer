
# Set our required libraries
libraries           = []
library_paths       = ''
cppDefines          = {}
cppFlags            = ['-Wall']  # , '-Werror']
cxxFlags            = ['-std=c++11']

# define the attributes of the build environment
env = Environment()
env.Append(LIBS             = libraries)
env.Append(LIBPATH          = library_paths)
env.Append(CPPDEFINES       = cppDefines)
env.Append(CPPFLAGS         = cppFlags)
env.Append(CXXFLAGS         = cxxFlags)
env.Append(CPPPATH          = ['inc'])

env.ParseConfig('wx-config --cflags --libs')

env.VariantDir('build', 'src', duplicate=0)

env.Program(target='build/ArxmlVisualizer', source=["src/main.cpp", "src/drawpane.cpp", "src/arxmlparser.cpp", "src/drawobject.cpp"])
