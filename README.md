# capacity-firming

Due to the intrinsic intermittent nature of renewable energy source, their utility in a microgrid can be enhanced by adding an energy storage system (ESS). Using a lookup table type MPC (Model Predictive Control), this study presents an optimal charging and discharging algorithm for the ESS which consists of multiple energy storage unit (ESU). The algorithm is designed to enable the integration of renewable energy and an ESS to dispatch scheduled power while performing SoC (State of Charge) balancing for each ESU as well as satisfying the constraints on SoC and current limits in power converters. Simulation and experimental results using ultra-capacitors as ESUs in a DC microgrid are presented here to show the effectiveness of the proposed charging and discharging algorithm.

Hardware Specification : 
1. The PC Host is a windows based PC communicating with the DSP using [Code Composer Studio IDE](https://www.ti.com/tool/CCSTUDIO).
2. The DSP used is a Texas Instruments 32-bit floating-point DSP [TMS320F28335](https://www.ti.com/product/TMS320F28335).

This firmware make sure that all the components required to run the capacity firming algorithm is performing well such as the IGBT switch and the array of sensor used to sense the voltage and current in various part of the experiments.


 ![alt text](https://github.com/apawitan1995/capacity-firming/blob/master/capacity_firming.jpg?raw=true)
