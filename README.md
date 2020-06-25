# Signal-generation-PsOC-Creator-
The aim of the project is to create a model of the analog signal obtained at the output of the digital-to-analog converter (DAC) for a given sampling rate, DAC bit and the shape of the ideal signal. The model should provide construction of time dependences of ideal, discretized signals and quantization error. The model should also calculate the RMS value of quantization noise. Functional generators are usually used as sources of test signals. For example, it is necessary to check the response of a certain electronic device to the influence of an input signal with certain time or frequency characteristics. A practical example is to check the operation of the amplitude detector. In this case, the input of the amplitude detector is fed an AM signal with a known depth of modulation and evaluate the operation of the AM detector based on the obtained output signal.
# Hardware development
Implementation of a variant of a functional generator based on a programmable system on a PSoC4 chip and a Pioneer Kit training stand. We use PSoC Creator development environment.
 
To implement this task we need:
 
 1. IDAC
 
The IDAC component is in the component catalog as follows Analog -> DAC -> CurrentDAC. The DAC output must be connected to the PSoC4 output. To do this, place on the diagram of the component Analog Pin (analog pin), which is located along the path Ports and Pins -> Analog Pin. Let's call this component Pin_analog_out.

The DAC setup window is shown in Figure 1
