#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>

#include <chrono>
#include <iostream>

#define FPS(start) (CLOCKS_PER_SEC / (clock()-start))


//class for taking capturing screen
class ScreenShot
{
    Display* display;
    Window root;
    int x,y,width,height;
    XImage* img{nullptr};
public:
    ScreenShot(int x, int y, int width, int height):
        x(x),
        y(y),
        width(width),
        height(height)
    {
        display = XOpenDisplay(nullptr);
        root = DefaultRootWindow(display);
    }

    void operator() (cv::Mat& cvImg)
    {
        if(img != nullptr)
            XDestroyImage(img);
        img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
        cvImg = cv::Mat(height, width, CV_8UC4, img->data);
    }

    ~ScreenShot()
    {
        if(img != nullptr)
            XDestroyImage(img);
        XCloseDisplay(display);
    }
};

int main(int argc, char* argv[])
{
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <width> <height>\n";
        return -1;
    }

    int width  = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);

    ScreenShot screen(0, 0, width, height);
    
    cv::Mat img;


    std::string str_fps;
    //used for calculating fps
    using clock = std::chrono::high_resolution_clock;
    auto last = clock::now();

    while(true) 
    {
        auto now = clock::now();
        double fps = 1.0 / std::chrono::duration<double>(now - last).count();
        str_fps = std::to_string(fps);
        last = now;
        
        screen(img);

        //textSize for putting fps in corner
        int baseline = 0;
        cv::Size textSize = cv::getTextSize(str_fps, cv::FONT_HERSHEY_SIMPLEX, 1.0, 2, &baseline);

        cv::putText(img,
            str_fps,
            cv::Point(img.cols - 10 - textSize.width, 30), 
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            CV_RGB(118, 185, 0), //font color
            2);

        std::cout<< str_fps << '\n';
        cv::imshow("img", img);
        char k = cv::waitKey(1);
        if (k == 'q')
            break;
    }
}
