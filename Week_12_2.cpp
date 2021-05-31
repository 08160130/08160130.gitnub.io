#include <GL/glut.h>
#include <stdio.h>
#include <opencv/highgui.h>   ///使用 OpenCV 2.1( 比較簡單 )
#include <opencv/cv.h>
#include<windows.h>

int myTexture(char *fliename)   ///設定貼上鋼彈圖片
{
    IplImage * img = cvLoadImage("fliename");    ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB);    ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D);    ///1. 開啟貼圖功能
    GLuint id;     ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id);    /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id);  ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);   /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

void display( )
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glutSolidTeapot(0.3);
     glutSwapBuffers( );
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, -5.0f, 0.0f };

const GLfloat mat_ambient[ ]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[ ]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[ ]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[ ] = { 100.0f };

int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week12_08160130");

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    myTexture("Diffuse.jpg");   ///鋼彈圖片貼上

    glutMainLoop( );
}