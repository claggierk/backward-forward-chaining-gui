#!/bin/bash

./clean.sh

echo " ***** backward-forward-chaining ***********************************"

g++ -o chaining-gui *.h *.cc $(pkg-config gtk+-2.0 --cflags) $(pkg-config gtk+-2.0 --libs) $(pkg-config --cflags libglade-2.0) $(pkg-config --libs libglade-2.0)
compiled_status=$?

if [[ $compiled_status -eq 0 ]]
then
    echo "Compilation success!"
    command="./chaining-gui"
    $command
else
    echo "failed compilation"
    exit 2
fi

echo " *******************************************************************"
echo ""

