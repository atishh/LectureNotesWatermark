//copyRights Atish Kumar Singh

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <fstream>
#include<iostream>
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows
#include "Magick++.h"

/// Global Variables
std::string sVideoPath;
const int nImageCompressionPercent = 85;
char* window_name = "copyMakeBorder Demo";
std::string sCopyRight = "created by domainname.com";
std::string sWaterMark = "domainname.com";
std::string sTitle = "Gravity & Lights: Lecture 2: Hyperplane";
int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
int textPointX;
int textPointY;
int nPageNo = 1;

int main(void)
{
	sVideoPath = "../../mod03lec10";
	std::ifstream inFile(sVideoPath + "_frame.list");
	std::string sFrameName;

	cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	std::string finalImageStr = "../../tmpP/finalImage.pdf";
	//std::list<Magick::Image> imageList;

	//Magick::readImages(&imageList, finalImageStr);

	std::list<Magick::Image> imageListW;

	std::string finalImageStrI2 = "../../tmpW/intermedia2.jpg";
	while(inFile >> sFrameName) {
		std::cout << sFrameName;
		std::cout << "Writing intermediate image\n";
		sFrameName = "../" + sFrameName; //This line is just temporary.
		cv::Mat imgFrameSrc = cv::imread(sFrameName);
		cv::imshow("origImage", imgFrameSrc);

		//Create a watermark
		cv::Mat imgFrameWM = cv::Mat::zeros(imgFrameSrc.rows, 
			imgFrameSrc.cols, imgFrameSrc.type());
		textPointX = (int)(imgFrameWM.cols/2);
		textPointY = (int)(imgFrameWM.rows - 200);
		cv::putText(imgFrameWM, sWaterMark,
			cv::Point(textPointX, textPointY), intFontFace, 2,
			cv::Scalar(255, 255, 255), 8);
		cv::imshow("watermark", imgFrameWM);

		//Blend watermark to original.
		for (int i = 0; i < imgFrameWM.rows; i++) {
			for (int j = 0; j < imgFrameWM.cols; j++) {
				cv::Vec3b intensity2 = imgFrameWM.at<cv::Vec3b>(i, j);
				double intensity = intensity2.val[0];
				if (intensity == 255) {
					cv::Vec3b intensitySrc = imgFrameSrc.at<cv::Vec3b>(i, j);
					if(intensitySrc.val[0] >= 5)
						imgFrameSrc.at<cv::Vec3b>(i, j)[0] = intensitySrc.val[0] - 5;
					else 
						imgFrameSrc.at<cv::Vec3b>(i, j)[0] = intensitySrc.val[0] + 5;
					if(intensitySrc.val[1] >= 5)
						imgFrameSrc.at<cv::Vec3b>(i, j)[1] = intensitySrc.val[1] - 5;
					else 
						imgFrameSrc.at<cv::Vec3b>(i, j)[1] = intensitySrc.val[1] + 5;
					if(intensitySrc.val[2] >= 5)
						imgFrameSrc.at<cv::Vec3b>(i, j)[2] = intensitySrc.val[2] - 5;
					else 
						imgFrameSrc.at<cv::Vec3b>(i, j)[2] = intensitySrc.val[2] + 5;
				}
			}
		}
		cv::imshow("After Blending", imgFrameSrc);


		//Make top and bottom BORDER
		int top, bottom, left, right;
		/// Initialize arguments for the filter
		top = 50; bottom = 50;
		left = 0; right = 0;
		cv::Mat imgFrameDes = imgFrameSrc;
		cv::Scalar value = cv::Scalar(255, 255, 255);
		int borderType = cv::BORDER_CONSTANT;
		cv::copyMakeBorder(imgFrameSrc, imgFrameDes, top, bottom, left, right, borderType, value);
		
		//Put Introduction Text.
		textPointX = (int)(30);
		textPointY = (int)(30);
		cv::putText(imgFrameDes, sTitle,
			cv::Point(textPointX, textPointY), intFontFace, 0.5,
			cv::Scalar(0, 0, 0), 1);

		//Put Page number Text.
		textPointX = (int)(imgFrameDes.cols-100); 
		textPointY = (int)(30);
		std::string sPageNo = "page " + std::to_string(nPageNo);
		cv::putText(imgFrameDes, sPageNo,
			cv::Point(textPointX, textPointY), intFontFace, 0.5, 
			cv::Scalar(0, 0, 0), 1);

		//Put Copy Right Text.
		textPointX = (int)(imgFrameDes.cols - 300);
		textPointY = (int)(imgFrameDes.rows - 20);
		cv::putText(imgFrameDes, sCopyRight,
			cv::Point(textPointX, textPointY), intFontFace, 0.5,
			cv::Scalar(0, 0, 0), 1);

		cv::imshow(window_name, imgFrameDes);

		//Write final image with some compression
		std::vector<int> params;
		if (nImageCompressionPercent > 0) {
			params.push_back(CV_IMWRITE_JPEG_QUALITY);
			params.push_back(nImageCompressionPercent);   // that's percent, so 100 == no compression, 1 == full 
		}
		cv::imwrite(finalImageStrI2, imgFrameDes, params);

		Magick::readImages(&imageListW, finalImageStrI2);

		nPageNo++;
	}

	std::string finalImageStrF = "../../tmpP/FinalImageF.pdf";
	Magick::writeImages(imageListW.begin(), imageListW.end(), finalImageStrF);

	inFile.close();
	cv::waitKey(0);

	return 0;
}