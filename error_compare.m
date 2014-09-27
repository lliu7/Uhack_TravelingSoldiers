%function: generate error figure for localization algorithm
num_obj = 3;
a = [1, 1 ; 2, 2; 2, 8];
b = [1, 2; 2, 3; 3, 8];

scatter(a(:,1), a(:,2), 'g','filled');
hold on;
scatter(b(:,1), b(:,2), 'b*');
axis([0 10 0 10]);

sum = 0;
max = 0;
for i = 1 : 3
    e(i) = sqrt((a(i, 1) - b(i, 1))^2 + (a(i, 2) - b(i, 2))^2); 
    sum = sum + e(i);
    if e(i) > max
        max = e(i);
    end
end

