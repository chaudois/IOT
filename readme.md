# Memory LightCube


Memory LightCube is a DIY Project realised during a lecture at ESGI school, on the subject of IoT (Internet of things). It was made by 3 students : Tristan Chuine, Romain Bignon and Damien Chaudois

### what does it do ?!?
The Memory LightCube is a memory game wich requires you to find all sequences of 3 led of the same color. you have 6 face of 4 leds each, for a total of 8 different colors ! once you find all triplets, you can get all the best score based on the time it took the player to finish the cube.

### Requirements
for this project, you'r going to need 2 things : a working brain and a bunch of tools. let's get around them

- at least one soldering iron and weld seam
- two kind of pincers : one to grab things like wires, and one to denude or cut them
- a voltmeter
- 3 meters of 4mm copper wire
- 24 push button (as opposed to switch button)
- 24 RGB led
- a glue gun
- a plate of sturdy yet easy to manipulate material, such as semi-hard plastic or cardboard
- an arduino card, with at least 13 pin, including at 4 input, analog or not. we will be using te arduino micro, in adition with an arduino wemo
- the Arduino IDE  [downloadable here](https://www.arduino.cc/en/Main/Software)
- the code available in this repository
- knowledge in c++ will help but is not necessary

### load the code into the card
first thing to do, is to make sure you get the code up and running. clone the content of this repository, and open the content of the sketch_nano folder in arduino IDE. 
go to the menu tools=>manage libraries. you need to install the following dependancies :
- arduinoSTL
- FastLED
- arduinoOSC

once installed, hit the top left button "verify" to make sure all dependencies are here.
go to the menu tools=>board and select the arduino micro
go to tools=>port and select the only COM chanel that should apear here
you can now hit "upload" next to verify to transfert the code to the card. 
## Crafting
the goal is to create a matrix of button, which will allow you to pin point wich button has been pressed in the said matrix. the wiring is as follow
![wiring](/img/Wireing_structure.png)
the leds are, however, wired serialy.  this way, we only need one wire to connect all our leds to the card! aditionaly, they have a built in adress system that allow us light one a time in particular.
each button is connected to 2 sides of your card : all button of each faces are connected together, and each number, from 1 to 4 are connected together.
first, cut 6 squares of around 5 cm each in your cardboard/plastic
glue 4 button on each square
![result1](/img/DSC_0324.JPG)
wield them together so it may look like this : 
![result2](/img/DSC_0319.JPG)
create a second network of wire on the back to wire all the 1's, the 2's and so one together
![result3](/img/DSC_0320.JPG)
glue one led on each button.*BE CARFEFUL* leds are one way components and needs  to be aranged to allow a serial wielding ! make sure you keep track of wich face has wich leds : face 1 got leds 1,2,3 and 4, face 2 got leds 5,6,7 and 8, and so on. connect each led following the logic gnd on gnd, 5v on 5v, and D0 on D_in as follow
![result4](/img/DSC_0012.JPG)
repeat for each face, then wield each face together, always following the led serial direction
![result5](/img/DSC_0360.JPG)
you now need to collect all ends of each faces, and all end of each numbers, and put them together on a plastic dongle
![result6](/img/DSC_0013.JPG)
you now need to connect the dongle that carry 6 wires (one for each face) to the pin of your card, from A0 to A5.
connect the dongle with 4 wires (one for each number) from D2 to D5
connect the card to a power source (either your computer, an extarna battery, or a mural plug)
you now have a functional Memory CubeLight ! you can custom all the extarnal layout, by sloting it into a plastic cube, or anything that let the light of the led pass!