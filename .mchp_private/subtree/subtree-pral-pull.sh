#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Pulling changes from subtree 'subrepo-pral' branch 'main' into recently checked out working branch...
git subtree pull --prefix="epc9137-firmware.X/sources/common/p33c_pral" subrepo-pral main --squash 
echo Pull complete
echo
echo Press Enter to exit
read
