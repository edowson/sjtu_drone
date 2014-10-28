#include "drone_object_ros.h"
#include <iostream>
#include <QtWidgets>


class KeyboardWnd:public QWidget{
public:
    DroneObjectROS* drone;
    KeyboardWnd(){
        drone = 0;
        setFocusPolicy(Qt::StrongFocus);
    }
    void setdrone(DroneObjectROS& drone){
        this->drone = &drone;
    }

    void keyPressEvent(QKeyEvent *event){
        if(!drone)
            return ;
        char key = event->key();
        std::cout << "key:" << key << std::endl;
        switch(key){
        case 'Z':
            //take off
            drone->takeOff();
            break;
        case 'X':
            //land
            drone->land();
            break;
        case 'H':
            drone->hover();
            break;
        case 'I':
            //going up
            drone->rise(0.4f);
            break;
        case 'K':
            //going down
            drone->rise(-0.4f);
            break;
        case 'J':
            //turn left
            drone->yaw(-0.4f);
            break;
        case 'L':
            //turn right
            drone->yaw(0.4f);
            break;
        case 'A':
            //tilt left
            if( !drone->isVelMode)
                drone->roll(-0.1f);
            else
                drone->pitch(0.7f);
            
            break;
        case 'D':
            //tilt right
            if( !drone->isVelMode)
                drone->roll(0.1f);
            else
                drone->pitch(-0.7f);
            break;
        case 'W':
            //title front
            if( !drone->isVelMode)
                drone->pitch(0.1f);
            else
                drone->roll(0.7f);
            break;
        case 'S':
            if( !drone->isVelMode)
                drone->pitch(-0.1f);
            else
                drone->roll(-0.7f);
            break;
       
        case 'M':
            drone->velMode(!drone->isVelMode);
            break;
            
        case 'T':
            testPositionControl();
            break;
           
        default:
            //break;
            if(!drone->isPosctrl)
                drone->hover();
        }
        event->accept();
    }
    
    virtual void keyReleaseEvent(QKeyEvent *event){
        if(!drone)
            return ;
        char key = event->key();
        if (!event->isAutoRepeat()){
            std::cout << "key:" << key << "is released !" << std::endl;
            if( !drone->isPosctrl)
                drone->hover();
            event->accept();
        }else{
            event->ignore();
        }
    }
    
    void testPositionControl(){
        if(drone->isPosctrl){
            drone->posCtrl(false);
            std::cout << "position control off!" << std::endl;
        }
        else{
            drone->posCtrl(true);
            std::cout << "(0.5,-1.5,6)" << std::endl;
            drone->moveTo(0.5,-1.5,2);
            sleep(5);
            drone->moveTo(0.5,1.5,2);
            sleep(5);
            drone->moveTo(-3,1.5,2);
            sleep(5);
            drone->moveTo(-3,-1.5,2);
            sleep(5);
            drone->moveTo(0.5,-1.5,2);
            sleep(5);

        }
    }    
};


int main(int argc, char** argv){
    ros::init(argc, argv, "drone_keyboard");
     
    QApplication app(argc, argv);
    
    ros::NodeHandle node;
    DroneObjectROS drone(node);
  
    KeyboardWnd keyWnd;
    keyWnd.resize(QSize(200,200));    
    keyWnd.setdrone(drone);    
    keyWnd.show();
  
    return app.exec();
}
