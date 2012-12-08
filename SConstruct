Program('main.c', CFLAGS='-fPIC -finstrument-functions')
SharedLibrary('trace', Split('trace.c'), LIBS='dl', CFLAGS='-fPIC -DMACRO=_GNU_SOURCE')
