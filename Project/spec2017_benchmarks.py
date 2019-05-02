import m5
from m5.objects import *
 
# These three directory paths are not currently used.
#gem5_dir = '<FULL_PATH_TO_YOUR_GEM5_INSTALL>'
#spec_dir = '<FULL_PATH_TO_YOUR_SPEC2017>'
#out_dir = '/home/rohan/gem5/'
 
alpha_suffix = '_base.mytest-m64'
 
#temp
#binary_dir = spec_dir
#data_dir = spec_dir
 
#600.perlbench
perlbench = Process()
perlbench.executable =  'erlbench_s' + alpha_suffix
# TEST CMDS
#perlbench.cmd = [perlbench.executable] + ['-I.', '-I./lib', 'attrs.pl']
# REF CMDS
#perlbench.cmd = [perlbench.executable] + ['-I./lib', 'checkspam.pl', '2500', '5', '25', '11', '150', '1', '1', '1', '1']
#perlbench.cmd = [perlbench.executable] + ['-I./lib', 'diffmail.pl', '4', '800', '10', '17', '19', '300']
perlbench.cmd = [perlbench.executable] + ['-I./lib', 'splitmail.pl', '1600', '12', '26', '16', '4500']
#perlbench.output = out_dir+'perlbench.out'
 
#657.xz
xz = Process() #     : This used to be LiveProcess()
xz.executable =  'xz_s' + alpha_suffix
# TEST CMDS
#bzip2.cmd = [bzip2.executable] + ['input.program', '5']
# REF CMDS
#xz.cmd = [xz.executable] + ['input.source', '280']
#bzip2.cmd = [bzip2.executable] + ['chicken.jpg', '30']
#bzip2.cmd = [bzip2.executable] + ['liberty.jpg', '30']
#bzip2.cmd = [bzip2.executable] + ['input.program', '280']
#bzip2.cmd = [bzip2.executable] + ['text.html', '280']
xz.cmd = [xz.executable] + ['cld.tar.xz', '1400']
#xz.output = out_dir + 'bzip2.out'
 
#403.gcc
gcc = Process() #     : This used to be LiveProcess()
gcc.executable = 'gcc' + alpha_suffix
# TEST CMDS
#gcc.cmd = [gcc.executable] + ['cccp.i', '-o', 'cccp.s']
# REF CMDS
gcc.cmd = [gcc.executable] + ['166.i', '-o', '166.s']
#gcc.cmd = [gcc.executable] + ['200.i', '-o', '200.s']
#gcc.cmd = [gcc.executable] + ['c-typeck.i', '-o', 'c-typeck.s']
#gcc.cmd = [gcc.executable] + ['cp-decl.i', '-o', 'cp-decl.s']
#gcc.cmd = [gcc.executable] + ['expr.i', '-o', 'expr.s']
#gcc.cmd = [gcc.executable] + ['expr2.i', '-o', 'expr2.s']
#gcc.cmd = [gcc.executable] + ['g23.i', '-o', 'g23.s']
#gcc.cmd = [gcc.executable] + ['s04.i', '-o', 's04.s']
#gcc.cmd = [gcc.executable] + ['scilab.i', '-o', 'scilab.s']
#gcc.output = out_dir + 'gcc.out'
 
#410.bwaves
bwaves = Process() #     : This used to be LiveProcess()
bwaves.executable = 'bwaves' + alpha_suffix
# TEST CMDS
#bwaves.cmd = [bwaves.executable]
# REF CMDS
bwaves.cmd = [bwaves.executable]
#bwaves.output = out_dir + 'bwaves.out'
 
#416.gamess
gamess = Process() #     : This used to be LiveProcess()
gamess.executable = 'gamess' + alpha_suffix
# TEST CMDS
#gamess.cmd = [gamess.executable]
#gamess.input = 'exam29.config'
# REF CMDS
gamess.cmd = [gamess.executable]
gamess.input = 'cytosine.2.config'
#gamess.cmd = [gamess.executable]
#gamess.input = 'h2ocu2+.gradient.config'
#gamess.cmd = [gamess.executable]
#gamess.input = 'triazolium.config'
#gamess.output = out_dir + 'gamess.out'
 
#605.mcf_r
mcf = Process() #     : This used to be LiveProcess()
mcf.executable =  'mcf_s' + alpha_suffix
# TEST CMDS
#mcf.cmd = [mcf.executable] + ['inp.in']
# REF CMDS
mcf.cmd = [mcf.executable] + ['inp.in']
#mcf.output = out_dir + 'mcf.out'
 
#433.milc
milc = Process() #     : This used to be LiveProcess()
milc.executable = 'milc' + alpha_suffix
# TEST CMDS
#milc.cmd = [milc.executable]
#milc.input = 'su3imp.in'
# REF CMDS
milc.cmd = [milc.executable]
milc.input = 'su3imp.in'
#milc.output = out_dir + 'milc.out'
 
#638.imagick
imagick = Process() #     : This used to be LiveProcess()
imagick.executable = 'imagick_s' + alpha_suffix
# TEST CMDS
#zeusmp.cmd = [zeusmp.executable]
# REF CMDS
imagick.cmd = [imagick.executable]
#zeusmp.output = out_dir + 'zeusmp.out'
 
#435.gromacs
gromacs = Process() #     : This used to be LiveProcess()
gromacs.executable = 'gromacs' + alpha_suffix
# TEST CMDS
#gromacs.cmd = [gromacs.executable] + ['-silent','-deffnm', 'gromacs', '-nice','0']
# REF CMDS
gromacs.cmd = [gromacs.executable] + ['-silent','-deffnm', 'gromacs', '-nice','0']
#gromacs.output = out_dir + 'gromacs.out'
 
#436.cactusADM
cactusADM = Process() #     : This used to be LiveProcess()
cactusADM.executable = 'cactusADM' + alpha_suffix 
# TEST CMDS
#cactusADM.cmd = [cactusADM.executable] + ['benchADM.par']
# REF CMDS
cactusADM.cmd = [cactusADM.executable] + ['benchADM.par']
#cactusADM.output = out_dir + 'cactusADM.out'
 
#437.leslie3d
leslie3d = Process() #     : This used to be LiveProcess()
leslie3d.executable = 'leslie3d' + alpha_suffix
# TEST CMDS
#leslie3d.cmd = [leslie3d.executable]
#leslie3d.input = 'leslie3d.in'
# REF CMDS
leslie3d.cmd = [leslie3d.executable]
leslie3d.input = 'leslie3d.in'
#leslie3d.output = out_dir + 'leslie3d.out'
 
#444.namd
namd = Process() #     : This used to be LiveProcess()
namd.executable = 'namd' + alpha_suffix
# TEST CMDS
#namd.cmd = [namd.executable] + ['--input', 'namd.input', '--output', 'namd.out', '--iterations', '1']
# REF CMDS
namd.cmd = [namd.executable] + ['--input', 'namd.input', '--output', 'namd.out', '--iterations', '38']
#namd.output = out_dir + 'namd.out'
 
#641.leela
leela = Process() #     : This used to be LiveProcess()
leela.executable = 'leela_s' + alpha_suffix
# TEST CMDS
#leela.cmd = [leela.executable] + ['--quiet','--mode', 'gtp']
#leela.input = 'dniwog.tst'
# REF CMDS
leela.cmd = [leela.executable] + ['--quiet','--mode', 'gtp']
leela.input = 'test.sgf'
#leela.cmd = [leela.executable] + ['--quiet','--mode', 'gtp']
#leela.input = 'nngs.tst'
#leela.cmd = [leela.executable] + ['--quiet','--mode', 'gtp']
#leela.input = 'score2.tst'
#leela.cmd = [leela.executable] + ['--quiet','--mode', 'gtp']
#leela.input = 'trevorc.tst'
#leela.cmd = [leela.executable] + ['--quiet','--mode', 'gtp']
#leela.input = 'trevord.tst'
#leela.output = out_dir + 'leela.out'
 
#447.dealII
####### NOT WORKING #########
dealII = Process() #     : This used to be LiveProcess()
dealII.executable = 'dealII' + alpha_suffix
# TEST CMDS
####### NOT WORKING #########
#dealII.cmd = [leela.executable]+['8']
# REF CMDS
####### NOT WORKING #########
#dealII.output = out_dir + 'dealII.out'
 
#450.soplex
soplex = Process() #     : This used to be LiveProcess()
soplex.executable = 'soplex' + alpha_suffix
# TEST CMDS
#soplex.cmd = [soplex.executable] + ['-m10000', 'test.mps']
# REF CMDS
soplex.cmd = [soplex.executable] + ['-m45000', 'pds-50.mps']
#soplex.cmd = [soplex.executable] + ['-m3500', 'ref.mps']
#soplex.output = out_dir + 'soplex.out'
 
#511.povray
povray = Process() #     : This used to be LiveProcess()
povray.executable = 'povray_r' + alpha_suffix
# TEST CMDS
#povray.cmd = [povray.executable] + ['SPEC-benchmark-test.ini']
# REF CMDS
povray.cmd = [povray.executable] + ['SPEC-benchmark.ini']
#povray.output = out_dir + 'povray.out'
 
#454.calculix
calculix = Process() #     : This used to be LiveProcess()
calculix.executable = 'calculix' + alpha_suffix
# TEST CMDS
#calculix.cmd = [calculix.executable] + ['-i', 'beampic']
# REF CMDS
calculix.cmd = [calculix.executable] + ['-i', 'hyperviscoplastic']
#calculix.output = out_dir + 'calculix.out' 
 
#456.hmmer
hmmer = Process() #     : This used to be LiveProcess()
hmmer.executable = 'hmmer' + alpha_suffix
# TEST CMDS
#hmmer.cmd = [hmmer.executable] + ['--fixed', '0', '--mean', '325', '--num', '45000', '--sd', '200', '--seed', '0', 'bombesin.hmm']
# REF CMDS
hmmer.cmd = [hmmer.executable] + ['nph3.hmm', 'swiss41']
#hmmer.cmd = [hmmer.executable] + ['--fixed', '0', '--mean', '500', '--num', '500000', '--sd', '350', '--seed', '0', 'retro.hmm']
#hmmer.output = out_dir + 'hmmer.out'
 
#458.sjeng
sjeng = Process() #     : This used to be LiveProcess()
sjeng.executable = 'sjeng' + alpha_suffix 
# TEST CMDS
#sjeng.cmd = [sjeng.executable] + ['test.txt']
# REF CMDS
sjeng.cmd = [sjeng.executable] + ['ref.txt']
#sjeng.output = out_dir + 'sjeng.out'
 
#459.GemsFDTD
GemsFDTD = Process() #     : This used to be LiveProcess()
GemsFDTD.executable = 'GemsFDTD' + alpha_suffix 
# TEST CMDS
#GemsFDTD.cmd = [GemsFDTD.executable]
# REF CMDS
GemsFDTD.cmd = [GemsFDTD.executable]
#GemsFDTD.output = out_dir + 'GemsFDTD.out'
 
#462.libquantum
libquantum = Process() #     : This used to be LiveProcess()
libquantum.executable = 'libquantum' + alpha_suffix
# TEST CMDS
#libquantum.cmd = [libquantum.executable] + ['33','5']
# REF CMDS [  10/2/2015]: Sparsh Mittal has pointed out the correct input for libquantum should be 1397 and 8, not 1297 and 8. Thanks!
libquantum.cmd = [libquantum.executable] + ['1397','8']
#libquantum.output = out_dir + 'libquantum.out' 
 
#464.h264ref
h264ref = Process() #     : This used to be LiveProcess()
h264ref.executable = 'h264ref' + alpha_suffix
# TEST CMDS
#h264ref.cmd = [h264ref.executable] + ['-d', 'foreman_test_encoder_baseline.cfg']
# REF CMDS
h264ref.cmd = [h264ref.executable] + ['-d', 'foreman_ref_encoder_baseline.cfg']
#h264ref.cmd = [h264ref.executable] + ['-d', 'foreman_ref_encoder_main.cfg']
#h264ref.cmd = [h264ref.executable] + ['-d', 'sss_encoder_main.cfg']
#h264ref.output = out_dir + 'h264ref.out'
 
#465.tonto
tonto = Process() #     : This used to be LiveProcess()
tonto.executable = 'tonto' + alpha_suffix
# TEST CMDS
#tonto.cmd = [tonto.executable]
# REF CMDS
tonto.cmd = [tonto.executable]
#tonto.output = out_dir + 'tonto.out'
 
#619.lbm
lbm = Process() #     : This used to be LiveProcess()
lbm.executable = 'lbm_s' + alpha_suffix
# TEST CMDS
#lbm.cmd = [lbm.executable] + ['20', 'reference.dat', '0', '1', '100_100_130_cf_a.of']
# REF CMDS
lbm.cmd = [lbm.executable] + ['lbm.in']
#lbm.output = out_dir + 'lbm.out'
 
#620.omnetpp
omnetpp = Process() #     : This used to be LiveProcess()
omnetpp.executable = 'omnetpp_s' + alpha_suffix 
# TEST CMDS
#omnetpp.cmd = [omnetpp.executable] + ['omnetpp.ini']
# REF CMDS
omnetpp.cmd = [omnetpp.executable] + ['omnetpp.ini']
#omnetpp.output = out_dir + 'omnetpp.out'
 
#473.exchange2
exchange2 = Process() #     : This used to be LiveProcess()
exchange2.executable = 'exchange2_s' + alpha_suffix
# TEST CMDS
#exchange2.cmd = [exchange2.executable] + ['lake.cfg']
# REF CMDS
exchange2.cmd = [exchange2.executable] + ['exchange2.txt']
#exchange2.output = out_dir + 'exchange2.out'
 
#481.wrf
wrf = Process() #     : This used to be LiveProcess()
wrf.executable = 'wrf' + alpha_suffix
# TEST CMDS
#wrf.cmd = [wrf.executable]
# REF CMDS
wrf.cmd = [wrf.executable]
#wrf.output = out_dir + 'wrf.out'
 
#482.sphinx3
sphinx3 = Process() #     : This used to be LiveProcess()
sphinx3.executable = 'sphinx_livepretend' + alpha_suffix 
# TEST CMDS
#sphinx3.cmd = [sphinx3.executable] + ['ctlfile', '.', 'args.an4']
# REF CMDS
sphinx3.cmd = [sphinx3.executable] + ['ctlfile', '.', 'args.an4']
#sphinx3.output = out_dir + 'sphinx3.out'
 
#483.xalancbmk
######## NOT WORKING ###########
xalancbmk = Process() #     : This used to be LiveProcess()
xalancbmk.executable = 'xalancbmk' + alpha_suffix
# TEST CMDS
######## NOT WORKING ###########
#xalancbmk.cmd = [xalancbmk.executable] + ['-v','test.xml','xalanc.xsl']
# REF CMDS
######## NOT WORKING ###########
#xalancbmk.output = out_dir + 'xalancbmk.out'
 
#998.specrand
specrand_i = Process() #     : This used to be LiveProcess()
specrand_i.executable = 'specrand' + alpha_suffix
# TEST CMDS
#specrand_i.cmd = [specrand_i.executable] + ['324342', '24239']
# REF CMDS
specrand_i.cmd = [specrand_i.executable] + ['1255432124', '234923']
#specrand_i.output = out_dir + 'specrand_i.out'
 
#999.specrand
specrand_f = Process() #     : This used to be LiveProcess()
specrand_f.executable = 'specrand' + alpha_suffix
# TEST CMDS
#specrand_f.cmd = [specrand_f.executable] + ['324342', '24239']
# REF CMDS
specrand_f.cmd = [specrand_f.executable] + ['1255432124', '234923']
#specrand_f.output = out_dir + 'specrand_f.out'
