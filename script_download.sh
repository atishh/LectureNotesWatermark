#!/bin/bash

COUNTER=0
while IFS= read -r line; do
      echo "$line"
      download=`echo "$line" | cut -d '"' -f 8 | sed "s/^/https:\/\/nptel.ac.in\/courses\/download_mp4.php?/" | sed 's/^/"/' | sed 's/$/"/' `
      file2=`echo $line | cut -d '=' -f 3 | cut -d '&' -f 1 | sed 's/^/"/' | sed 's/$/"/' `
      echo "wget -O ${file2} ${download} " |& tee /tmp/atish_d.sh
      source /tmp/atish_d.sh
      let COUNTER=COUNTER+1
done < info.list

