% runSim - Runs simulation for the Truck Benchmark developed for AAC 2016
%   Simulation function for running a simulation of Benchmark problem.
%   
%

if ~exist('scenario','var')
  error('"scenario" not loaded');
end
tic
%% set some variables from the scenario and load the Truck model
road=scenario.road;
vehicleMass=scenario.vehicleMass;
load TruckBenchmark_Data
model.vehicle.m=vehicleMass; % Set vehicle mass to the model

%% Do pre computations, Cloud-Scenario
disp('Running controller computations, in the cloud...')
load TruckBenchmark_Control
%control.Ts=1; % Set controller sample time
control.Ts= 0.001;
can_sample_time = 0.001;
%can_sample_time = 0.1;

% Simple smoke limitier assume m_a propto p_im
control.k_smoke=0.0011;
%control.v_set=80; % Add some margin for starting
%control.v_set=scenario.v_set + 1.8; % Add some margin for starting
control.v_set=scenario.v_set; % Add some margin for starting

cct=toc; % measure cloud computing time

fprintf('Cloud computing time %.3f s\n',cct)

%% Do on-line simulation
disp('Runnig benchmark simulation...')
sim('TruckBenchmark')
