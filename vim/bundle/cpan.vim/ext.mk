


INSTALL_CPANM_TO=~/bin/cpanm

install-cpanm-git:
	cd /tmp ; \
		git clone git://github.com/miyagawa/cpanminus.git ; \
			cd cpanminus ;  \
				perl Makefile.PL && make && sudo make install

install-cpanm:
	mkdir -p ~/bin/
	if [[ -n `which wget` ]] ; then wget -c http://xrl.us/cpanm -O $(INSTALL_CPANM_TO) ; \
	elif [[ -n `which curl` ]] ; then curl http://xrl.us/cpanm -o $(INSTALL_CPANM_TO) ; \
	fi
	@chmod +x $(INSTALL_CPANM_TO)
	@echo "Please add ~/bin to your PATH env variable"
