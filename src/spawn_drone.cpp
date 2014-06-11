#include <iostream>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>

int main(int _argc, char** _argv){
    gazebo::setupClient(_argc, _argv);
    gazebo::transport::NodePtr node(new gazebo::transport::Node());
    node->Init();
    
    // Create a publisher on the ~/factory topic
     gazebo::transport::PublisherPtr factoryPub =
     node->Advertise<gazebo::msgs::Factory>("~/factory");
    
     // Wait for a subscriber to connect
     factoryPub->WaitForConnection();
     
     // Create the message
     gazebo::msgs::Factory msg;
         
     msg.set_sdf_filename("model://sjtu_drone");
    
    // Pose to initialize the model to
    gazebo::msgs::Set(msg.mutable_pose(),
               gazebo::math::Pose(gazebo::math::Vector3(0, 0, 1), 
               gazebo::math::Quaternion(0, 0, 0)));
    
     
    // Send the message
    factoryPub->Publish(msg);    
}
