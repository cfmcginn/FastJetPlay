FastJetPlay
===========

Learning FastJet with some playground scripts

Gonna need access to an up-to-date version of fastjet and fjcontrib

Can get a tar of fastjet-3.0.6 here: http://fastjet.fr/
Would recommend throwing it a level above the repo.
Run "tar -xzvf fastjet-3.0.6.tar.gz" to unpack

To Install: 
  * ./configure --prefix=$PWD/../fastjet-install
  * make
  * make check
  * make install
  

To get fjcontrib, up to date:
  *  svn checkout http://fastjet.hepforge.org/svn/contrib/trunk fjcontrib 
  *  cd fjcontrib
  *  scripts/update-contribs.sh
  *  ./configure --fastjet-config=
  *  make
  *  make check
  *  make install


We want a specific version of nsubjettiness code, to grab go to your fjcontrib directory:

