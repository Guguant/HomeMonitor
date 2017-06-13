#include "user_command.h"


/***********************************************
 * 控制台命令，用以操作图像
 **********************************************/
bool UserCommand(char & command, cv::Mat & image)
{
	switch (command)
	{
	case '1': { /* 开始显示视频 */
		cvNamedWindow("video from server", 1);
		cv::imshow("video from server", image);
		cv::waitKey(1);
		break;
	}
	case '2': { /* 关闭视频窗口 */
		cvDestroyWindow("video from server");
		command = '2';
		break;
	}
	case '3': { /* 保存当前图片 */
		// 保存路径
		time_t t = time(0);
		char path[100];
		// scanf("输入路径 %s", &path);
		strftime(path, sizeof(path), "C:\\Users\\sunyiming\\Desktop\\savedimage\\%Y-%m-%d-%H-%M-%S.jpg", localtime(&t));
		if (cv::imwrite(path, image))
		{
			printf("saved as %s\n", path);
		}
		else {
			printf("failed to save!\n");
		}
		command = '1';
		break;
	}
	case '4': { /* 人脸识别 */
		//cvNamedWindow("video from server", 1);
		//cv::cvtColor(image, image, CV_BGR2GRAY);
		//cv::threshold(image, image, 0, 255, CV_THRESH_OTSU);

		cv::CascadeClassifier ccf;   //创建分类器对象
		if (!ccf.load(xmlPath))   //加载训练文件
		{
			printf("不能加载指定的xml文件\n");
			return 0;
		}
		vector<cv::Rect> faces;  //创建一个容器保存检测出来的脸
		cv::Mat gray;
		cvtColor(image, gray, CV_BGR2GRAY);		//转换成灰度图，因为harr特征从灰度图中提取
		equalizeHist(gray, gray);				//直方图均衡行
		ccf.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(10, 10), cv::Size(100, 100)); //检测人脸
		for (vector<cv::Rect>::const_iterator iter = faces.begin();iter != faces.end();iter++)
		{
			cv::rectangle(image, *iter, cv::Scalar(0, 0, 255), 2, 20); //画出脸部矩形
		}
		faces.clear();
		cv::imshow("video from server", image);
		cv::waitKey(1);
		//command = '1';
		break;
	}
	case '5': { /* help */
		help();
		command = '2';
		break;
	}
	default: { /* others */
		command = '1';
	}
	}
	return true;
}



/******************************
* 时间戳水印
*****************************/
void WaterMask(cv::Mat & image)
{
	// 获取系统时间
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A %z", localtime(&t));

	//设置绘制文本的相关参数  
	std::string text = tmp;
	int    font_face = cv::FONT_HERSHEY_PLAIN;	// 字体
	double font_scale = 1;						// 尺寸因子
	int    thickness = 1;						// 线条宽度
	int    baseline;							// 基线
	cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline); // 获取文本框的长宽 

	//将文本框 (x, y) 绘制  
	cv::Point origin;
	origin.x = 45;
	origin.y = 30;
	cv::putText(image, text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
}