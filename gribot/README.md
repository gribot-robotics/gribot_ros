# Gribot

Gribot is an **open source agricultural robot mower** that can cut grass in crops such as trees, grapes, etc. All software, modules, plans, models, with the exception of purchased elements, are freely available under LGPL.
Gribot is not only limited to agriculture: it can be used in every area where grass has to be periodically cut, such as 
roadsides, industrial areas, etc.

We are developping more that just a mower: we are creating a platform that can carry many tools: in a first step, we do focus on grass cutting.

# Project web site

The project web site is www.gribot.org.

# How to support us

There are several way to support our project.
* You can participate, just register via github of via <a href="https://gribot.org/i-would-like-to-participate/">Gribot</a> web site.
* You can fund our project in <a href="https://gribot.org/donations/support_us/">making a donation</a>  

In any case, do not hesitate to <a href="https://gribot.org/contact-us/">contact us</a> for any question or comment.

# Why gribot ?

We would like to build an open source, modular and cost effective robotic platform for agriculture in collaborative mode,
in order to reduce CO2 emissions of farmers, stop the use of toxic chemicals, simplify their live and optimize their production costs.

We want to accelerate the transition to sustainable development, which is why we distribute all the
plans and software of our robot under GNU General Public License (GPL), except for ready-made
items such as motors, GPS modules, LIDAR , etc. Which are under the manufacturer's license.

# Project status

At the time being, it is possible to start <a href="https://gribot.org/first-test-in-simulator/">playing</a> with the simulator based on gazebo.
It gives an idea of the eay Gribot should behave.
A mechanical model is being designed, but needs improvements. 

The master branch contains a working system. All development are made in dev branch (or other if necessary), and are merged into master only when they have been tested.

# Getting started 

Gribot has been moved to ROS melodic on Ubuntu 18.04.

To use Gribot software, you have to do the following:

1. Install a Ubuntu 18.04 server if not already done
2. Install ROS Melodic packages
3. Create a catking working folder
4. Clone gribot git folder

If everything went well, you should be able to start gribot in typing the following command:

```
roslaunch gribot gribot.launch
```

# Contribution

Thank you to all the people who already contributed to Gribot.

<a href="https://github.com/guycorbaz/gribot/graphs/contributors">Contributors</a>
