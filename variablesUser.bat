@echo off
set dir=%CD%
echo Placez ce fichier dans un repertoire contenant les repertoires racines de ogre et cegui (renommez les en 'ogre' et 'cegui')
reg add "HKEY_USER LOCAL\Environment" /v OIS_HOME /t REG_SZ /d "%dir%\ogre"
reg add "HKEY_USER LOCAL\Environment" /v OGRE_HOME /t REG_SZ /d "%dir%\ogre"
reg add "HKEY_USER LOCAL\Environment" /v CEGUI_ROOT /t REG_SZ /d "%dir%\cegui"
reg add "HKEY_USER LOCAL\Environment" /v BOOST_ROOT /t REG_SZ /d "%dir%\ogre\boost_1_44"
reg add "HKEY_USER LOCAL\Environment" /v BULLET_ROOT /t REG_SZ /d "%dir%\bullet"
reg add "HKEY_USER LOCAL\Environment" /v OGREBULLET_HOME /t REG_SZ /d "%dir%\ogrebullet"
reg add "HKEY_USER LOCAL\Environment" /v OGG_HOME /t REG_SZ /d "%dir%\ogg"
reg add "HKEY_USER LOCAL\Environment" /v VORBIS_HOME /t REG_SZ /d "%dir%\vorbis"
reg add "HKEY_USER LOCAL\Environment" /v OGREAL_HOME /t REG_SZ /d "%dir%\ogreal"
 
 
