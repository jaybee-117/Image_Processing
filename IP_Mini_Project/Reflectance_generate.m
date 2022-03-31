%% Adding defocusing two two images
disp('Generation of defocused bi-layers');
I2 = im2double(imread("lena_colored_256.bmp"));
I1 = im2double(imread("idk_256.tiff"));
gauss_size = 50;
sigma = 2;
h = fspecial( 'gaussian' ,gauss_size,sigma);
I2_h = imfilter(I2,h, 'conv' ); 
I = (I1+I2_h)./2;
imwrite(I,"reflectance_subject.bmp");
figure(3),
subplot 131, imshow(I1), title('input');
subplot 132, imshow(I2); title('defocus img');
subplot 133, imshow(I); title('final relectance subject');