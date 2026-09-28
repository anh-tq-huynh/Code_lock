# Summary
This program implements a code lock, interconnecting leds and buttons with a queue.

# Requirements
Implement a code lock that uses three tasks to read button presses and one task to process the button
presses. The button presses from reader tasks must be passed to the processing task using a queue. The
button to monitor and the queue to send to are passed through task parameters pointer to the button
reader tasks.
The processing task waits on the button queue with 5 second timeout. If a button press is received the
corresponding LED is lit for 200ms and the press is processed as shown in the state diagram. If a timeout
occurs, then lock is returned to the initial state where it starts detecting the sequence from the beginning.
An open lock is indicated by switching on all three LEDs for 5 seconds (=the time lock stays open). If any
button is pressed while lock is open the lock is closed immediately (LEDs switched off).

# Hardware
The program was implemented on Raspberry Pi Pico W.
