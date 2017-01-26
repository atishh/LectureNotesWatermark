#!/bin/csh

rm output.txt
touch output.txt
foreach file (`cat video.list`)
	echo $file |& tee -a output.txt
	/home/atish/projects/build/lecturenotes/LectureNote $file |& tee -a output.txt
end

rm -rf /tmp/youtube.list
touch /tmp/youtube.list
set j = 0
while ( $j <= 60 )
  wget -O - http://nptel.ac.in/courses/117105135/${j} | grep youtube | grep movie |& tee -a /tmp/youtube.list
  echo "Welcome $j times"
  @ j++
end

//To merge columns of 2 files
paste info.list /tmp/youtube.list > /tmp/atish10
