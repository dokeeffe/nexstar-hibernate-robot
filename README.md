# nexstar-hibernate-robot

An arduino robot to hibernate/wake/power-on/power-off a celestron telescope to enable remote operation using indi or ascom.
It is possible to hibernate the telescope by using 3 buttons on the keypad (enter,menu and up). The robot uses 2 servos over these buttons to hibernate and wake the telescope. The robot also controls the 12v supply to the scope using a relay.

See https://github.com/dokeeffe/nexstar-hibernate-robot/wiki/Building-the-hardware for more details

![pic](http://s10.postimg.org/besys9rxl/Screen_Shot_2015_10_09_at_22_05_09.png)

![pic](https://lh3.googleusercontent.com/-8SMeUvQ9cJA/Vhtz3U-KskI/AAAAAAAAHO0/52kvWx4vo4I/s512-Ic42/20151011_220414.jpg)

Celestron have not published the serial commands to hibernate/wake the nexstar telescopes which makes this robot necessary for fully remote operation.
