# Strava Data Visualizer
This project is a data visualization tool built with C++ and the Qt framework. It uses the Strava API to retrieve workout data and displays it in an interactive chart. The tool provides insights into workout trends over time, including distance, average heart rate, moving time, etc.

## Passing Strava API credentials:

<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/0da62384-36a1-4588-9448-8017da471263" width="300">
</div>

## Example Chart 1:
<!---
<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/60a9e2b4-33a3-429e-81db-f05b424be81e" width="700">
</div>
-->

<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/502beae7-fd49-4dff-b741-333284f45ff4" width="600">
</div>
<br>
<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/ce1af193-df06-41e2-bb4f-85400d37944f" width="600">
</div>



## Example Chart 2:
<!---
<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/64cd2692-05c0-406b-9482-c393d7557cb8" width="600">
</div>
-->
<!---
<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/366acaed-2895-4e39-86a6-7465639d0a5c" width="600">
</div>
-->
<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/a77e881e-cf4b-4452-8996-599dade740b8" width="600">
</div>
<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/da6efef2-6459-4f79-a6cd-18385c71033d" width="600">
</div>


  
## Features

- Retrieves workout data from Strava's REST API using OAuth 2.0 authentication.
- Visualizes data using interactive charts created with Qt Charts.

## Installation (Build)

### Prerequisites (To generate executable)
- Docker Engine
- git

### Steps (Linux)
1. `git clone https://github.com/helioshe4/Strava-Data-Visualizer.git`  
2. `cd Strava-Data-Visualizer`  
3. Run script to compile via Docker container: `./tools/build.sh`  
4. Navigate to executable: `cd QTStravaChart`
5. Run executable: `./QTStravaChart`

   
## Installation (Development)

### Prerequisites

- C++ compiler (C++11 or later is required)
- Qt 5.15.3 or higher
- libcurl
- nlohmann JSON library
- Qt Charts library

### Steps (Linux)

1. `sudo apt-get update`  
2. `sudo apt-get -y install build-essential qt5-default libcurl4-openssl-dev nlohmann-json3-dev libqt5charts5-dev`  
3. Clone the repository: `git clone https://github.com/helioshe4/Strava-Data-Visualizer.git`  
4. Navigate to the project's src directory: `cd Strava-Data-Visualizer/src`
5. Compile the project: `make`
6. To develop via qt: run `qtcreator` for the qt IDE.  Ensure you have X11 forwarding if using WSL or via ssh.

## Usage

If you would like to use API credentials from your own Strava account, information can be found [here](https://towardsdatascience.com/using-the-strava-api-and-pandas-to-explore-your-activity-data-d94901d9bfde).
## Authors

Helios He  
helios.he@uwaterloo.ca

## Version History

- July 2023
  - Initial Release
 

## Acknowledgments
- Info on Strava API: [github.com/franchyze923](https://github.com/franchyze923/Code_From_Tutorials/blob/master/Strava_Api/strava_api.py)
<!-- ## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details


Inspiration, code snippets, etc.

- [awesome-readme](https://github.com/matiassingers/awesome-readme)
- [PurpleBooth](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
- [dbader](https://github.com/dbader/readme-template)
- [zenorocha](https://gist.github.com/zenorocha/4526327)
- [fvcproductions](https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46) -->
