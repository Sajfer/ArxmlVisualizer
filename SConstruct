rootEnv = Environment()

# Set our required libraries
libraries           = []
library_paths       = ''
cppDefines          = {}
cppFlags            = ['-Wall'] #, '-Werror']
cxxFlags            = ['-std=c++11']


rootEnv.Append(LIBS             = libraries)
rootEnv.Append(LIBPATH          = library_paths)
rootEnv.Append(CPPDEFINES       = cppDefines)
rootEnv.Append(CPPFLAGS         = cppFlags)
rootEnv.Append(CXXFLAGS         = cxxFlags)
rootEnv.Append(CPPPATH          = ['../inc'])
rootEnv.ParseConfig('wx-config --cflags --libs')


Export('rootEnv')
SConscript('src/SConscript', variant_dir='build', duplicate=0)
