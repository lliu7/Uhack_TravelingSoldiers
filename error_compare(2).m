%function: generate error figure, sum errors, avg errors and maximum errors for localization algorithm
a_g = [1, 2 ; 2, 1; 5, 1; 7, 1; 7, 2; 1, 6; 2, 6; 2, 7; 5, 6; 7, 7];

b_g_4 = [1.660703,2.044905; 2.044905,1.660703; 5.008321,1.520934; 7.000000,1.000000; 6.339297,2.044905; 1.660703,5.955095; 2.101837,5.898162; 2.044905,6.339297; 5.253001,6.054287; 7.000000,7.000000];
b_g_2 = [2.079909,2.000000;2.080084,2.000000;5.954312,2.000000;6.085167,2.000000;5.994435,2.000000;2.027152,6.000000;2.055495,6.000000;2.027495,6.000000;5.863131,6.000000;6.198231,6.000000];
b_g_9 = [2.062330,2.062459;2.062459,2.062330;5.962798,2.036399;6.064659,1.935341;5.987228,2.013108;2.027826,5.971931;2.044443,5.955558;2.028069,5.972175;5.903449,5.903593;6.165679,6.165679];

a_t = [1, 2 ; 2, 1; 5, 1; 1, 6; 2, 6; 2, 7; 5, 6];
b_t_4 = [1.660703,2.044905; 2.044905,1.660703; 5.008321,1.520934; 1.660703,5.955095; 2.101837,5.898162; 2.044905,6.339297; 5.253001,6.054287];
b_t_2 = [2.079909,2.000000;2.080084,2.000000;5.954312,2.000000;2.027152,6.000000;2.055495,6.000000;2.027495,6.000000;5.863131,6.000000;];
b_t_9 = [2.062330,2.062459;2.062459,2.062330;5.962798,2.036399;2.027826,5.971931;2.044443,5.955558;2.028069,5.972175;5.903449,5.903593];

figure('Name','Grid based localization simulation result, #ref tags is 2','NumberTitle','off')
scatter(a_g(:,1), a_g(:,2), 'g','filled');
hold on;
scatter(b_g_2(:,1), b_g_2(:,2), 'b*');
axis([0 8 0 8]);

figure('Name','Grid based localization simulation result, #ref tags is 4','NumberTitle','off')
scatter(a_g(:,1), a_g(:,2), 'g','filled');
hold on;
scatter(b_g_4(:,1), b_g_4(:,2), 'b*');
axis([0 8 0 8]);

figure('Name','Grid based localization simulation result, #ref tags is 9','NumberTitle','off')
scatter(a_g(:,1), a_g(:,2), 'g','filled');
hold on;
scatter(b_g_9(:,1), b_g_9(:,2), 'b*');
axis([0 8 0 8]);



figure('Name','Taxonomy based localization simulation result, #ref tags is 2','NumberTitle','off')
scatter(a_t(:,1), a_t(:,2), 'g','filled');
hold on;
scatter(b_t_2(:,1), b_t_2(:,2), 'b*');
axis([0 6 0 8]);

figure('Name','Taxonomy based localization simulation result, #ref tags is 4','NumberTitle','off')
scatter(a_t(:,1), a_t(:,2), 'g','filled');
hold on;
scatter(b_t_4(:,1), b_t_4(:,2), 'b*');
axis([0 6 0 8]);

figure('Name','Taxonomy based localization simulation result, #ref tags is 9','NumberTitle','off')
scatter(a_t(:,1), a_t(:,2), 'g','filled');
hold on;
scatter(b_t_2(:,1), b_t_2(:,2), 'b*');
axis([0 6 0 8]);

sum_g2 = 0;
max_g2 = 0;
for i = 1 : 10
    e_g2(i) = sqrt((a_g(i, 1) - b_g_2(i, 1))^2 + (a_g(i, 2) - b_g_2(i, 2))^2); 
    sum_g2 = sum_g2 + e_g2(i);
    if e_g2(i) > max_g2
        max_g2 = e_g2(i);
    end
end
max_g2
avg_g2 = sum_g2 / 10
energy_g2 = 4*2;

sum_g4 = 0;
max_g4 = 0;
for i = 1 : 10
    e_g4(i) = sqrt((a_g(i, 1) - b_g_4(i, 1))^2 + (a_g(i, 2) - b_g_4(i, 2))^2); 
    sum_g4 = sum_g4 + e_g4(i);
    if e_g4(i) > max_g4
        max_g4 = e_g4(i);
    end
end
max_g4
avg_g4 = sum_g4 / 10
energy_g4 = 4*4;

sum_g9 = 0;
max_g9 = 0;
for i = 1 : 10
    e_g9(i) = sqrt((a_g(i, 1) - b_g_9(i, 1))^2 + (a_g(i, 2) - b_g_9(i, 2))^2); 
    sum_g9 = sum_g9 + e_g9(i);
    if e_g9(i) > max_g9
        max_g9 = e_g9(i);
    end
end
max_g9
avg_g9 = sum_g9 / 10
energy_g9 = 4*9;


sum_t2 = 0;
max_t2 = 0;
for i = 1 : 7
    e_t2(i) = sqrt((a_t(i, 1) - b_t_2(i, 1))^2 + (a_t(i, 2) - b_t_2(i, 2))^2); 
    sum_t2 = sum_t2 + e_t2(i);
    if e_t2(i) > max_t2
        max_t2 = e_t2(i);
    end
end
max_t2
avg_t2 = sum_t2 / 7
energy_t2 = 3*2;

sum_t4 = 0;
max_t4 = 0;
for i = 1 : 7
    e_t4(i) = sqrt((a_t(i, 1) - b_t_4(i, 1))^2 + (a_t(i, 2) - b_t_4(i, 2))^2); 
    sum_t4 = sum_t4 + e_t4(i);
    if e_t4(i) > max_t4
        max_t4 = e_t4(i);
    end
end
max_t4
avg_t4 = sum_t4 / 7
energy_t4 = 3*4;

sum_t9 = 0;
max_t9 = 0;
for i = 1 : 7
    e_t9(i) = sqrt((a_t(i, 1) - b_t_9(i, 1))^2 + (a_t(i, 2) - b_t_9(i, 2))^2); 
    sum_t9 = sum_t9 + e_t9(i);
    if e_t9(i) > max_t9
        max_t9 = e_t9(i);
    end
end
max_t9
avg_t9 = sum_t9 / 7
energy_t9 = 3*9;

