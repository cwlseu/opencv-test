#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/// Global variables
const char* source_window = "Source image";
const char* warp_window = "Warp";
const char* warp_rotate_window = "Warp + Rotate";

/** @function main */
int main( int argc, char** argv )
{
    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat rot_mat(2, 3, CV_32FC1 );
    Mat warp_mat(2, 3, CV_32FC1 );
    Mat src, warp_dst, warp_rotate_dst;

    /// Load the image
    src = cv::imread("../res/face_01.jpg"); 

    /// Set the dst image the same type and size as src
    warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

    /// Set your 3 points to calculate the  Affine Transform
    srcTri[0] = Point2f( 0,0 );
    srcTri[1] = Point2f( src.cols, 0 );
    srcTri[2] = Point2f( 0, src.rows);

    dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
    dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
    dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );

    /// Get the Affine Transform
    warp_mat = getAffineTransform( srcTri, dstTri );

    /// Apply the Affine Transform just found to the src image
    warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

    /** Rotating the image after Warp */
    /// Compute a rotation matrix with respect to the center of the image
    Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
    double angle = -50.0;
    double scale = 1;
    /// Get the rotation matrix with the specifications above
    rot_mat = getRotationMatrix2D( center, angle, scale );
    /// Rotate the warped image
    warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );
    /// Show what you got
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );
    cv::imwrite("src.jpg", src); 
    // namedWindow( warp_window, CV_WINDOW_AUTOSIZE );
    // imshow( warp_window, warp_dst );
    cv::imwrite("warp_affine.jpg", warp_dst); 
    // namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
    // imshow( warp_rotate_window, warp_rotate_dst );
    cv::imwrite("warp_affine_rotate.jpg", warp_rotate_dst); 

    std::cout << "{";
    for(int i = 0; i < 3; i++)
        std::cout << "{" << srcTri[i].x <<","<< srcTri[i].y <<"},";
    std::cout << "}" << std::endl;
    std::cout << std::endl;

    std::cout << "{";
    for(int i = 0; i < 3; i++)
        std::cout << "{" << dstTri[i].x <<","<< dstTri[i].y <<"},";
    std::cout << "};" << std::endl;
    std::cout << std::endl;
    
    std::cout<<"{";
    for(int i = 0; i < 2; i++)
    {
        std::cout<<"{";
        for(int j = 0; j < 3; j++)
        {
            std::cout << warp_mat.at<double>(i, j) << ",";
        }
        std::cout<<"},"<< std::endl;
    }    
    std::cout<<"};"<< std::endl;
    return 0;
}

void test_4_points()
{  
    Mat img = cv::imread("face_01.jpg");  








    int img_height = img.rows;  
    int img_width = img.cols;  
    
    std::vector<Point2f> corners, corners_trans;
    corners.push_back(Point2f(2, 3));
    corners.push_back(Point2f(3, 1));
    corners.push_back(Point2f(1, 4));

    corners_trans.push_back(Point2f(3, 3));
    corners_trans.push_back(Point2f(7, 4));
    corners_trans.push_back(Point2f(5, 6));

    float _T[3][3], T[3][3] = {
        { -8, -6, 37 },
        { -7, -4, 29 },
        { 0, 0, 1 }
    };
    Mat transform = cv::getAffineTransform(corners, corners_trans);  
    
    // vector<Point2f> ponits, points_trans;
    // for(int i=0;i<img_height;i++){  
    //     for(int j=0;j<img_width;j++){  
    //         ponits.push_back(Point2f(j,i));  
    //     }  
    // }  

    // Mat img_trans = Mat::zeros(img_height,img_width,CV_8UC3);  
    // cv::Size dst_sz = img.size();

    // cv::warpAffine(ponits, points_trans, transform, dst_sz);

    // int count = 0;  
    // for(int i=0;i<img_height;i++){  
    //     uchar* p = img.ptr<uchar>(i);  
    //     for(int j=0;j<img_width;j++){  
    //         int y = points_trans[count].y;  
    //         int x = points_trans[count].x;  
    //         uchar* t = img_trans.ptr<uchar>(y);  
    //         t[x*3]  = p[j*3];  
    //         t[x*3+1]  = p[j*3+1];  
    //         t[x*3+2]  = p[j*3+2];  
    //         count++;  
    //     }  
    // }  
    // cv::imwrite("face01_trans.png", img_trans); 
    
   
}
