<p align="center">
  <img src="https://github.com/user-attachments/assets/5ebfb781-1bff-4225-bed2-81b0f29f62f2" alt="Arduino-Streamdeck_pic1" width="500"/>
</p>

# Arduino-Streamdeck - What is even that?
Together with a buddy, I built this streamdeck. The functions of the buttons were all hard-coded back then - and it worked great!
But that was a while ago...
Now it was time to give the whole thing a ✨user-friendly✨ upgrade.

My idea: The user should be able to easily customize the button assignments via software - and the Streamdeck (or the Arduino behind it) saves everything locally. No more fiddling around in the code. 😊👍

<details>
  <summary><strong>But first a short overfiew of the streamdeck itself:</strong></summary>

  ### <strong> (You can the full instruction on [Instructables](https://www.instructables.com/HyperDeck-an-Arduino-Streamdeck/)) </strong>



### Used Parts
- Arduino Pro Micro (5V)
- 12 Switches/buttons (I used "CS Matcha Green Switch" from AKKO)
- (optional) led strip as backlight (cut to 3 leds)


### Circuit diagram
<p>
  <img src="https://github.com/user-attachments/assets/abe124eb-8918-41ba-aacf-c531ada75a4c" alt="circuit-diagram-streamdeck" width="500"/>
</p>

### Case
The design of the case is completely up to you :)
BUT I recommend a white filament for the backplate of the buttons to let the light through (if you want it glowing). 
</details>

---

# The HyperDeck Software + How to use it
The whole application is written in C#
fun-fact: This is my first application completely written in C# :)

### So, how the duck do you use it???

When you start the application, the COM-port will probably be the wrong one. (For non-IT folks: a COM-port is like an old-fashioned plug on your computer that lets it talk to other devices. You find out, what the right port is by using the device manager)

Select the right port, and you're connected to your streamdeck in no time.

<strong>Now it's time for the exciting part: You can assign functions to the keys!</strong>

Select the button you want to set on the left side and choose a function/shortcut from the big dropdown on the right side. You can change multiple keys before submitting your changes via the submit button (don't forget 😉)
