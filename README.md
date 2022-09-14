# alexa-aircooler
 Hacking an aircooler to be controlled by Alexa

 Waking up in the middle of the night to turn on the humidifier that is far away, is not cool. I had this cheaper Air cooler that I paid about 10 dolars, so I decided to integrate the main board with a spare ESP32 and it worked very well.

 ![Device](/miscs/device.JPG "Device")


 ## Material

 I recommend  for you to use a NodeMCU in the place, since is cheaper and will do the same.

 * [NodeMCU (ESP8266)](https://www.amazon.se/-/en/dp/B06Y1ZPNMS/ref=sr_1_9) or [ESP32](https://www.amazon.se/-/en/dp/B08LL7ZH2W/ref=sr_1_6)
 * [Day Air Cooler](https://www.pricerunner.dk/pl/453-5208957/Indeklima/DAY-Air-cooler-5W-Sammenlign-Priser) (You can find others similar to this one)
 * Soldering Iron
 * Cables
 * Heat shrink insulator
 * [Arduino IOT Cloud](https://create.arduino.cc/iot/things/)


## Assembling

### Circuit

Since I dont have the complete circuit of the Air cooler, I tried to place only the component that we need to interact with, the blue wires are for the water control, purple's fan control, grey power on and red/black for power supply to ESP. The yellows wires are the place where you need to connect in order to interact with the LEDs, so try ot use the places, the green wires are part of the common joint of the LEDs, do not use it.

![Circuit](/miscs/circuit.jpg "Circuit")

In this last pic you can see how mine got in the end, just a small tip: The power connector has a layer of protection, so it is hard to solder there, I need to scratch with a knife until get a proper connection, but got ugly as hell.

![Board](/miscs/Board.JPG "Board")

## IOT

for this project I use Arduino IOT Cloud in order to give a try, it is really simple and you can connect some devices for free, it's work really nice for this.
You will need to create a new Thing, feel free to choose any name.

![IOT](/miscs/iot.png "IOT")

 1 - So first you will need to setup your device, if you dont have any, setup a new one in **3rd Party device** > ESP32 > your_model. Be sure to save your device ID and the Secret key.

 2 - Configure your network, just place the Wi-Fi name, the password and your Secret Key.

 3 - Add variables.

 ### Variables

 In this part I decided to use 3 variables, for power On as switch, fan and water as a dimmed light, because you can controll the velocity with this one, since Arduino do not have a humidificator type.

 Follow this for yours:

| Name            | Type        |
|-----------------|-------------|
| FanLevel        | DimmedLight |
| WaterLevel      | DimmedLight |
| PowerHumidifier | Switch      |

With this, Arduino will generate the code for you, check in **Skecth**. If you want, select in **Open full editor** and just change the content of your main file with the alexa-aircooler.ino and upload to your device. If you prefer to use the local Arduino IDE, remember to fill the file **arduino_secrets.h** and the DEVICE_LOGIN_NAME in **thingProperties.h**.

## Alexa

With everything prepared, go to your Alexa app in your cellphone, in the end of Devices row you will find **Your Smart Home Skills**, select that > **Enable Smart Home Skills** > Arduino. Just setup your account and you should be ready to go.

## Tips

You can rename the variables inside Alexa to something more normal than "waterLevel" or "fanLevel".