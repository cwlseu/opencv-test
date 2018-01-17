#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void test_4_points()
{  
    Mat img = cv::imread("../res/face_01.jpg");  
    int img_height = img.rows;  
    int img_width = img.cols;  
    vector<Point2f> corners(4);

    corners[0] = Point2f(0, 0);  
    corners[1] = Point2f(img_width-1, 0);  
    corners[2] = Point2f(0, img_height-1);  
    corners[3] = Point2f(img_width-1, img_height-1); 

    vector<Point2f> corners_trans(4); 
    std::cout <<"height:" <<img_height << "   width:" << img_width << std::endl;

    corners_trans[0] = Point2f((img_width-1)*1/4, (img_height-1)*1/5);  
    corners_trans[1] = Point2f(img_width-1, 0);  
    corners_trans[2] = Point2f(0, img_height-1);  
    corners_trans[3] = Point2f((img_width-1)*3/4, (img_height-1)*3/5);
    

    Mat transform = getPerspectiveTransform(corners, corners_trans);  

    vector<Point2f> ponits, points_trans;
    for(int i=0;i<img_height;i++){  
        for(int j=0;j<img_width;j++){  
            ponits.push_back(Point2f(j,i));  
        }  
    }  
  
    perspectiveTransform( ponits, points_trans, transform);  
    Mat img_trans = Mat::zeros(img_height,img_width,CV_8UC3);  
    int count = 0;  
    for(int i=0;i<img_height;i++){  
        uchar* p = img.ptr<uchar>(i);  
        for(int j=0;j<img_width;j++){  
            int y = points_trans[count].y;  
            int x = points_trans[count].x;  
            uchar* t = img_trans.ptr<uchar>(y);  
            t[x*3]  = p[j*3];  
            t[x*3+1]  = p[j*3+1];  
            t[x*3+2]  = p[j*3+2];  
            count++;  
        }  
    }  
    cv::imwrite("perspective.jpg", img_trans); 
    
    std::cout << "{";
    for(int i = 0; i < 4; i++)
        std::cout << "{" << corners[i].x <<","<< corners[i].y <<"},";
    std::cout << "}" << std::endl;
    std::cout << std::endl;

    std::cout << "{";
    for(int i = 0; i < 4; i++)
        std::cout << "{" << corners_trans[i].x <<","<< corners_trans[i].y <<"},";
    std::cout << "};" << std::endl;
    std::cout << std::endl;
    
    std::cout<<"{";
    for(int i = 0; i < 3; i++)
    {
        
        std::cout<<"{";
        for(int j = 0; j < 3; j++)
        {
            std::cout << transform.at<double>(i, j) << ",";
        }
        std::cout<<"},"<< std::endl;
    }    
    std::cout<<"};"<< std::endl;
}

void test_multi_points()
{
    Mat img = cv::imread("../res/face_01.jpg");  
    int img_height = img.rows;  
    int img_width = img.cols; 
    std::cout <<"height:" <<img_height << "   width:" << img_width << std::endl;

    vector<Point2f> corners(6);

    corners[0] = Point2f(0, 0);  
    corners[1] = Point2f(img_width-1, 0);  
    corners[2] = Point2f(0, img_height-1);  
    corners[3] = Point2f(img_width-1, img_height-1); 
    corners[4] = Point2f(img_width/2, img_height/2);
    corners[5] = Point2f(img_width/3, img_height/3);
    
    vector<Point2f> corners_trans(6); 

    corners_trans[0] = Point2f((img_width-1)*1/4, (img_height-1)*1/5);  
    corners_trans[1] = Point2f(img_width-1, 0);  
    corners_trans[2] = Point2f(0, img_height-1);  
    corners_trans[3] = Point2f((img_width-1)*3/4, (img_height-1)*3/5);
    corners_trans[4] = Point2f(img_width/2, img_height/2);
    corners_trans[5] = Point2f(img_width/3, img_height/5);
    
    

    Mat transform = getPerspectiveTransform(corners, corners_trans);  

    vector<Point2f> ponits, points_trans;
    for(int i=0;i<img_height;i++){  
        for(int j=0;j<img_width;j++){  
            ponits.push_back(Point2f(j,i));  
        }  
    }  
  
    perspectiveTransform( ponits, points_trans, transform);  
    Mat img_trans = Mat::zeros(img_height,img_width,CV_8UC3);  
    int count = 0;  
    for(int i=0;i<img_height;i++){  
        uchar* p = img.ptr<uchar>(i);  
        for(int j=0;j<img_width;j++){  
            int y = points_trans[count].y;  
            int x = points_trans[count].x;  
            uchar* t = img_trans.ptr<uchar>(y);  
            t[x*3]  = p[j*3];  
            t[x*3+1]  = p[j*3+1];  
            t[x*3+2]  = p[j*3+2];  
            count++;  
        }  
    }  
    cv::imwrite("boy_trans.png", img_trans); 
    
    std::cout << "{";
    for(int i = 0; i < 4; i++)
        std::cout << "{" << corners[i].x <<","<< corners[i].y <<"},";
    std::cout << "}" << std::endl;
    std::cout << std::endl;

    std::cout << "{";
    for(int i = 0; i < 4; i++)
        std::cout << "{" << corners_trans[i].x <<","<< corners_trans[i].y <<"},";
    std::cout << "};" << std::endl;
    std::cout << std::endl;
    
    std::cout<<"{";
    for(int i = 0; i < 3; i++)
    {
        
        std::cout<<"{";
        for(int j = 0; j < 3; j++)
        {
            std::cout << transform.at<double>(i, j) << ",";
        }
        std::cout<<"},"<< std::endl;
    }    
    std::cout<<"};"<< std::endl;
}
int main(int argc, char const *argv[])
{
    //test_multi_points();
    test_4_points();
    return 0;
}
