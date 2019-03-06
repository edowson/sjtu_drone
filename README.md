# Overview

sjtu_drone is a quadrotor simulation program forked from ['tum_simulator'] (http://wiki.ros.org/tum_simulator), developed using ROS + Gazebo.

It is used for testing visual SLAM algorithms with different sensors, such as IMU, sonar range finder and laser range finder. 

The acronym 'sjtu' stands for Shanghai Jiao Tong University. This package has been used in the past for testing algorithms for the [UAV contest at SJTU](http://mediasoc.sjtu.edu.cn/wordpress)

## Requirements

The package requires ROS Kinetic version.

This implies that you will have to use Ubuntu-16.04. The recommended Gazebo version is 7.


## Download and Compiling

```
$cd <catkin_ws>/src
$git clone https://github.com/edowson/sjtu_drone.git
$cd <catkin_ws>
$catkin_make -j4
```

Here <catkin_ws> is the path of the catkin work space. Please refer to the [tutorial](http://wiki.ros.org/ROS/Tutorials) about how to create a catkin work space in ROS.

## Run

The simplest way is calling
```
$cd <where you check out the code>
$export ROS_PACKAGE_PATH=`pwd`:$ROS_PACKAGE_PATH
$roslaunch sjtu_drone start.launch
```
or by running the different parts of the package, step by step

```
$cd <where you check out the code>
$export ROS_PACKAGE_PATH=`pwd`:$ROS_PACKAGE_PATH
$roscore #to start the ROS server
$rosrun sjtu_drone start_gzserver <world file> #run the gazebo server and loading the world file
$rosrun sjtu_drone start_gui #run the gazebo client
$rosrun sjtu_drone spawn_model # generate a quadrotor in the scene
$rosrun sjtu_drone drone_keyboard # run the keyboard controller to control the quadrotor
```

## Read sensor data from ROS topics
```
forward looking camera : /drone/front_camera/image_raw
downward looking camera: /drone/down_camera/image_raw
sonar data: /drone/sonar
laser range data: /drone/laser
```
