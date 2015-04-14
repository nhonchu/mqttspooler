MQTT-Spooler
============

This tool enables your device application to easily exchange data over MQTT with Sierra Wireless AirVantage server.

Coding is not require, Generic and Loosely coupled solution through CSV-based file interface:

* To send MQTT message to AirVantage, you just need to format your messages as CSV and save them to files. e.g. bedroom.temperature;20.2;

* Upon receiving MQTT data from AirVantage, this tools automatically converts incoming MQTT message to CSV files. e.g. bedroom.TurnOn.Hearter;true;14301456445

This tools could be used as a quick integration option (no need to deal with MQTT code and payload encoding/decoding) for your existing sensor/actuator based application.

MQTTspooler, written in C language, has been tested on RaspberryPI, PC/Ubuntu, MacOS, it can be easily adapted to other Linux-based system.

CSV Interface Format
--------------------
Key;Value;OptionalTimestamp
<dd>*where OptionalTimestamp is the number of elapsed seconds since Jan 1st 1970*.<br>
<dd>*if OptionalTimestamp is ommited then MQTTspooler will provide the current timestamp.*

Use Case Example
----------------
Your device aggregates data from various sensors, and save the collected data to one or several CSV file(s), for instance:<br>
bedroom.temperature;17;<br>
bedroom.luminosity;2500;<br>
livingroom.temperature;20;<br>
kitchen.temperature;21;<br>
kitchen.humidity;60;<br>

MQTTspooler will automatically detect your CSV files, parse them, convert CSV entries to JSON format prior publishing them to AirVantage server.
Posted data can then be visualized on Sierra Wireless AirVantage web portal or collected by your server through WebAPI. Refer to doc.airvantage.net for further information.
<br>
<br>
You can have AirVantage server to send data, over MQTT, to your device application. e.g. perform remote actions on your actuators.
MQTTspooler, running on your device system, will automatically convert incoming MQTT data (JSON formatted) to CSV files, for instance:<br>
bedroom.TurnOn.Heater;true;14301456445<br>
bedroom.TurnOn.Light;true;14301456445<br>
kitchen.TurnOn.Heater;false;14301456445<br>
kitchen.TurnOn.Fan;2;14301456445<br>

Your device application just needs to parse CSV files to extract trigger commands or apply particular setting.
 
Prerequisite
------------
Before your device application can exchange MQTT data with Sierra Wireless AirVantage server, the following must be performed:<br>
1. Have an account on [AirVantage server](https://eu.airvantage.net/) and apply the following steps.<br>
2. Register your system/device, refer to [How-To](), *Getting started with HL Module*, step 1.<br>
    * If you don't have IMEI (e.g. not using 2G/3G/4G module), provide a serial number when creating a gateway.
3. Create the counterpart server-side application on AirVantage, refer to [How-To](), *Getting started with HL Module*, step 2.
    * A sample application model is provided in appModel directory.
    * If serial number is used, change the *protocol comm-id* from IMEI to SERIAL, in the XML application model.
4. Associate the server-side application to your device and assign a password. refer to [How-To](), *Getting started with HL Module*, step 2.<br>
5. Your device/system must have an internet access (e.g. cellular, WiFi, ethernet...) with port 1883 not being blocked.<br>

Build
-----
Just use the Makefile:
*make*

to build MQTTspooler executable.

Run
---
Launching MQTTspooler requires 4 mandatory arguments and 1 optional argument, as follow:
~~~
./mqttspooler imei password pubFolderName subFolderName pubPeriod
~~~

Arguments:
* imei:				the IMEI or Serial Number as provided in Prerequisite step 2.
* password: 		the password as provided in Prerequisite step 3.
* pubFolderName:	an existing directory in which MQTTspooler will be scanning for CSV files to be published to AirVantage server.
* subFolderName:	an existing directory in which MQTTspooler will be dumping CSV files upon receiving incoming MQTT messages from AirVantage server.
* pubPeriod:		optional argument in number of seconds. Spooling frequency of the pubFolder, default is 30 seconds.


Testing
-------
Once the MQTTspooler has been launched as shown above, you may simply test message publishing as follow (e.g. in a separate console)
~~~
cd pubFolderName
echo "bedroom.temperature;17;" >> sensor.txt
~~~

To test the incoming MQTT messages, refer to [How-To](), *Getting started with HL Module*, step 3, to send message from AirVantage server.
Once MQTT messages are received, simply check for them as follow:
~~~
cd ../subFolderName
more data-*xxx*.txt
~~~
