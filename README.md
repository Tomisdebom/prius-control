# Prius control

The following guide takes you through the installation and usage of the arrow-key-controlled prius program.

## Installation

Open your terminal and execute the following steps:

```bash
source /opt/ros/kinetic/setup.bash
cd ~
mkdir -p catkin_ws/src
cd catkin_ws/src
catkin init_workspace
git clone git@gitlab.me41025.3me.tudelft.nl:students-1920/lab3/group61.git
git clone git@gitlab.me41025.3me.tudelft.nl:students-1920/me41025 simulator.git
cd ..
catkin_make
source devel/setup.bash
```

## Usage

For controlling the Prius with the arrow keys type:
```ros
roslaunch simple_control simple_control.launch
```
For recording your path type:
```ros
roslaunch simple_control record.launch
```
For playing your recorded path type:
```ros
roslaunch simple_control play.launch
```

## License
Tom Kerssemakers \
Binnert Prins
