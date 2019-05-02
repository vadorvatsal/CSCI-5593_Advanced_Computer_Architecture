# CSCI-5593_Advanced_Computer_Architecture
  
1. Install related packages  
  
sudo apt install scons build-essential git m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev python-dev python automake libboost-all-dev  
  
2. Download gem5 src code  
  
	i.  cd  
	ii. git clone https://gem5.googlesource.com/public/gem5  
  
3. make changes in gem5 src code  
copy ~/ruby folder from this repository to ~/gem5/src/mem/.  
  
cp -r ~/CSCI-5593_Advanced_Computer_Architecture/Project/ruby ~/gem5src/mem/.  
  
4. compile gem5  
  
	i.   cd ~/gem5  
	ii.  scons build/X86/gem5.opt RUBY=True PROTOCOL=MESI_Three_Level -j3  
	iii. if compilation fails, then it is because of missing package in your linux. Install that package and then repeat above step  
  
5. Download Kernel and default workloads for gem5 X86 and place at appropriate position  
  
	i.    cd  
	ii.   wget http://www.m5sim.org/dist/current/x86/x86-system.tar.bz2  
	iii.  tar xjf x86-system.tar.bz2  
	iv.   mv disks/linux-x86.img disks/x86root.img  
	v.    sudo mkdir -p /dist/m5/system  
	vi.   sudo chown -R "username:usergroup" /dist  
	vii.  mv ~/binaries /dist/m5/system/.  
	viii. mv ~/disks /dist/m5/system/.  
  
6.  Run gem5  
  
~/gem5/build/X86/gem5.opt ~/gem5/configs/example/fs.py --num-cpus=1 --ruby --l1d_size=32kB --l1i_size=32kB --l2_size=256kB --l3_size=4mB --mem-size=4GB --l1d_assoc=8 --l1i_assoc=8 --l2_assoc=8 --l3_assoc=16 --maxinsts=10000 --kernel=/dist/m5/system/binaries/x86_64-vmlinux-2.6.22.9  
  
7. see stats  
  
	You can see all the stats in ~/gem5/m5out/stats.txt  
  
8. If someone wants to change replacement policy, then do following steps  
  
	i.   open file ~/gem5/src/mem/ruby/structures/RubyCache.py  
	ii.  update imports and replacement policies (simply by doing comment and uncomment)  
	iii. recompile gem5 using step 4  
  
9. If you want to run gem5 with SPEC CPU2017  
  
  	Read "SPEC and Gem5 IntegrationDoc.docx" document before this
  	
	i.   cp ~/spec17_config.py ~/gem5/configs/example/.  
	ii.  cp ~/spec2017_benchmarks.py ~/gem5/configs/example/.  
	iii. cp ~/spec2017_benchmarks.pyc ~/gem5/configs/example/.  
	iv.  cp ~/run_gem5_x86_spec17_benchmark.sh ~/gem5/.  
	v.   chmod +x run_gem5_x86_spec17_benchmark.sh  
	vi.  ./run_gem5_x86_spec17_benchmark.sh $benchmark_name $output_dir  
	vii. benchmark_name can be  
			perlbench  
			imagick  
			mcf  
			exchange2  
			omnetpp  
			povray  
			lbm  
			leela  
  