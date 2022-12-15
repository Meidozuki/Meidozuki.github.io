#!/bin/bash
fnames=$(ls */img/*.dot)
echo $fnames

for name in $fnames; do
  dot -O -Tjpg $name
done
