# CSCI-5593_Advanced_Computer_Architecture

1. Install related packages

sudo apt install scons build-essential git m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev python-dev python automake libboost-all-dev

2. Download gem5 src code

git clone https://gem5.googlesource.com/public/gem5

3. make changes in gem5 src code
copy ~/ruby folder from this repository to ~/gem5/src/mem/.

cp -r ~/CSCI-5593_Advanced_Computer_Architecture/Project/ruby ~/gem5src/mem/.

4. compile gem5

	i.  cd ~/gem5
	ii. scons build/X86/gem5.opt RUBY=True PROTOCOL=MESI_Three_Level -j3
	
5. Download Kernel and default workloads for gem5 X86 and place at appropriate position

	1. wget -o http://www.m5sim.org/dist/current/x86/x86-system.tar.bz2
	2. tar xjf x86-system.tar.bz2
	3. sudo mkdir /dist
	


		