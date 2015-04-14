<?xml version="1.0" encoding="ISO-8859-1"?>
<app:application 
        xmlns:app="http://www.sierrawireless.com/airvantage/application/1.0" 
        type="com.test.airvantage.mqtt.spooler" 
        name="MQTT Spooler Sample"
        revision="0.0.1">
  <capabilities>
    <communication>
      <protocol comm-id="IMEI" type="MQTT" />
    </communication>
    <data>
      <encoding type="MQTT">
        <asset default-label="Bedroom" id="bedroom">
          <variable default-label="Bedroom Temperature" path="temperature" type="double"/>
          <variable default-label="Bedroom Luminosity" path="luminosity" type="double"/>
          <command path="TurnOn" default-label="Bedroom Turn on">
            <parameter id="Light" default-label="light" type="boolean" />
            <parameter id="Heater" default-label="heater" type="boolean" />
          </command>
        </asset>
        <asset default-label="Kitchen" id="kitchen">
          <variable default-label="Kitchen Humidity" path="humidity" type="double"/>
          <variable default-label="Kitchen Temperature" path="temperature" type="double"/>
          <command path="TurnOn" default-label="Kitchen Turn on">
            <parameter id="Light" default-label="light" type="boolean" />
          </command>
          <command path="Set" default-label="Kitchen Set">
            <parameter id="FanSpeed" default-label="FanSpeed" type="double" />
          </command>
        </asset>
        <asset default-label="Livingroom" id="livingroom">
          <variable default-label="Livingroom Temperature" path="temperature" type="int"/>
        </asset>
      </encoding>
    </data>
  </capabilities>
</app:application>