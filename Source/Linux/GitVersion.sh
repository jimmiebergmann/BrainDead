#!/bin/bash

GITHASH=`git log --pretty=format:"%H" -1`
GITHASHSHORT=`git log --pretty=format:"%h" -1`
GITDATE=`git log --pretty=format:"%cd" -1`
GITROLLINGCOUNT=`git log --pretty=format:'' | wc -l`
GITHEADER=./Headers/GitVersion.hpp
PROJECT=BRAINDEAD

printf "Generating $PROJECT Git Version Header...\n"
printf "Revision: $GITROLLINGCOUNT [$GITHASH] $GITDATE\n"

printf "#ifndef __%s_GITVERSION_HPP__\n" $PROJECT > $GITHEADER
printf "#define __%s_GITVERSION_HPP__\n\n" $PROJECT >> $GITHEADER
printf "#define GIT_COMMITHASH			\"%s\"\n" "$GITHASH" >> $GITHEADER
printf "#define GIT_COMMITHASHSHORT		\"%s\"\n" "$GITHASHSHORT" >> $GITHEADER
printf "#define GIT_COMMITTERDATE		\"%s\"\n" "$GITDATE" >> $GITHEADER
printf "#define GIT_ROLLINGCOUNT		%d\n\n" $GITROLLINGCOUNT >> $GITHEADER
printf "#endif\n" >> $GITHEADER

printf "Done\n"
