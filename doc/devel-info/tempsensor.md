# Temp Sensor 

## Name - Tech - etc

Name: Wi-Fi Temperature & Humidity Sensor 
Brand: Tuya 
Chip: LMIC LM8005 A787389

## Watch Port

cmd:  nmap -v -A 192.168.2.204

```bash
nmap -v -A 192.168.2.204
Scanning 192.168.2.204 [2 ports]
Completed Ping Scan at 18:41, 0.10s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 18:41
Completed Parallel DNS resolution of 1 host. at 18:41, 0.00s elapsed
Initiating Connect Scan at 18:41
Scanning 192.168.2.204 [1000 ports]
Discovered open port 6668/tcp on 192.168.2.204
Completed Connect Scan at 18:41, 8.40s elapsed (1000 total ports)
Initiating Service scan at 18:41
Scanning 1 service on 192.168.2.204
Completed Service scan at 18:44, 169.64s elapsed (1 service on 1 host)
NSE: Script scanning 192.168.2.204.
Initiating NSE at 18:44
Completed NSE at 18:44, 14.17s elapsed
Initiating NSE at 18:44
Completed NSE at 18:44, 1.09s elapsed
Initiating NSE at 18:44
Completed NSE at 18:44, 0.00s elapsed
Nmap scan report for 192.168.2.204

Not shown: 999 closed ports
PORT     STATE SERVICE VERSION
6668/tcp open  irc?
|_irc-info: Unable to open connection
``` 


## Using API 

[Links API Discription](https://github.com/tuya/tuya-home-assistant/blob/main/docs/platform_configuration.md)

[Tuya Plattform](https://eu.iot.tuya.com/)

### Good to know 

App for Device: Smart Life 

User-Account: Germany 

Data-Center: Central Europe 

Add Projects with only the right data center and set our account to the right one. Without this setting you cant get the device in the IoT Platform. 