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


### 3. Display 

The display on which we will display data about the name of the signal and the mode in which we currently work (mode 1 displays Fmod = 0.2F, mode 2 - Fmod = 0.1F). The display is in the window with the components by: Display -> Character LCD, let's call it LCD, no additional settings with this component are required.

### 4. Mode selection button

It will switch between modes. You can find the button by: Ports and pins -> Analog pin. After adding a button to the circuit, open the settings, name Pin_mode and check the box next to Digital input, as shown in Fig. 

### 5. The Start button
(Pin_gen) is selected similarly to the previous one.

After making the appropriate settings, we obtain a ready-made diagram of the hardware of the generator, which is presented in Fig. 7


We will generate the Start signal with one of the toggle switches on the additional board to the Pioneer Kit. We have a choice of six toggle switches, respectively ports from P1.0 to P1.5. We need two toggle switches: One to select the mode, the other to start the generation. Let's use port P1.1 to select the mode and P1.0 to start generation. Also, to connect the DAC to the PSoC4 output, we will give the P3.0 port to the Pin_analog_out pin, and P2 to the display [6: 0]. This is shown in Figures - 8 a, b.


This completes the drawing of the scheme and the configuration of the implemented components in the project. Then it remains to open the file "main.c" and write the program part.
 

