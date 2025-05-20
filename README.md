# Application1
Analysis/Engineering:
Open-Ended Exploration: Once you get the lab running explore and answer the following.
Vary Priorities: Change the print task’s priority to 2 (higher than blink’s 1). With such short tasks and delays, you may not notice a big difference, but in principle the print task would preempt the blink task if it were ready. Given both tasks spend most time sleeping, the effect is minimal. In later projects with CPU-bound tasks, priority will matter more. Does anything happen to the LED if you increase the delay within the print task?
**Nothing happens to the LED as the print task delays are increased.**
 What if you increase the number of characters printed?
**Nothing is changed when we increased the number of characters printed because the print tasked is not connected with the display of the LED light.**
Thematic Customization: If you chose the space context, perhaps change the printed message to “Telemetry OK” or similar. In healthcare, print a pseudo heart rate. In security, print sensor status.  Assume you were a developer of one of these applications - might there be some considerations that you would want to take into consideration in how verbose (or not) you want your messages to be? If I was a developer of a health care I would want to take into consideration the data logs of each patient. Also, the clarity and the detail precision of description.
Additionally, explain why this system benefits from having correct functionality at predictable times? The system benefits from having correct functionality at predictable times because it ensures reliability and synchronization in real-time applications. Predictable timing is critical for tasks like blinking LEDs or printing messages, where timing errors could disrupt system behavior or user expectations. 
 
Real-Time Concept Check:
Identify the period of each task; you can try to do this via the simulator, or perhaps by printing data to the console?:
LED blink task period: is 550ms, where 300ms is for off and 250 is for on
Print task period: The print task period is 10,000 but I also change it to 500 to see the printing task
Did our system tasks meet the timing requirements? Yes
How do you know? Using the task delayed works, but removing it stops the LED light and code from working. The LED Blink Task was coded to toggle every 250 ms ON / 300 ms OFF, totaling 550 ms.
I then changed the delay on the Console Print Task to 10,000 ms, 500 ms, and even 5,000 ms. I observed the output feedback as I changed the delay.

How did you verify it?
We verified this by printing and analyzing timestamps using xTaskgetticketcount and calculating time differences between events.
When xTaskdelay was removed from the high-priority task, the LED task missed its timing, showing how proper delay and priority management are essential for real-time scheduling.

Did you try running the code? Yes
Can you cause the LED to miss it's timing requirements?
If yes, how?
I made the LED miss its timing by giving the console print task a higher priority and removing it's taskdelay, causing it to hog the CPU and starve the lower-priority LED task.

If no, what did you try?





Single loop systems run all code in one cycle without concurrency, whereas multi task systems use an RTOS to run multiple tasks independently, offering better timing, modularity, and scalability for real-time applications.

When I am working on the debugging of the code, I use artificial intelligence (AI) to assist me. I was able to gain a greater understanding of the small things that I didn’t understand before I took the course. 

