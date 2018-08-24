#!/bin/bash

COUNTER=0
while IFS= read -r line; do
      echo "$line"
      file1=`echo "$line" | cut -d '"' -f 8 | sed "s/^/download_mp4.php?/" | sed 's/^/"/' | sed 's/$/"/' `
      echo $file1
      file2=`echo $line | cut -d '=' -f 3 | cut -d '&' -f 1 | sed 's/^/"/' | sed 's/$/"/' `
      echo $file2
      echo "mv $file1 $file2" |& tee /tmp/atish.sh
      source /tmp/atish.sh
      let COUNTER=COUNTER+1
done < info.list

