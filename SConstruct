#shared
source_files = ['src/cello-shell.c']
env = Environment(CC = 'gcc', CCFLAGS=['-std=gnu99', '-Wall', '-fnested-functions'])
env.Append(LIBS = ['Cello'])
#optimized env
opt = env.Clone()
opt.Append(CCFLAGS = ['-O3'])

#debug env
dbg = env.Clone()
dbg.Append(CCFLAGS = ['-g', '-DDEBUG=1'])

#main program
shell = env.Program('build/cello-shell', source_files)

#optimized program
o = opt.Object('build/cs-opt', source_files)
optimize = opt.Program(o)

#debug program
d = dbg.Object('build/cs-dbg', source_files)
debug = dbg.Program(d)



