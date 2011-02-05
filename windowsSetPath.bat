@echo off
echo Set Var Env ...
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v BOOST_ROOT /t REG_SZ /d "C:\Users\Administrateur\Downloads\OgreSDK_vc9_v1-7-2\boost_1_44"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v OGRE_HOME /t REG_SZ /d "C:\Users\Administrateur\Downloads\OgreSDK_vc9_v1-7-2"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v CEGUI_HOME /t REG_SZ /d "C:\Users\Administrateur\Downloads\CEGUI-SDK-0.7.5-vc9"
echo Necessite un redemarrage ! ou Fermer et rouvrir la session !
pause