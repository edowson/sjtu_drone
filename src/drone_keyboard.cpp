#include "drone_object_ros.h"
#include <iostream>
#include <QtWidgets>


class KeyboardWnd:public QWidget{
public:
    DroneObjectROS* ardrone;
    KeyboardWnd(){
        ardrone = 0;
        setFocusPolicy(Qt::StrongFocus);
    }
    void setARDrone(DroneObjectROS& drone){
        ardrone = &drone;
    }

    void keyPressEvent(QKeyEvent *event){
        if(!ardrone)
            return ;
        char key = event->key();
        std::cout << "key:" << key << std::endl;
        switch(key){
        case 'Z':
            //take off
            ardrone->takeOff();
            break;
        case 'X':
            //land
            ardrone->land();
            break;
        case 'H':
            ardrone->hover();
            break;
        case 'I':
            //going up
            ardrone->rise(0.4f);
            break;
        case 'K':
            //going down
            ardrone->rise(-0.4f);
            break;
        case 'J':
            //turn left
            ardrone->yaw(-0.4f);
            break;
        case 'L':
            //turn right
            ardrone->yaw(0.4f);
            break;
        case 'A':
            //tilt left
            ardrone->roll(-0.1f);
            break;
        case 'D':
            //tilt right
            ardrone->roll(0.1f);
            break;
        case 'W':
            //title front
            ardrone->pitch(0.1f);
            break;
        case 'S':
            ardrone->pitch(-0.1f);
            break;
            
        case 'T':
            testPositionControl();
            break;
           
        default:
            //break;
            if(!ardrone->isPosctrl)
                ardrone->hover();
        }
        event->accept();
    }
    
    virtual void keyReleaseEvent(QKeyEvent *event){
        if(!ardrone)
            return ;
        char key = event->key();
        if (!event->isAutoRepeat()){
            std::cout << "key:" << key << "is released !" << std::endl;
            if( !ardrone->isPosctrl)
                ardrone->hover();
            event->accept();
        }else{
            event->ignore();
        }
    }
    
    void testPositionControl(){
        if(ardrone->isPosctrl){
            ardrone->posCtrl(false);
            std::cout << "position control off!" << std::endl;
        }
        else{
            ardrone->posCtrl(true);
            std::cout << "(0.5,-1.5,6)" << std::endl;
            ardrone->moveTo(0.5,-1.5,2);
            sleep(5);
            ardrone->moveTo(0.5,1.5,2);
            sleep(5);
            ardrone->moveTo(-3,1.5,2);
            sleep(5);
            ardrone->moveTo(-3,-1.5,2);
            sleep(5);
            ardrone->moveTo(0.5,-1.5,2);
            sleep(5);

        }
    }    
};


int main(int argc, char** argv){
    ros::init(argc, argv, "ardrone_keyboard");
     
    QApplication app(argc, argv);
    
    ros::NodeHandle node;
    DroneObjectROS ardrone(node);
  
    KeyboardWnd keyWnd;
    keyWnd.resize(QSize(200,200));    
    keyWnd.setARDrone(ardrone);    
    keyWnd.show();
  
    return app.exec();
}
