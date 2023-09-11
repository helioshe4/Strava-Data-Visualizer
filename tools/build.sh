#!/bin/bash

# Step 1: Build the Docker image
docker build --target build -t qt_strava_build .

# Step 2: Run the container in detached mode
container_id=$(docker run -d qt_strava_build /bin/sh -c "while :; do sleep 1; done")

# Step 3: Execute make inside the container
docker exec $container_id make -C /src/QTStravaChart

#Copy the executable to the host 
docker cp $container_id:/src/QTStravaChart/QTStravaChart ./QTStravaChart

docker rm -f $container_id

echo "Executable has been copied to ./QTStravaChart"
