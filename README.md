# Arduino based brachiograph clock
This project was inspired by https://www.brachiograph.art/ .
This code, instead of using raspberry pi, runs on arduino. It uses the cosine law of triangles
to convert from x-y positions to the angles for the 2 joins.
The project was built as project 2 of Mark Rober's engineering class.

the system uses:
1. atx power supply (required to power the servos)
2. elegoo arduino board atmel mega 2560: https://smile.amazon.com/gp/product/B01EWNUUUA/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
3. 3 servos: ds3218mg: https://smile.amazon.com/gp/product/B07MH1QRK5/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
4. one linear actuator, 6in, 12VDC: https://smile.amazon.com/gp/product/B07HP2RZJ8/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
5. two 5V relays to change the direction of the linear actuator: https://smile.amazon.com/gp/product/B00LW15A4W/ref=ppx_yo_dt_b_asin_title_o03_s01?ie=UTF8&psc=1

2 servos are used for the arm, the third is used to lift the arm so the pen does not write.
We use a dry erase board and use the linear actuator to delete the previous time.

timelapse: https://www.youtube.com/watch?v=Pwm5O0Vulfs
