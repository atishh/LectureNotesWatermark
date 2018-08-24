#!/bin/bash

rm output.txt
touch output.txt
COUNTER=0
while IFS= read -r line; do
      echo "$line"
      echo "/home/atish/projects/lecturenoteswatermark_build/LNWaterMark $line " |& tee /tmp/atish_w.sh
      source /tmp/atish_w.sh |& tee -a output.txt
      let COUNTER=COUNTER+1
done < info.list

