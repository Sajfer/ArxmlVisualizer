
# Set our required libraries
libraries           = []
library_paths       = ''
cppDefines          = {}
cppFlags            = ['-Wall']#, '-Werror']
cxxFlags            = ['-std=c++11']

# define the attributes of the build environment
env = Environment()
env.Append(LIBS             = libraries)
env.Append(LIBPATH          = library_paths)
env.Append(CPPDEFINES       = cppDefines)
env.Append(CPPFLAGS         = cppFlags)
env.Append(CXXFLAGS         = cxxFlags)

env = Environment()

env.Program(target = 'helloworld', source=["src/helloworld.cpp"])
