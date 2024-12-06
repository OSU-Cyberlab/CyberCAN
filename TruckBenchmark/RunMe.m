% RunMe
% Select scenario
clear all
close all
clc

spoofed_value = 0;
v_vehicle = 0;
attack_time = 0;
DoS = 0;

%can_sample_time = 0.01;%-1; %0.54e-3 recommended time for CAN Sample
sim_time = input('Enter the total simulation time: ');
assignin('base', 'sim_time', sim_time);

cruise_profile = input('Select Cruise Profile (Step decrease = 1, Constant 80kph = 2): ');
assignin('base', 'cruise_profile', cruise_profile);

attack_type = input('Select the type of Attack (1= Fuzzy, 2=spoofing, 3=Plateau, 4=Replay Attack, 5 = GAttack, 6= C-GAttack, 7= No Attack, 8 = Denial of Service):');
assignin('base', 'attack_type', attack_type);

attack_freq = input('Enter the desired frequency of attack: ');
assignin('base', 'attack_freq', attack_freq);

attack_duration = input('Enter the duration of each attack: ');
assignin('base', 'attack_duration', attack_duration);

if (attack_type == 2)
    spoofed_value= input('Set the spoofing value:');
    assignin('base', 'spoofed_value', spoofed_value);
end

if (attack_type == 3)
    assignin('base', 'plateau', 1);
else
    assignin('base', 'plateau', 0);
end

if (attack_type ~= 7)
    attack_time = input('Enter the time for attack: ');
    assignin('base', 'attack_time', attack_time);
end


%for GAttack (Success) Parameters are:
% Enter the total simulation time: 650
% Select Cruise Profile (Step decrease = 1, Constant 80kph = 2): 2
% Select the type of Attack (0 = No Attack, 1 = GAttack, 2= C-GAttack): 1
% Enter the time for attack (Enter Simulation Time if No Attack): 150

%for GAttack (Fail) Parameters are:
% Enter the total simulation time: 650
% Select Cruise Profile (Step decrease = 1, Constant 80kph = 2): 1
% Select the type of Attack (0 = No Attack, 1 = GAttack, 2= C-GAttack): 1
% Enter the time for attack (Enter Simulation Time if No Attack): 150


%for C-GAttack Parameters are:
% Enter the total simulation time: 650
% Select Cruise Profile (Step decrease = 1, Constant 80kph = 2): 1
% Select the type of Attack (0 = No Attack, 1 = GAttack, 2= C-GAttack): 2
% Enter the time for attack (Enter Simulation Time if No Attack): 150
%% C-GAttack Data Loading

load('attack_vehicle_velocity_RCGAN.mat');
% Desired timeline (Length of original time * 10 seconds)
desired_time = ts.orig_30kph.Time * 20;
%interpolating data to map speed profile to desired timeline
% Example data (Replace ts.gen_30kph.Data with your actual data)
data = ts.gen_30kph.Data;  % Assuming this is the speed profile data with 35,000 indices
% Original timeline (Assuming 1 index corresponds to 1 time unit)
original_time = ts.gen_30kph.Time;
% Resample or interpolate the data to match the desired timeline
ts.gen_30kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_30kph.Time = desired_time;

% figure;
% plot(ts.gen_30kph.Time, ts.gen_30kph.Data);
% hold on;
% plot(ts.orig_30kph.Time, ts.orig_30kph.Data);
% hold off;

data = ts.gen_40kph.Data; 
original_time = ts.gen_40kph.Time;
ts.gen_40kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_40kph.Time = desired_time;

data = ts.gen_50kph.Data; 
original_time = ts.gen_50kph.Time;
ts.gen_50kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_50kph.Time = desired_time;

data = ts.gen_60kph.Data; 
original_time = ts.gen_60kph.Time;
ts.gen_60kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_60kph.Time = desired_time;

data = ts.gen_70kph.Data; 
original_time = ts.gen_70kph.Time;
ts.gen_70kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_70kph.Time = desired_time;

data = ts.gen_80kph.Data; 
original_time = ts.gen_80kph.Time;
ts.gen_80kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_80kph.Time = desired_time;

data = ts.gen_90kph.Data; 
original_time = ts.gen_90kph.Time;
ts.gen_90kph.Data = interp1(original_time, data, desired_time, 'linear');
ts.gen_90kph.Time = desired_time;

% figure;
% plot(ts.gen_90kph.Time, ts.gen_90kph.Data);
% hold on;
% plot(ts.orig_90kph.Time, ts.orig_90kph.Data);
% hold off;

%% GAttack Data Loading

gattack_data = load('gattack_data_80kph.mat');
data = gattack_data.gattack_lp;
original_time = 1:length(data);

gattack_data = interp1(original_time, data, desired_time, 'linear');
gattack_time = desired_time;

% figure;
% plot(gattack_time, gattack_data);
% hold on;
% plot(ts.orig_30kph.Time, ts.orig_80kph.Data);
% hold off;

%% Simulation Section

%CaseToRun='Flat';
CaseToRun='So_No';

switch CaseToRun
  case 'So_No'
    load Sodertalje_Norrkoping_Scenario
    scenario.v_set = 0;
    scenario.v_init = scenario.v_set;
    runSim;
  case 'Flat'
    road.k_slopeVector = [0 0];
    road.x_distanceVector = [0 25000];
    scenario.vehicleMass=40000;
    scenario.road=road;
    scenario.v_set=80;
    scenario.v_init=scenario.v_set;
    %scenario.v_init=0;
    scenario.gear_init=4;
    scenario.vehicleMass=40000;
    scenario.h_0 = 0;
    runSim;
end

%% acquiring signal data for GAN
%vehicle_data = extractTimetable(TruckBenchmark_Result,SignalNames=["v_vehicle","x_distance"]);
% writetimetable(vehicle_data, 'vehicle_data.csv');
%vehicle_data_vel = extractTimetable(TruckBenchmark_Result, 'SignalNames',"v_vehicle");      %extracting velocity only
%vehicle_data_dis = extractTimetable(TruckBenchmark_Result, 'SignalNames',"x_distance");      %extracting velocity only

%% Analysis

%data_normal = load('results_normal_08312024.mat');
%save('results_normal_gattack_09012024.mat', 'v_chassis', 'simTime', 'v_error', 'v_gattack', 'v_ref', 'v_cgattack', 'k_slope', 'accel', 'TruckBenchmark_Result');
data_normal_gattack = load('results_normal_gattack_09012024.mat');

%save('results_normal_CGattack_09012024.mat', 'v_chassis', 'simTime', 'v_error', 'v_gattack', 'v_ref', 'v_cgattack', 'k_slope', 'accel', 'TruckBenchmark_Result');
data_normal_CGattack = load('results_normal_CGattack_09012024.mat');

%figure; plot(vehicle_data_dis.x_distance,vehicle_data_vel.v_vehicle)
figure; plot(vel, accel); xlabel('Velocity'); ylabel('Acceleration'); xlim([0, 120]); title('Velocity vs. Acceleration');grid on;
figure; plot(simTime, v_error); xlabel('Time'); ylabel('Velocity Error'); title('Velocity Error vs. Time');grid on;
%writetimetable(vehicle_data_vel, 'velocity.csv');

%%%%%%%%%%%Evaluating GAttack and C-GAttack%%%%%%%%%%%%%%%%%%%%%%%%%
%figure; plot(v_ref); xlabel('Time'); ylabel('Reference Velocity - Set Commands'); ylim([0, 100]); title('Ref Velocity vs. Time');grid on;
%figure; plot(v_cgattack); xlabel('Time'); ylabel('C-GAttack'); ylim([0, 100]); title('C-GAttack Velocity vs. Time');grid on;
%figure; plot(v_gattack); xlabel('Time'); ylabel('GAttack'); ylim([0, 100]); title('GAttack Velocity vs. Time');grid on;
%figure; plot(v_chassis); xlabel('Time'); ylabel('Actual Vel'); ylim([0, 100]); title('Actual Velocity (Normal Behavior) vs. Time');grid on;
%figure; plot(k_slope.*100); xlabel('Time'); ylabel('slope (rad*100)'); title('road slope vs. Time');grid on;

%calculating Mean Square Error between the current velocity and the normal velocity signal
mse = mean((v_chassis.Data - data_normal_gattack.v_chassis.Data).^2);
%rmspe = sqrt(mean(((data_normal_gattack.v_chassis.Data - v_chassis.Data) ./ data_normal_gattack.v_chassis.Data).^2)) * 100;
disp(['Mean Squared Error: ', num2str(mse)]);

%calculating Max Velocity Reached
max_vel = max(v_chassis.Data);
disp(['Max Velocity Reached: ', num2str(max_vel)]);

figure; plot(v_ref, 'b', 'LineWidth', 2); xlabel('Time'); ylabel('Velocity'); ylim([0, max(v_chassis)+10]); title('Cruise Speed Command vs. Vehicle Velocity vs. Time');%grid on;
hold on;
plot(v_chassis, 'r', 'LineWidth', 2);
hold on;
plot(data_normal_gattack.v_chassis, '--m', 'LineWidth' , 1);
yyaxis right
area(k_slope.Time,(k_slope.Data),'FaceColor',[0.7,0.7,0.7],'FaceAlpha',.3,'EdgeAlpha',0, 'LineWidth', 2);
ylabel('Road Grad [rad]')
legend('Cruise Setpoint Command', 'Actual Velocity', 'Normal Velocity', 'Road Slope');
% Display the rmspe on the plot
text(0.1, 0.9, ['MSE: ', num2str(mse, '%.2f')], 'Units', 'normalized', 'FontSize', 12, 'Color', 'k');
text(0.1, 0.96, ['Max Veloctiy(kph): ', num2str(max_vel, '%.2f')], 'Units', 'normalized', 'FontSize', 12, 'Color', 'k');
hold off;

figure; plot(v_attack, 'b', 'LineWidth', 1); xlabel('Time'); ylabel('Veloctiy (kph)'); ylim([0, max(v_attack)+10]); title('Malicious Data Input (Feedback) vs. Time');%grid on;

%GAttack Success Demo
if (cruise_profile == 2 && attack_type == 5)
    %data_normal_gattack
    figure; plot(v_ref, 'b', 'LineWidth', 1); xlim([0, max(simTime)]); xlabel('Time'); ylabel('Velocity [km/h]'); ylim([0, max(v_chassis)]); title('[Scenario: GAttack (Success)] Velocity vs. Time');%grid on;
    hold on;
    plot(v_gattack, 'r', 'LineWidth', 2);
    hold on;
    plot(data_normal_gattack.v_chassis, '--m', 'LineWidth' , 2);
    hold on;
    plot(v_chassis, 'k', 'LineWidth', 1);
    yyaxis right
    area(k_slope.Time,(k_slope.Data),'FaceColor',[0.7,0.7,0.7],'FaceAlpha',.3,'EdgeAlpha',0, 'LineWidth', 2);
    ylabel('Road Grad [rad]')
    legend('Reference Velocity - cruise cmd', 'GAttack Velocity', 'Normal Velocity', 'Chassis Velocity', 'Road Slope');
    hold off;

    thr_normal = data_normal_gattack.TruckBenchmark_Result{2}.Values.Data; %throttle cmd for normal drive cycle
    thr_attack = TruckBenchmark_Result{2}.Values.Data;    %throttle cmd for attack cycle
    figure; 
    plot(data_normal_gattack.simTime , thr_normal./10, '--b', 'LineWidth', 2); xlim([0, max(simTime)]); xlabel('Time'); ylabel('throttle cmd %'); ylim([-10, 40]); title('Throttle cmd % (GAttack success)');%grid on;
    hold on;
    plot(simTime, thr_attack./10, 'r', 'LineWidth', 1);
    legend('Throttle cmd (Normal)', 'Throttle cmd (Attack)');
    
    figure;
    plot(data_normal_gattack.simTime , data_normal_gattack.v_error, '--b', 'LineWidth', 1); xlim([0, max(simTime)]); xlabel('Time'); ylabel('Vel Error km/h'); title('Vel Error km/h (GAttack success)');%grid on;
    hold on;
    plot(simTime, v_error, 'r', 'LineWidth', 2);
    hold off;
    legend('Velocity Error (Normal)', 'Velocity Error (Attack)');
    hold off;
end


%%GAttack Fail Demo on varying cruise profile
if (cruise_profile == 1 && attack_type == 5)
    %data_normal = load('results_normal_08312024.mat'); %to get what the normal velocity would have looked like
    
    figure; plot(v_ref, 'b', 'LineWidth', 1); xlim([0, max(simTime)]); xlabel('Time'); ylabel('Velocity [km/h]'); ylim([0, max(v_chassis)]); title('[Scenario: GAttack (Fail)] Velocity vs. Time');%grid on;
    hold on;
    plot(v_gattack, 'r', 'LineWidth', 2);
    hold on;
    plot(data_normal_CGattack.v_chassis, '--m', 'LineWidth' , 2);
    hold on;
    plot(v_chassis, 'k', 'LineWidth', 1);
    hold on;
    yyaxis right
    area(k_slope.Time,(k_slope.Data),'FaceColor',[0.7,0.7,0.7],'FaceAlpha',.3,'EdgeAlpha',0, 'LineWidth', 2);
    ylabel('Road Grad [rad]')
    legend('Reference Velocity - cruise cmd', 'GAttack Velocity', 'Normal Velocity', 'Chassis Velocity', 'Road Slope');
    hold off;
    
    thr_normal = data_normal_CGattack.TruckBenchmark_Result{2}.Values.Data; %throttle cmd for normal drive cycle
    thr_attack = TruckBenchmark_Result{2}.Values.Data;    %throttle cmd for attack cycle
    figure; 
    plot(data_normal_CGattack.simTime ,thr_normal./10, '--b', 'LineWidth', 2); xlim([0, max(simTime)]); xlabel('Time'); ylabel('throttle cmd %'); ylim([-10, 40]); title('Throttle cmd % (GAttack fail)');%grid on;
    hold on;
    plot(simTime, thr_attack./10, 'r', 'LineWidth', 1);
    legend('Throttle cmd (Normal)', 'Throttle cmd (Attack)');
    
    figure;
    plot(data_normal_CGattack.simTime , data_normal_CGattack.v_error, '--b', 'LineWidth', 1); xlim([0, max(simTime)]); xlabel('Time'); ylabel('Vel Error km/h'); title('Vel Error km/h (GAttack fail)');%grid on;
    hold on;
    plot(simTime, v_error, 'r', 'LineWidth', 2);
    hold off;
    legend('Velocity Error (Normal)', 'Velocity Error (Attack)');
    hold off;
end



%%C-GAttack Success Demo
if (attack_type == 6) %cruise_profile == 1 &&
    figure; plot(v_ref, 'b', 'LineWidth', 1); xlim([0, max(simTime)]); xlabel('Time'); ylabel('Velocity [km/h]'); ylim([0, max(v_chassis)]); title('[Scenario: C-GAttack] Velocity vs. Time');%grid on;
    hold on;
    plot(v_cgattack, 'r', 'LineWidth', 2);
    hold on;
    plot(data_normal_CGattack.v_chassis, '--m', 'LineWidth', 2);
    hold on;
    plot(v_chassis, 'k', 'LineWidth', 1);
    hold on;
    yyaxis right
    area(k_slope.Time,(k_slope.Data),'FaceColor',[0.7,0.7,0.7],'FaceAlpha',.3,'EdgeAlpha',0, 'LineWidth', 2);
    ylabel('Road Grad [rad]')
    legend('Reference Velocity - cruise cmd', 'C-GAttack Velocity', 'Normal Velocity', 'Chassis Velocity', 'Road Slope');
    hold off;
    %figure; plot(v_chassis); xlabel('Time'); ylabel('Actual Vel'); ylim([0, 100]); title('Actual Velocity (Normal Behavior) vs. Time');%grid on;
    
    thr_normal = data_normal_CGattack.TruckBenchmark_Result{2}.Values.Data; %throttle cmd for normal drive cycle
    thr_attack = TruckBenchmark_Result{2}.Values.Data;    %throttle cmd for attack cycle
    figure; 
    plot(data_normal_CGattack.simTime , thr_normal./10, '--b', 'LineWidth', 2); xlim([0, max(simTime)]); xlabel('Time'); ylabel('throttle cmd %'); ylim([-10, 40]); title('Throttle cmd % (C-GAttack success) ');%grid on;
    hold on;
    plot(simTime, thr_attack./10, 'r', 'LineWidth', 1);
    legend('Throttle cmd (Normal)', 'Throttle cmd (Attack)');
    
    figure;
    plot(data_normal_CGattack.simTime , data_normal_CGattack.v_error, '--b', 'LineWidth', 1); xlim([0, max(simTime)]); xlabel('Time'); ylabel('Vel Error km/h'); title('Vel Error km/h (C-GAttack success)');%grid on;
    hold on;
    plot(simTime, v_error, 'r', 'LineWidth', 2);
    hold off;
    legend('Velocity Error (Normal)', 'Velocity Error (Attack)');
    hold off;
end

% Convert timetable to a table before saving to HDF5
% dataAsTable = table(TruckBenchmark_Result.Time, TruckBenchmark_Result.Sine, TruckBenchmark_Result.Cosine, TruckBenchmark_Result.Tangent, 'VariableNames', {'Time', 'Sine', 'Cosine', 'Tangent'});
% writetable(dataAsTable, 'data.h5', 'Filetype', 'HDF5', 'WriteRowNames', true, 'WriteVariableNames', true);

%save('myDataFile.mat', 'newVar', '-append');
%load('myDataFile.mat');

%% Data for IDS
%v_chassis_data_gattack = data_normal_gattack.v_chassis.Data;
%v_chassis_data_cgattack = data_normal_CGattack.v_chassis.Data;
%save('IDS_gattack_success_09052024.mat', 'simTime', 'v_gattack', 'v_chassis_data_gattack');
%save('IDS_gattack_fail_09052024.mat', 'simTime', 'v_gattack', 'v_chassis_data_gattack');
%save('IDS_cgattack_success_09052024.mat', 'simTime', 'v_cgattack', 'v_chassis_data_cgattack');
