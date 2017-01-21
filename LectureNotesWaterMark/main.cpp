//copyRights Atish Kumar Singh

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<fstream>
#include<iostream>
#ifdef __linux__ 
    //linux code goes here
#elif _WIN32
    // windows code goes here
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows
#else
#endif

#include "Magick++.h"
#include <time.h>

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
bool bIsThumbNailWritten = false;
const int nThumbNailWidth = 300;
const int nThumbNailHeight = 200;
const bool bEnableSharpening = true; //Aha moment
const bool bShowImage = true;

int main(int argc, char* argv[])
{
	clock_t tStart = clock();

	assert(argc > 2);
	sVideoPath = argv[1];
	sTitle = argv[2];
	//sVideoPath = "../../g1USSZVWDsY";
	//sVideoPath = "../../Lecture14";
	std::ifstream inFile(sVideoPath + "_frame.list");
	std::string sFrameName;

	cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	//For reading pdf file directly. May be required for some testing
	//std::string finalImageStr = "../../tmpP/finalImage.pdf";
	//std::list<Magick::Image> imageList;
	//Magick::readImages(&imageList, finalImageStr);

	std::list<Magick::Image> imageListW;
	std::string finalImageStrI2 = "/tmp/" + sVideoPath + ".jpg";

	while(inFile >> sFrameName) {
		std::cout << sFrameName;
		std::cout << "Writing intermediate image\n";
		cv::Mat imgFrameSrc = cv::imread(sFrameName);
		if(imgFrameSrc.data == NULL)
			continue;
		if(bShowImage) cv::imshow("origImage", imgFrameSrc);

		//Sharpen image
		if (bEnableSharpening) {
			cv::Mat imgFrameInput = imgFrameSrc.clone();
			cv::GaussianBlur(imgFrameInput, imgFrameSrc, cv::Size(0, 0), 3);
			cv::addWeighted(imgFrameInput, 1.5, imgFrameSrc, -0.5, 0, imgFrameSrc);
			//cv::Mat_<float> mykernel(3, 3);
			//mykernel << -1, -1, -1, -1, 9, -1, -1, -1, -1;
			//mykernel << 1, 1, 1, 1, -7, 1, 1, 1, 1;
			//cv::Mat_<float> mykernel(5, 5);
			//mykernel << -1, -1, -1, -1, -1, -1, 2, 2, 2, -1, -1, 2, 8, 2, -1,
			//	-1, 2, 2, 2, -1, -1, -1, -1, -1, -1;
			//mykernel = mykernel / 8.0;

			//cv::filter2D(imgFrameInput, imgFrameSrc, -1, mykernel);

		}

		//Create a watermark
		cv::Mat imgFrameWM = cv::Mat::zeros(imgFrameSrc.rows, 
			imgFrameSrc.cols, imgFrameSrc.type());
		textPointX = (int)(imgFrameWM.cols/2);
		textPointY = (int)(imgFrameWM.rows - 200);
		//Font Size = 2 , thickness = 8
		//Font Size = 1.5 , thickness = 6
		if(imgFrameSrc.cols < 1000) {
			cv::putText(imgFrameWM, sWaterMark,
				cv::Point(textPointX, textPointY), intFontFace, 1.5,
				cv::Scalar(255, 255, 255), 6);
		}
		else {
			cv::putText(imgFrameWM, sWaterMark,
				cv::Point(textPointX, textPointY), intFontFace, 2,
				cv::Scalar(255, 255, 255), 8);
		}
		if(bShowImage) cv::imshow("watermark", imgFrameWM);

		//Create a source2 same as source1		
		cv::Mat imgFrameSrc2 = imgFrameSrc.clone();

		//Create a temporary black and white image just to find intensity
		cv::Mat imgFrameSrcBW = imgFrameSrc.clone();
		cv::cvtColor(imgFrameSrcBW, imgFrameSrcBW, CV_BGR2GRAY);

		//Blend watermark to source2.
		for (int i = 0; i < imgFrameWM.rows; i++) {
			for (int j = 0; j < imgFrameWM.cols; j++) {
				cv::Vec3b intensity2 = imgFrameWM.at<cv::Vec3b>(i, j);
				double intensity = intensity2.val[0];
				if (intensity == 255) {

					cv::Scalar intensity2 = imgFrameSrcBW.at<uchar>(i, j);
					double intensity3 = intensity2.val[0];
					if (intensity3 > 127) {
						imgFrameSrc2.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
					}
					else {
						imgFrameSrc2.at<cv::Vec3b>(i,j) = cv::Vec3b(255,255,255);
					}

					/*
					cv::Vec3b intensitySrc = imgFrameSrc.at<cv::Vec3b>(i, j);
					if(intensitySrc.val[0] >= 5)
						imgFrameSrc.at<cv::Vec3b>(i, j)[0] = intensitySrc.val[0] - 15;
					else 
						imgFrameSrc.at<cv::Vec3b>(i, j)[0] = intensitySrc.val[0] + 15;
					if(intensitySrc.val[1] >= 5)
						imgFrameSrc.at<cv::Vec3b>(i, j)[1] = intensitySrc.val[1] - 15;
					else 
						imgFrameSrc.at<cv::Vec3b>(i, j)[1] = intensitySrc.val[1] + 15;
					if(intensitySrc.val[2] >= 5)
						imgFrameSrc.at<cv::Vec3b>(i, j)[2] = intensitySrc.val[2] - 15;
					else 
						imgFrameSrc.at<cv::Vec3b>(i, j)[2] = intensitySrc.val[2] + 15;
					*/
				}
			}
		}

		if(bShowImage) cv::imshow("After Watermark", imgFrameSrc2);
		//Blend source1 and source2
	    cv::addWeighted(imgFrameSrc, 0.9, imgFrameSrc2, 0.1, 0, imgFrameSrc);

		if(bShowImage) cv::imshow("After Blending", imgFrameSrc);


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
		std::string sPageNo = std::to_string(nPageNo);
		cv::putText(imgFrameDes, sPageNo,
			cv::Point(textPointX, textPointY), intFontFace, 0.5, 
			cv::Scalar(0, 0, 0), 1);

		//Put Copy Right Text.
		textPointX = (int)(imgFrameDes.cols - 300);
		textPointY = (int)(imgFrameDes.rows - 20);
		cv::putText(imgFrameDes, sCopyRight,
			cv::Point(textPointX, textPointY), intFontFace, 0.5,
			cv::Scalar(0, 0, 0), 1);

		if(bShowImage) cv::imshow(window_name, imgFrameDes);

		//Write final image with some compression
		std::vector<int> params;
		if (nImageCompressionPercent > 0) {
			params.push_back(CV_IMWRITE_JPEG_QUALITY);
			params.push_back(nImageCompressionPercent);   // that's percent, so 100 == no compression, 1 == full 
		}
		cv::imwrite(finalImageStrI2, imgFrameDes, params);

		if (bIsThumbNailWritten == false) {
			//First image is written as smaller thumbnail.
			std::string sThumbNail = sVideoPath + "_thumbnail.jpg";
			cv::Mat imgFrameTN = cv::Mat::zeros(nThumbNailHeight, 
				nThumbNailWidth, imgFrameDes.type());
			resize(imgFrameDes, imgFrameTN, imgFrameTN.size());
			if(bShowImage) cv::imshow("thumbnail", imgFrameTN);
			cv::imwrite(sThumbNail, imgFrameTN, params);
			bIsThumbNailWritten = true;
		}

		Magick::readImages(&imageListW, finalImageStrI2);

		nPageNo++;
	}

	std::string finalImageStrF = sVideoPath + "N.pdf";
	Magick::writeImages(imageListW.begin(), imageListW.end(), finalImageStrF);

	inFile.close();

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	
	if(bShowImage) cv::waitKey(0);

	return 0;
}
