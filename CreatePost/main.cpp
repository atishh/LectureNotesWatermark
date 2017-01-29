//copyRights Atish Kumar Singh

#include<fstream>
#include<iostream>
#include <time.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	clock_t tStart = clock();

	std::cout << "argc = " << argc << std::endl;
    for(int i = 0; i < argc; i++) {
	std::cout << argv[i] << std::endl;
	}
	assert(argc > 4);
	std::string sVideoPath = argv[1];
	std::string sTitle = argv[2];
	std::string sChapter = argv[3];
	std::string sYoutube = argv[4];

	std::ofstream outFile("post.txt", std::ios::app);

	outFile << "<div class=\"home-columns clearfix\">" << std::endl;
	outFile << sChapter << std::endl;
	outFile << "<div class=\"one-half\">" << std::endl;
	outFile << "<iframe class=\"iframe-size\" src=\"";
	outFile << sYoutube;
	outFile << "\" width=\"400\" height=\"200\" frameborder=\"0\" allowfullscreen=\"allowfullscreen\"></iframe>" << std::endl;
	outFile << "</div>" << std::endl;
	outFile << "<div class=\"one-half last\">" << std::endl;
	outFile << "<iframe class=\"iframe-size\" src=\"/home/atish/Desktop/lecture videos/DigitalImageProcessingPKBiswas/";
	outFile << sVideoPath << "N.pdf";
	outFile << "\" style=\"width:400px; height:200px;\" frameborder=\"0\" allowfullscreen=\"\"></iframe>" << std::endl;
	outFile << "<nav class=\"site-nav site-header-nav departments-nav clearfix\"> <ul>" << std::endl;
	outFile << "<li><a href=\"/home/atish/Desktop/lecture videos/DigitalImageProcessingPKBiswas/";
	outFile << sVideoPath << "N.pdf";
	outFile << "\" download=\"" << sVideoPath << "N.pdf" ;
	outFile << "\" class = \"btn-element\" >Download</a></li>" << std::endl;
	outFile << "<li><a href=\"/home/atish/Desktop/lecture videos/DigitalImageProcessingPKBiswas/";
	outFile << sVideoPath << "N.pdf";
	outFile << "\" class = \"btn-element\" >View</a></li>" << std::endl;
	outFile << "</ul></nav>" << std::endl;
	outFile << "</div>" << std::endl;
	outFile << "</div>" << std::endl;
	outFile.close();
	return 0;
}

/*
<div class="home-columns clearfix">
Lecture 1: Topology
<div class="one-half">
<iframe class="iframe-size" src="https://www.youtube.com/embed/VkV8xp-JFlA" width="400" height="200" frameborder="0" allowfullscreen="allowfullscreen"></iframe>
</div>
<div class="one-half last">
<iframe class="iframe-size" src="/home/atish/Desktop/lecture videos/DigitalImageProcessingPKBiswas/mod01lec01-mod01lec01N.pdf" style="width:400px; height:200px;" frameborder="0" allowfullscreen=""></iframe>

<nav class="site-nav site-header-nav departments-nav clearfix"> <ul>
<li><a href="/home/atish/Desktop/lecture videos/DigitalImageProcessingPKBiswas/mod01lec01-mod01lec01N.pdf" download="mod01lec01-mod01lec01N.pdf" class = "btn-element" >Download</a></li>
<li><a href="/home/atish/Desktop/lecture videos/DigitalImageProcessingPKBiswas/mod01lec01-mod01lec01N.pdf" class = "btn-element" >View</a></li>
</ul></nav>
</div>
</div>
*/

