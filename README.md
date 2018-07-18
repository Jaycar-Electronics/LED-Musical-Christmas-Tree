# LED musical christmas tree
_Project 00005_

One of the ideas that sprung to mind when we first got in the XC4380 LED Strip Module was that it would be great for displays like Christmas lights. With Christmas on the way, we’ve turned them into a miniature Christmas tree complete with music playing from an SD card. Add a little bit of Christmas to your desk or workbench! Some soldering needed.

## Bill of Materials
| Qty | Code | Description |
| --- | --- | ---|
|1 | [XC4410](http://jaycar.com.au/p/XC4410) | UNO main board
|1 | [XC4536](http://jaycar.com.au/p/XC4536) | Data logging shield
|3 | [XC4380](http://jaycar.com.au/p/XC4380) | LED strip module
|1 | [AB3440](http://jaycar.com.au/p/AB3440) | Piezo transducer
|1 | [XC4983](http://jaycar.com.au/p/XC4983) | 8GB Micro SD card

## Connection Table

| Shield | LED strip 1 | LED strip 2 | LED strip 3 | Piezo buzzer |
| ---|--- |--- |--- |--- |
|5V | VDC | VDC |VDC |  |
|GND |GND | GND | GND | BLACK
| D6 | DIN|| |  |
| | DOUT | DIN | | |
| | | DOUT | DIN | |
|D9| | | | RED|


## Downloads
* [Source code](../downloads/LED_Christmas_Tree_with_Music)
* [Christmas Sounds](../downloads/Christmas_Sounds.zip)

## Software Libraries
|Library | Author
| --- |--- |
| NeoPixel | AdaFruit |
| TMRpcm | TMRh20 |


## Assembly

Start by soldering the short piece of header strip to the input end of each LED strip. This is the end that has the
'DIN' marking.

![](../images/NPI00005a.png)

Solder the three modules onto the Datalogging Shield in a tree shape, but make sure the ends aren’t pushed tight together, as we have to make some connections at the top. We found it easiest to solder one pin, and make sure all three strips were where we wanted them before soldering everything in place rigidly.

![](../images/NPI00005b.png)

The position isn't critical, but if you follow what we've done, you'll be able to work out the wiring more easily. On the underside of the Datalogging Shield, run red and black wires for 5V (marked 4- 7VDC on the strips) and GND connections.

![](../images/NPI00005c.png)

Run a wire from D6 to the DIN pin on the strip closest to it, and also run some wire from the DOUT on one strip to the DIN on the next strip- all the DINs should be connected to something. There's no reason you can't drape the wire around the strips a bit to make it look more like tinsel on the tree.

![](../images/NPI00005d.png)

Finally take the Piezo Transducer, and solder the black wire to GND and the red wire to D9.



## Programming
Download the source code and extract into a new folder, open the .ino file in the Arduino IDE and press upload.

You can add more strips by connecting `DIN` to `DOUT` of the last strip and change this line of code:
```c
#define LEDCOUNT 24
```
The color definitions can be changed at the start of the sketch

```c
unsigned long colours[6]={ //only using half intensity so we don't overload USB power
pixels.Color(127,0,0), //red
pixels.Color(0,127,0), //green
pixels.Color(0,0,127), //blue
pixels.Color(127,127,0), //yellow
pixels.Color(127,0,127), //purple
pixels.Color(127,63,0) //orange
};
```

## Use

There won't be any music or sound, as the card will be empty. You will need to copy .wav format files (mp3's will not work as the Arduino does not have enough processing power to decode the mp3) in 8bit mono format, preferable at not more than 32kHz sample rate. We found the free download Audacity program was easy to use for this.

The Arduino will simply cycle through all the files in the root folder of the SD card, so make sure there aren't any other files there as the Arduino might try to play them.

## Future Improvements
