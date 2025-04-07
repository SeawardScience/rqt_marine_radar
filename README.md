# Marine Radar Plugin for rqt

Allows viewing of marine radar data as well as controlling supported hardware.

## Installation

Clone this repo into your workspace: 

```git clone git@github.com:CCOMJHC/rqt_marine_radar.git```

### Dependencies

Install package dependencies for your ROS2 distribution:

```sudo apt install ros-<distro>-marine-sensor-msgs```

Alternatively, you can use the development package here: https://github.com/apl-ocean-engineering/marine_msgs

Clone the `marine_radar_control_msgs` repo: 

```git clone git@github.com:CCOMJHC/marine_radar_control_msgs.git```

### Build

From the root of your workspace, run `colcon build`.

## Usage

TODO: plugin screenshot with radar connected

## Topics

### Subscribed Topics 

| Topic  | Data Type                                   | 
|--------|---------------------------------------------|
| `todo` | `marine_radar_control_msgs/RadarControlSet` |
| `todo` | `marine_sensor_msgs/RadarSector` |

### Published Topics 

| Topic  | Data Type                                   | 
|--------|---------------------------------------------|
| `todo + change_state` | `marine_radar_control_msgs/RadarControlValue` |