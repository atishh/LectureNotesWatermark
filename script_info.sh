#!/bin/sh

courseid=106105151
category="CS"
course="CPP"

rm -rf info.list
touch info.list
j=1
while [ $j -lt 100 ]
do
  rm -rf /tmp/atish_i
  wget -O /tmp/atish_i http://nptel.ac.in/courses/${courseid}/${j}
  title=`grep breadcrumbs-course /tmp/atish_i -A 10 | grep nbsp | cut -d '&' -f 1 | cut -d '>' -f 3 | sed 's/^/"/' | sed 's/$/"/' `
  chapter=`grep breadcrumbs-course /tmp/atish_i -A 10 | grep lecturename | cut -d '>' -f 3 | cut -d '<' -f 1 | sed "s/^/Lecture ${j}: /" |sed 's/^/"/' | sed 's/$/"/' `
  youtube=`grep youtube /tmp/atish_i | grep embed | cut -d '?' -f 1 | cut -d '/' -f 5 |sed 's/^/"/' | sed 's/$/"/' `
  download=`grep download_mp4 /tmp/atish_i | head -n 1 | cut -d '"' -f 2 | cut -d '?' -f 2 | sed 's/^/"/' | sed 's/$/"/' `
  filename=`grep "mod.*lec" /tmp/atish_i | head -n 1 | cut -d "." -f 3 | cut -d "/" -f 7 | sed 's/^/"/' | sed 's/$/"/' `
  echo $j $title $chapter $youtube $download $filename $category $course |& tee -a info.list
  echo "Welcome $j times"
  j=`expr $j + 1`
done
