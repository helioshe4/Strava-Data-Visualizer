# Strava Data Visualizer
This project is a data visualization tool built with C++ and the Qt framework. It uses the Strava API to retrieve workout data and displays it in an interactive chart. The tool provides insights into workout trends over time, including distance, average heart rate, moving time, etc.

## Passing Strava API credentials:

<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/0da62384-36a1-4588-9448-8017da471263" width="300">
</div>

## Example Chart 1:

<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/60a9e2b4-33a3-429e-81db-f05b424be81e" width="700">
</div>

## Example Chart 2:

<div align="center">
  <img src="https://github.com/helioshe4/Strava-Data-Visualizer/assets/115726225/64cd2692-05c0-406b-9482-c393d7557cb8" width="700">
</div>
  
## Features

- Retrieves workout data from Strava's REST API using OAuth 2.0 authentication.
- Visualizes data using interactive charts created with Qt Charts.

## Installation

### Prerequisites

- C++ compiler (C++11 or later is required)
- Qt 5.15.3 or higher
- libcurl
- nlohmann JSON library
- Qt Charts library

### Steps

1. `sudo apt-get update`  
2. `sudo apt-get -y install build-essential qt5-default libcurl4-openssl-dev nlohmann-json3-dev libqt5charts5-dev`  
3. Clone the repository: `git clone https://github.com/helioshe4/Strava-Data-Visualizer.git`  
4. Navigate to the project's src directory: `cd Strava-Data-Visualizer/src`
5. Compile the project: `make`

## Usage

After compiling the project, you can run the application with `./QTStravaChart`.

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
