#include "user_command.h"


/***********************************************
 * ����̨������Բ���ͼ��
 **********************************************/
bool UserCommand(char & command, cv::Mat & image)
{
	switch (command)
	{
	case '1': { /* ��ʼ��ʾ��Ƶ */
		cvNamedWindow("video from server", 1);
		cv::imshow("video from server", image);
		cv::waitKey(1);
		break;
	}
	case '2': { /* �ر���Ƶ���� */
		cvDestroyWindow("video from server");
		command = '2';
		break;
	}
	case '3': { /* ���浱ǰͼƬ */
		// ����·��
		time_t t = time(0);
		char path[100];
		// scanf("����·�� %s", &path);
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
	case '4': { /* ����ʶ�� */
		//cvNamedWindow("video from server", 1);
		//cv::cvtColor(image, image, CV_BGR2GRAY);
		//cv::threshold(image, image, 0, 255, CV_THRESH_OTSU);

		cv::CascadeClassifier ccf;   //��������������
		if (!ccf.load(xmlPath))   //����ѵ���ļ�
		{
			printf("���ܼ���ָ����xml�ļ�\n");
			return 0;
		}
		vector<cv::Rect> faces;  //����һ�������������������
		cv::Mat gray;
		cvtColor(image, gray, CV_BGR2GRAY);		//ת���ɻҶ�ͼ����Ϊharr�����ӻҶ�ͼ����ȡ
		equalizeHist(gray, gray);				//ֱ��ͼ������
		ccf.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(10, 10), cv::Size(100, 100)); //�������
		for (vector<cv::Rect>::const_iterator iter = faces.begin();iter != faces.end();iter++)
		{
			cv::rectangle(image, *iter, cv::Scalar(0, 0, 255), 2, 20); //������������
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
* ʱ���ˮӡ
*****************************/
void WaterMask(cv::Mat & image)
{
	// ��ȡϵͳʱ��
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A %z", localtime(&t));

	//���û����ı�����ز���  
	std::string text = tmp;
	int    font_face = cv::FONT_HERSHEY_PLAIN;	// ����
	double font_scale = 1;						// �ߴ�����
	int    thickness = 1;						// �������
	int    baseline;							// ����
	cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline); // ��ȡ�ı���ĳ��� 

	//���ı��� (x, y) ����  
	cv::Point origin;
	origin.x = 45;
	origin.y = 30;
	cv::putText(image, text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
}