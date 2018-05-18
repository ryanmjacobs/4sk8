# 4sk8

## Introduction
Within a 24 hour timeframe, our team augmented a skateboard with hardware peripherals that guide
the rider to a destination. We integrated the FourSquare API to retrieve our end goal, and used
real-time GPS data to calculate the user's necessary direction. The direction is converted to
a lightstrip pattern for the user's discretion.

Our board utilizes Twilio Programmable Wireless for data connectivity.

## Usage
1. User turns on skateboard hardware using a slider switch.
2. User opens our app on their phone.
3. User enters a location query (e.g. Ramen, In-and-Out, Target, etc.)
    - A request to the FourSquare API fetches the nearest location that fits the input query.
4. Skateboard lights up, with a compass underglow.
5. As the user rides, the compass continually adjusts in real-time to direct the user to their
   chosen location.

## Features
- FourSquare integration
- GPS
- IoT Wifi / Twilio SMS+Data
- Oh yeah, and it lights up

### Stack
- C++
- Node.js
- Vanilla HTML/CSS/JS

&copy; 2018 Ryan Jacobs, Chi Wong, David James, Srivishnu Ramamurthi, and Alex Chen

<img src="https://github.com/ryanmjacobs/4sk8/raw/master/photos/P1040136.JPG" width="100%">
<img src="https://github.com/ryanmjacobs/4sk8/raw/master/photos/P1040159.JPG" width="100%">
<img src="https://github.com/ryanmjacobs/4sk8/raw/master/photos/P1040165.JPG" width="100%">
<img src="https://github.com/ryanmjacobs/4sk8/raw/master/photos/P1040168.JPG" width="100%">
<img src="https://github.com/ryanmjacobs/4sk8/raw/master/photos/P1040171.JPG" width="100%">
