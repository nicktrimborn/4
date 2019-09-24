#!/bin/sh
# Pass is Group4
gpg --decrypt gitprofile.tar.gz.gpg | tar xpvz -C $HOME
cd ~/
git clone git@course-gitlab.tuni.fi:tie-50307-real-time-systems_2019-2020/4.git
