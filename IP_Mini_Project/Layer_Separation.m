%% Intrinsic Image Decomposition
disp('Intrinsic Images Example');
I1 = im2double(imread('intrinsic_cup.png')); 
[R,S] = Intrinsic_Decomposition(I1, 0);
imwrite(R,"intrinsic_reflectance.bmp");
imwrite(S,"intrinsic_illumination.bmp");
figure(1),
subplot 131, imshow(I1), title('input');
subplot 132, imshow(R); title('reflectace');
subplot 133, imshow(S); title('illumination');


%% Reflection Separation Using Focus 
disp('Reflection Removal Example');
I2 = im2double(imread('reflectance_subject_tampered.png'));
[H,W,D] = size(I2);
[LB,LR] = Reflection_Removal(I2, 50, zeros(H,W,D), I2);
imwrite(LB, "Image_background.bmp");
imwrite(LR,"Image_refelction.bmp");
figure(2),
subplot 131, imshow(I2) , title('input');
subplot 132, imshow(LB*2), title('background'); 
subplot 133, imshow(LR*2), title('reflection');
