DOCUMENTATION :

* Le Manuel d'utilisation rapide d'AGECYMO est accessible depuis le menu
Help de l application.

* Une documentation technique g�n�r�e automatiquement par DOXYGEN se
  trouve dans le repertoire AGECYMO/doc/



INSTALLATION :

* Qt doit �tre install�

* Pour compiler AGECYMO :
  (en supposant que vous vous trouvez dans le repertoire o� l'archive a
  �t� d�compress�e)

  export LD_LIBRARY_PATH= <AbsolutePath>/AGECYMO/lib/
  cd AGECYMO/src/
  qmake
  make

* Pour compiler les plugins

  cd AGECYMO/src/plugins/
  qmake	
  make

  Pour les installer :

  cd AGECYMO/src/plugins/	
  cp ioVRML/libioVRML.plg.so.1.0.0 libioVRML.plg
  (proceder de meme pour chaque plugin en renommant l'extension du
  plugin en .plg)


LANCEMENT DE L'APPLICATION :

  cd AGECYMO/src/	   
  ./modeler		   