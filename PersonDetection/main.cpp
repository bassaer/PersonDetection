#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

Mat detectHumanInImage(Mat &image,string &cascade_file){
    CascadeClassifier cascade;
    cascade.load(cascade_file);
    
    vector<Rect> humans;
    //cascade.detectMultiScale(image, humans, 1.1,3,0,Size(20,20));
    
    printf("size = %lu",humans.size());
    
    for (int i = 0; i< humans.size(); i++){
        rectangle(image,Point(humans[i].x,humans[i].y),Point(humans[i].x + humans[i].width,humans[i].y + humans[i].height),Scalar(0.0,200),3,CV_AA);
        
    }
    return image;
    
}

Mat detectHumanInImage(Mat &image,CascadeClassifier cascade){
    vector<Rect> humans;
    cascade.detectMultiScale(image, humans,1.1,2);
    for (int i = 0; i< humans.size(); i++){
        rectangle(image,Point(humans[i].x,humans[i].y),Point(humans[i].x + humans[i].width,humans[i].y + humans[i].height),Scalar(200.0,100),3,CV_AA);
        
    }
    return image;
}

void detectHumanInVideo(){
    VideoCapture video("/Users/user/Pictures/OpenCV/sample.mp4");
    video.set(CV_CAP_PROP_FPS, 30.0);
    CascadeClassifier cascade;
    String path0 = "/usr/local/Cellar/opencv/2.4.12/share/OpenCV/haarcascades/haarcascade_fullbody.xml";
    String path1 = "/usr/local/Cellar/opencv/2.4.12/share/OpenCV/haarcascades/cascade.xml";
    cascade.load(path0);
    
    while(1) {
        Mat frame;
        video >> frame;
        if(frame.empty() || waitKey(30) >=0 || video.get(CV_CAP_PROP_POS_AVI_RATIO)==1){
            break;
        }
        frame = detectHumanInImage(frame,cascade);
        imshow("Human Detection",frame);
    }
}


int main(void){
    detectHumanInVideo();
}