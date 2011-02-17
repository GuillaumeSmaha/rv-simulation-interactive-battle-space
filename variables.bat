@echo off
set dir=%CD%
echo Placez ce fichier dans un repertoire contenant les repertoires racines de ogre et cegui (renommez les en 'ogre' et 'cegui')
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment" /v OIS_HOME /t REG_SZ /d "%dir%\ogre"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment" /v OGRE_HOME /t REG_SZ /d "%dir%\ogre"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment" /v CEGUI_ROOT /t REG_SZ /d "%dir%\cegui"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment" /v BOOST_ROOT /t REG_SZ /d "%dir%\ogre\boost_1_42"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment" /v BULLET_ROOT /t REG_SZ /d "%dir%\bullet"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment" /v OGREBULLET_HOME /t REG_SZ /d "%dir%\ogrebullet"
 
 
