Balancing robot
============

This self balancing robot built from Lego is controlled by Microsoft Windows 8.1 running on the Galileo prototyping board.

[<img src="_img/robot.jpg?raw=true" alt="Balancing robot" width="480" height="640"/>]

## Parts list ##
- [Intel Galileo](http://en.wikipedia.org/wiki/Intel_Galileo) board
- 2 [LEGO XL motors](http://shop.lego.com/en-US/LEGO-Power-Functions-XL-Motor-8882) (other 9V motors should be also Ok)
- DFRduino [L298P motor shield](http://www.dfrobot.com/index.php?route=product/product&product_id=69)
- DC-DC step down converter (I use one based on LM2596 IC)
- [Sparkfun IMU Fusion board](https://www.sparkfun.com/products/10252) (3D accelerometer, 3D gyroscope)
- 8.4 V battery (any battery 7.4 V - 9 V that can power two motors should be Ok)

## Motors ##
Any 9V DC motors should be Ok. I used ones from Lego because they are perfectly suited to rapid prototyping. 
[<img src="_img/motors.jpg?raw=true" alt="Motors" width="640" height="480"/>]

##Power circuit##
The battery provides about 8.4 volts, the exact voltage varies depending on load. The Galileo board needs a stabilized 5V current supply over 5.6 mm jack. I took DC-DC step down converter based on LM2596 chip.

Motors are controlled by the Arduino motor shield that gets the power directly from the battery. 
[<img src="_img/power.jpg?raw=true" alt="Power circuits" width="640" height="480"/>]
