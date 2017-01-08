//copyRights Atish Kumar Singh

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows
#include "Magick++.h"

/// Global Variables
const int nImageCompressionPercent = 85;
char* window_name = "copyMakeBorder Demo";
std::string sCopyRight = "created by domainname.com";
/*
cv::Mat src, dst;
int top, bottom, left, right;
int borderType;
cv::Scalar value;

cv::RNG rng(12345);
*/
/** @function main  */
int main(void)
{
	cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	std::string finalImageStr = "../../tmpP/finalImage.pdf";
//	std::string finalImageStr = "C:\\Users\\atishks\\Documents\\Visual Studio 2015\\Projects\\tmpP\\finalImage.pdf";
	std::list<Magick::Image> imageList;

	Magick::readImages(&imageList, finalImageStr);

	std::list<Magick::Image> imageListW;

	std::string finalImageStrI = "../../tmpW/intermedia1.jpg";
	std::string finalImageStrI2 = "../../tmpW/intermedia2.jpg";
	for (std::list<Magick::Image>::iterator it = imageList.begin(); it != imageList.end(); ++it) {
		std::cout << "Writing intermediate image\n";
		(*it).write(finalImageStrI);
		cv::Mat imgFrameSrc = cv::imread(finalImageStrI);
		cv::imshow(finalImageStrI, imgFrameSrc);

		int top, bottom, left, right;
		/// Initialize arguments for the filter
		top = 50; bottom = 50;
		left = 0; right = 0;
		cv::Mat imgFrameDes = imgFrameSrc;
		cv::Scalar value = cv::Scalar(255, 255, 255);
		int borderType = cv::BORDER_CONSTANT;
		cv::copyMakeBorder(imgFrameSrc, imgFrameDes, top, bottom, left, right, borderType, value);
		
		int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
		int textPointX = (int)(imgFrameDes.cols-300); 
		int textPointY = (int)(imgFrameDes.rows-20);
		cv::putText(imgFrameDes, sCopyRight,
			cv::Point(textPointX, textPointY), intFontFace, 0.5, 
			cv::Scalar(0, 0, 0), 1);
		cv::imshow(window_name, imgFrameDes);

		std::vector<int> params;
		if (nImageCompressionPercent > 0) {
			params.push_back(CV_IMWRITE_JPEG_QUALITY);
			params.push_back(nImageCompressionPercent);   // that's percent, so 100 == no compression, 1 == full 
		}
		cv::imwrite(finalImageStrI2, imgFrameDes, params);

		Magick::readImages(&imageListW, finalImageStrI2);
	}

	std::string finalImageStrF = "../../tmpP/FinalImageF.pdf";
	Magick::writeImages(imageListW.begin(), imageListW.end(), finalImageStrF);

	cv::waitKey(0);

	return 0;
}