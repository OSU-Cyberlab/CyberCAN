% Load the CSV data
data = readtable('sensor_data_complete_high_res2.csv');

% Remove NaN values from the generated data and timestamps
valid_idx = ~isnan(data.gen_speed_30kph) & ~isnan(data.Timestamp_gen1);
filtered_data = data(valid_idx,:);

% Create the time series for original data
ts_orig_30kph = timeseries(filtered_data.orig_speed_30kph, filtered_data.Timestamp1, 'Name', 'orig_speed_30kph');
% Create the time series for generated data
ts_gen_30kph = timeseries(filtered_data.gen_speed_30kph, filtered_data.Timestamp_gen1, 'Name', 'gen_speed_30kph');
% Create the time series for original data
ts_orig_40kph = timeseries(filtered_data.orig_speed_40kph, filtered_data.Timestamp2, 'Name', 'orig_speed_40kph');
% Create the time series for generated data
ts_gen_40kph = timeseries(filtered_data.gen_speed_40kph, filtered_data.Timestamp_gen2, 'Name', 'gen_speed_40kph');
% Create the time series for original data
ts_orig_50kph = timeseries(filtered_data.orig_speed_50kph, filtered_data.Timestamp3, 'Name', 'orig_speed_50kph');
% Create the time series for generated data
ts_gen_50kph = timeseries(filtered_data.gen_speed_50kph, filtered_data.Timestamp_gen3, 'Name', 'gen_speed_50kph');
% Create the time series for original data
ts_orig_60kph = timeseries(filtered_data.orig_speed_60kph, filtered_data.Timestamp4, 'Name', 'orig_speed_60kph');
% Create the time series for generated data
ts_gen_60kph = timeseries(filtered_data.gen_speed_60kph, filtered_data.Timestamp_gen4, 'Name', 'gen_speed_60kph');
% Create the time series for original data
ts_orig_70kph = timeseries(filtered_data.orig_speed_70kph, filtered_data.Timestamp5, 'Name', 'orig_speed_70kph');
% Create the time series for generated data
ts_gen_70kph = timeseries(filtered_data.gen_speed_70kph, filtered_data.Timestamp_gen5, 'Name', 'gen_speed_70kph');
% Create the time series for original data
ts_orig_80kph = timeseries(filtered_data.orig_speed_80kph, filtered_data.Timestamp6, 'Name', 'orig_speed_80kph');
% Create the time series for generated data
ts_gen_80kph = timeseries(filtered_data.gen_speed_80kph, filtered_data.Timestamp_gen6, 'Name', 'gen_speed_80kph');
% Create the time series for original data
ts_orig_90kph = timeseries(filtered_data.orig_speed_90kph, filtered_data.Timestamp7, 'Name', 'orig_speed_90kph');
% Create the time series for generated data
ts_gen_90kph = timeseries(filtered_data.gen_speed_90kph, filtered_data.Timestamp_gen7, 'Name', 'gen_speed_90kph');

% Combine the time series objects into a cell array or structure
ts = struct('orig_30kph', ts_orig_30kph, 'gen_30kph', ts_gen_30kph, 'orig_40kph', ts_orig_40kph, 'gen_40kph', ts_gen_40kph, 'orig_50kph', ts_orig_50kph, 'gen_50kph', ts_gen_50kph, 'orig_60kph', ts_orig_60kph, 'gen_60kph', ts_gen_60kph,'orig_70kph', ts_orig_70kph, 'gen_70kph', ts_gen_70kph, 'orig_80kph', ts_orig_80kph, 'gen_80kph', ts_gen_80kph, 'orig_90kph', ts_orig_90kph, 'gen_90kph', ts_gen_90kph);

% Save the time series data in a .mat file
save('attack_vehicle_velocity_RCGAN.mat', 'ts', '-v7.3');