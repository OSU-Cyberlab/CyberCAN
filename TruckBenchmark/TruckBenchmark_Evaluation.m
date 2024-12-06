v_vehicle       = TruckBenchmark_Result.find('v_vehicle').Values;
fuelConsumption = TruckBenchmark_Result.find('fuelConsumption').Values;
distance        = TruckBenchmark_Result.find('x_distance').Values;
altitude        = TruckBenchmark_Result.find('altitude').Values;
k_slope         = TruckBenchmark_Result.find('k_slope').Values;
n_engine        = TruckBenchmark_Result.find('n_engine').Values;
gear            = TruckBenchmark_Result.find('gear').Values;
curr_gear       = TruckBenchmark_Result.find('curr_gear').Values;
lambda          = TruckBenchmark_Result.find('lambda').Values;
M_c             = TruckBenchmark_Result.find('M_c').Values;
clutch_pos      = TruckBenchmark_Result.find('clutch_pos').Values;
M_c_max         = TruckBenchmark_Result.find('M_c_max').Values;
u_delta         = TruckBenchmark_Result.find('u_delta').Values;


figure(1)
clf
subplot(321)
plot(v_vehicle.time , v_vehicle.data)
grid
xlabel('Time [s]')
ylabel('Vehicle speed [km/h]')
title(['Vehicle mass: ' num2str(model.vehicle.m) ' [kg], Average velocity: '...
  sprintf('%3.2f',distance.data(end)/distance.time(end)*3.6) '[km/h]']);
xlim([0 v_vehicle.time(end)])




subplot(323)
plot(k_slope.time , k_slope.data)
grid
xlabel('Time [s]')
ylabel('Slope [-]')
xlim([0 v_vehicle.time(end)])

subplot(325)
plot(altitude.time , altitude.data)
grid
xlabel('Time [s]')
ylabel('Altitude [m]')
xlim([0 v_vehicle.time(end)])

subplot(322)
plot(gear.time , gear.data, curr_gear.time, curr_gear.data)%, clutch_pos.time,clutch_pos.data*15,'.-')
grid
xlabel('Time [s]')
ylabel('Gear [-]')
legend('gear_{ref}','gear_{act}')
xlim([0 v_vehicle.time(end)])
ylim([-0.5 14.5])
title(['Fuel consumption: ' sprintf('%2.2f',fuelConsumption.data(end)) ' [litre/100km]  Time:'...
                            sprintf('%2.2f',fuelConsumption.time(end)) '[s]'])

subplot(324)
plot(n_engine.time , n_engine.data)
grid
xlabel('Time [s]')
ylabel('Engine speed [rpm]')
xlim([0 v_vehicle.time(end)])

subplot(326)
plot(simTime , simM_e) %, M_c.time,M_c.data, M_c_max.time,abs(M_c_max.data), '--')
grid
xlabel('Time [s]')
ylabel('Torque [Nm]')
xlim([0 v_vehicle.time(end)])


figure(2);clf
subplot(321)
ind_v=find(v_vehicle.data>91);
plot(v_vehicle.time , v_vehicle.data,[0 v_vehicle.time(end)],91*[1 1],'r--',...
    v_vehicle.time(ind_v),v_vehicle.data(ind_v),'r.')    
grid
if isempty(ind_v)
    legend('Vehicle speed','Speed limit')
else
    legend('Vehicle speed','Speed limit','Failed points')
end
xlabel('Time [s]')
ylabel('Vehicle speed [km/h]')
xlim([0 v_vehicle.time(end)])


subplot(322)
n_t_limit=11e4;
ind_n_t=find(simn_t>n_t_limit);
plot(simTime,simn_t,[0 v_vehicle.time(end)],n_t_limit*[1 1],'r--',simTime(ind_n_t),simn_t(ind_n_t),'r.')
if isempty(ind_n_t)
    legend('Turbo speed','Turbo speed limit')
else
    legend('Turbo speed','Turbo speed limit','Failed points')
end
grid
xlabel('Time [s]')
ylabel('Turbo Speed [RPM]')
xlim([0 v_vehicle.time(end)])
if (max(get(gca,'ylim'))<11.5e4)
    set(gca,'ylim',[min(get(gca,'ylim')) 11.5e4]);
end


subplot(323)
lambda_limit=1.3;
ind_lambda=find(simlambda<lambda_limit);
plot(simTime,simlambda,[0 v_vehicle.time(end)],lambda_limit*[1 1],'r--',simTime(ind_lambda),simlambda(ind_lambda),'r.')
grid
if isempty(ind_lambda)
    legend('lambda','lambda limit')
else
    legend('lambda','lambda limit','Failed points')
end
xlabel('Time [s]')
ylabel('Lambda [-]')
xlim([0 v_vehicle.time(end)])
ylim([1 5])

subplot(324)
plot(simTime,simp_im,simTime,simp_em)
grid
xlabel('Time [s]')
ylabel('p_{im} & p_{em} [Pa]')
xlim([0 v_vehicle.time(end)])
legend('p_{im}','p_{em}')


subplot(325)
plot(simTime,simu_vgtact,simTime,simu_egr,simTime,simu_delta,u_delta.time,u_delta.data,clutch_pos.time,clutch_pos.data*100)
grid
xlabel('Time [s]')
ylabel('Control signals [%]')
xlim([0 v_vehicle.time(end)])
legend('u_{vgt}','u_{egr}','u_{\delta,act}','u_{\delta,ref}','Clutch')


linkaxes([findall(1,'type','axes','tag','');findall(2,'type','axes','tag','')],'x')

subplot(326)
plot(simn_e,simM_e,simn_e(ind_lambda),simM_e(ind_lambda),'r.')
grid
if ~isempty(ind_lambda)
    legend('Torque','\lambda < 1.3')
end
xlabel('Engine speed [rpm]');
ylabel('Torque [Nm]')

fail=[0 0 0 0];
%% Check data and report
if max(v_vehicle.data)>91,
  disp(['Controller failed, vehicle got caught speeding. v_max=' ...
      num2str(max(v_vehicle.data)) ' km/h ,  v_lim=' num2str(91) ' km/h'])
  fail(1)=1;
end
if any(simlambda<lambda_limit)
  disp(['Controller failed, vehicle emits too much smoke. lambda_min=' ...
      num2str(min(simlambda)) ' , lambda_lim=' num2str(lambda_limit)])
  fail(2)=1;
end
if any(simn_t>110e3),
  disp(['Controller failed, turbo charger damaged. n_t_max=' ...
      num2str(max(simn_t)) ' rpm , n_t_lim=' num2str(110e3) ' rpm'])
  fail(3)=1;
end
if distance.data(end)/distance.time(end)*3.6<scenario.v_set,
  disp(['Controller failed, controller drives too slow, missed delivery deadline. v_avg=' ...
      num2str(distance.data(end)/distance.time(end)*3.6) ' km/h , v_des=' ...
      num2str(scenario.v_set) ' km/h'])
  fail(4)=1;
end

