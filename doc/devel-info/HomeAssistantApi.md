# Home Assisstant API

## How-To

[HELP](https://developers.home-assistant.io/docs/api/rest/)

Generate a Long life token (node: the key ist 182 sign long)

Ad to configuration.yml

```yml

api:

```

Check with curl

```bash
curl -X GET -H "Authorization: Bearer xyz"   http://192.168.2.xxx:8123/api/
```

If this answer is the folling, that good 

```json
{"message":"API running."}
```

More get the entity_id test: 

```bash
curl -X GET -H "Authorization: Bearer xyz"   http://192.168.2.165:8123/api/states/sensor.tempbad_temperature
```

Update some entity State hear the bad per POST

```bash
curl -X POST -H "Authorization: Bearer xyz -H "Content-Type: application/json" -d '{"entity_id":"input_boolean.heater_bad","state":"on","attributes":{"editable":false,"icon":"mdi:radiator","friendly_name":"Bad Heizung an"}}' http://192.168.2.165:8123/api/states/input_boolean.heater_bad
{"entity_id":"input_boolean.heater_bad","state":"on","attributes":{"editable":false,"icon":"mdi:radiator","friendly_name":"Bad Heizung an"},"last_changed":"2022-12-31T14:00:56.842133+00:00","last_updated":"2022-12-31T14:00:56.842133+00:00","context":{"id":"01GNM7RN8A8ETFFX0ZVZY0DX2Q","parent_id":null,"user_id":"e05c526b42fb4xxxxx"}}
```

Some Home Assistant Climate

[LINK](https://www.home-assistant.io/integrations/#climate)

Thermostat with all cool time function:

https://www.home-assistant.io/integrations/generic_thermostat/

### SmartFloorHeating Thermostat

Example

```yml
# active rest api
api:

# sfh switches 
input_boolean:
  wohnzimmer:
    name: Wohnzimmer Heizung an
    icon: mdi:radiator
  schlafzimmer:
    name: Schalfzimmer Heizung an
    icon: mdi:radiator
  kueche:
    name: Kueche Heizung an
    icon: mdi:radiator
  heater_kind1:
    name: Ankleidezimmer Heizung an
    icon: mdi:radiator
  heater_bad:
    name: Bad Heizung an
    icon: mdi:radiator

# sfh_1
climate:
  - platform: generic_thermostat
    name: Wohnzimmer
    unique_id: thermostat_wohnzimmer
    heater: input_boolean.wohnzimmer
    target_sensor: sensor.tempwohnzimmer_temperature
    min_temp: 19
    max_temp: 21
    target_temp: 20
    ac_mode: false

# sfh_2
  - platform: generic_thermostat
    name: Schalfzimmer
    unique_id: thermostat_schlafzimmer
    heater: input_boolean.schlafzimmer
    target_sensor: sensor.tempschlafzimmer_temperature
    min_temp: 16
    max_temp: 19
    target_temp: 18
    ac_mode: false

# sfh_3
  - platform: generic_thermostat
    name: Kueche
    unique_id: thermostat_keuche
    heater: input_boolean.kueche
    target_sensor: sensor.tempkueche_temperature
    min_temp: 19
    max_temp: 21
    target_temp: 19.5
    ac_mode: false

# sfh_4
  - platform: generic_thermostat
    name: Ankleidezimmer
    unique_id: thermostat_kind1
    heater: input_boolean.heater_kind1
    target_sensor: sensor.tempkind1_temperature
    min_temp: 18
    max_temp: 22
    target_temp: 20
    ac_mode: false

# sfh_5
  - platform: generic_thermostat
    name: Bad
    unique_id: thermostat_bad
    heater: input_boolean.heater_bad
    target_sensor: sensor.tempbad_temperature
    target_temp: 20.5
    min_temp: 18
    max_temp: 23
    ac_mode: false

```

Send some state to HA api

```bash
curl -X POST -H "Authorization: Bearer eyJhbGciOiWPoU" -H "Content-Type: application/json" -d '{"entity_id":"input_boolean.heater_bad","state":"on"}' http://192.168.2.165:8123/api/states/input_boolean.heater_bad
```
