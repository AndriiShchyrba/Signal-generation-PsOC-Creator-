# Signal-generation-PsOC-Creator-
The aim of the project is to create a model of the analog signal obtained at the output of the digital-to-analog converter (DAC) for a given sampling rate, DAC bit and the shape of the ideal signal. The model should provide construction of time dependences of ideal, discretized signals and quantization error. The model should also calculate the RMS value of quantization noise. Functional generators are usually used as sources of test signals. For example, it is necessary to check the response of a certain electronic device to the influence of an input signal with certain time or frequency characteristics. A practical example is to check the operation of the amplitude detector. In this case, the input of the amplitude detector is fed an AM signal with a known depth of modulation and evaluate the operation of the AM detector based on the obtained output signal.
# Hardware development
Implementation of a variant of a functional generator based on a programmable system on a PSoC4 chip and a Pioneer Kit training stand. We use PSoC Creator development environment.
 
To implement this task we need:
 
### 1. IDAC
 
The IDAC component is in the component catalog as follows Analog -> DAC -> CurrentDAC. The DAC output must be connected to the PSoC4 output. To do this, place on the diagram of the component Analog Pin (analog pin), which is located along the path Ports and Pins -> Analog Pin. Let's call this component Pin_analog_out.

The DAC setup window is shown in Figure 1

![1 1](https://user-images.githubusercontent.com/64357748/85798406-15d38980-b746-11ea-83e1-2b0eaba5b1e5.jpg)

### 2. Timer

Timer for generating time samples with a frequency of 24 MHz, it is located in the window with the components by Digital-> Functions-> Timer. Let's place the Timer component on the circuit and call it Timer. The timer will generate short-term pulses with a specified period, which will cause an interruption. In the interrupt processing subroutine, we will display the corresponding sample on the DAC. To organize interrupts to the output "tc" components Timer connect the component Interrupt, the implementation of which is called isr. The Interrupt component is located in the component window via System-> Interrupt.

The Timer_ setting window is shown in Figure 1a

![1 2](https://user-images.githubusercontent.com/64357748/85855613-355ac880-b7bf-11ea-94eb-6b6b518c104e.jpg)

The timer for the duration of the generation is called TimerDuration. The optimization frequency of this component is a 32 kHz drive (internal LFCLK generator in PSoC4). At the time we were working with the economical internal resources of PSoC4, we needed the least amount of lower coefficients, and then there was the least 24MGc, like TimerMain.

![1 3](https://user-images.githubusercontent.com/64357748/85872036-e8cfb700-b7d7-11ea-94d9-35742860eacc.jpg)
### 3. Display 

The display on which we will display data about the name of the signal and the mode in which we currently work (mode 1 displays Fmod = 0.2F, mode 2 - Fmod = 0.1F). The display is in the window with the components by: Display -> Character LCD, let's call it LCD, no additional settings with this component are required.

### 4. Mode selection button

It will switch between modes. You can find the button by: Ports and pins -> Analog pin. After adding a button to the circuit, open the settings, name Pin_mode and check the box next to Digital input, as shown in Fig. 

![1 4](https://user-images.githubusercontent.com/64357748/85872040-ea00e400-b7d7-11ea-9555-ef9e71c7c2b2.jpg)

### 5. The Start button
(Pin_gen) is selected similarly to the previous one.

![1 5](https://user-images.githubusercontent.com/64357748/85872046-ea997a80-b7d7-11ea-8870-af92df9f1d4c.jpg)

After making the appropriate settings, we obtain a ready-made diagram of the hardware of the generator

![1 6](https://user-images.githubusercontent.com/64357748/85872049-eb321100-b7d7-11ea-8f81-497bc9d53655.jpg)

We will generate the Start signal with one of the toggle switches on the additional board to the Pioneer Kit. We have a choice of six toggle switches, respectively ports from P1.0 to P1.5. We need two toggle switches: One to select the mode, the other to start the generation. Let's use port P1.1 to select the mode and P1.0 to start generation. Also, to connect the DAC to the PSoC4 output, we will give the P3.0 port to the Pin_analog_out pin, and P2 to the display [6: 0].

![1 7](https://user-images.githubusercontent.com/64357748/85872053-ecfbd480-b7d7-11ea-91c7-6903cea2e974.jpg)

![1 8](https://user-images.githubusercontent.com/64357748/85872057-ed946b00-b7d7-11ea-9fdc-1ce870668257.jpg)

This completes the drawing of the scheme and the configuration of the implemented components in the project. Then it remains to open the file "main.c" and write the program part.
 
 
# Software development
Development should begin with drawing up of algorithm of actions of each component of our device.
The main program works according to the following algorithm:
 
 ![1 9](https://user-images.githubusercontent.com/64357748/85872063-eec59800-b7d7-11ea-9ab6-2143e08bf12c.jpg)
 
The button interrupt processing subroutine works according to the following algorithm:

![1 10](https://user-images.githubusercontent.com/64357748/85872066-ef5e2e80-b7d7-11ea-8be4-f1efa015a876.jpg)
 
Formation of signal samples according to the following algorithm:


Display the signal according to the following algorithm:
 ![1 11](https://user-images.githubusercontent.com/64357748/85872070-f127f200-b7d7-11ea-871f-b924eb438c56.jpg)

 
Now you need to display the idea in the form of code that will be placed in the application. Let's check if the program works correctly. To do this, click on the Program button at the top of the window, or use the hot keys Ctrl + F5. After compiling and flashing, here is what the program displayed:


Mode selector toggle in position 1, Stationary mode.

![1 12](https://user-images.githubusercontent.com/64357748/85872072-f1c08880-b7d7-11ea-8b62-46f8e1befa77.jpg)

 
Oscillogram: mode selection in position 1, Stationary mode.

![1 13](https://user-images.githubusercontent.com/64357748/85872076-f2f1b580-b7d7-11ea-8af5-e7b76b4bd555.jpg)

The display of the mode in which we are works. Let's see if the AM signal is generated. To do this, move the toggle switch to the first position and start the generation with the upper toggle switch. We will follow this on the oscilloscope.

 ![1 14](https://user-images.githubusercontent.com/64357748/85872079-f38a4c00-b7d7-11ea-9a70-951cdcd26def.jpg)

Mode selector toggle in position 1, Run mode

 ![1 15](https://user-images.githubusercontent.com/64357748/85872086-f4bb7900-b7d7-11ea-9b81-292621804bfb.jpg)
 
 Oscillogram: mode selection in position 1, Run mode.

![1 16](https://user-images.githubusercontent.com/64357748/85872090-f5eca600-b7d7-11ea-91fd-6a5a2aab4e42.jpg)

As you can see from the waveform, the program outputs the AM signal with a given frequency. Let's switch the toggle switch to another mode. The program outputs the frequency change by 0.1F, so we can conclude that the program works.

Mode selector toggle switch in position 2, Run mode

![1 16](https://user-images.githubusercontent.com/64357748/85872090-f5eca600-b7d7-11ea-91fd-6a5a2aab4e42.jpg)

 Oscillogram: mode selection in position 2, Run mode.
 
![1 17](https://user-images.githubusercontent.com/64357748/85872097-f71dd300-b7d7-11ea-9cf6-bcbc88596e2a.jpg)

# Calculation of the low-pass filter
The scheme of the filter on the basis of RC-circuit which cuts off high-frequency oscillations is shown. The reactance of the capacitor decreases with frequency, and therefore the capacitor transmits only high-frequency signals, and the better, the higher the frequency. As a result, at high frequencies, the capacitor bypasses the signal. Only a low frequency signal will remain at the output of such a quadrupole.
The cutoff frequency is equal to:
f_gr = 2f_c
f_gr = 2 ∙ 200 = 400 Hz
Now we can determine the capacitance of the capacitor by the formula:
C = 1 / 2πfR
C = 1 / (2 ∙ 3.14 ∙ 400 ∙ 1000) = 0.398 μF

To build the circuit, I choose from a series of E24 capacitors with a capacity of 0.33 uF and 0.068 uF.
The time constant is determined by the formula:
τ = R ∙ C
τ = 1 〖〖10〗 ^ 3 ∙ 0.398 〖∙ 10〗 ^ (- 6) = 398 μs

We make the scheme on the calculated parameters:

The scheme of the low-pass filter.
Output the frequency response of our filter, as we see at -3dB at the point of intersection with the frequency axis, the frequency is 400 Hz.
 
 ![1 18](https://user-images.githubusercontent.com/64357748/85872104-f84f0000-b7d7-11ea-96b4-4ceee660f958.jpg)
 
 Amplitude-frequency characteristics of the filter

![1 19](https://user-images.githubusercontent.com/64357748/85872106-f8e79680-b7d7-11ea-948c-bd9eee427112.jpg)
