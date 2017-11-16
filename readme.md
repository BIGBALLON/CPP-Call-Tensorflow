
# Calling TensorFlow Python Program from C++

This Demo will show how to call an pre-trained imagenet model to predict picture in C++.

├─ prediction.cpp                 % C++ file
├─ vgg_model.py                   % TensorFlow vgg model   
├─ makefile                       % Compile file
└─ test_pic/                      % Test pictures
	├─ cat.jpeg     
	├─ puzzle.jpeg
	└─ tiger.jpeg  

## The python script

Firstly, we need an python script which let us to load VGG model & use it to do predict op.

You can test the script ``vgg_model.py`` by using the following cmd:


```
(deeplearning) bg@bg-cgi:~/Desktop/C_python$ python3 vgg_model.py 
Using TensorFlow backend.
Downloading data from https://github.com/fchollet/deep-learning-models/releases/download/v0.1/vgg19_weights_tf_dim_ordering_tf_kernels.h5
574562304/574710816 [============================>.] - ETA: 0s2017-11-17 01:06:29.952399
...
...
...
2017-11-17 01:06:30.106077: I tensorflow/core/common_runtime/gpu/gpu_device.cc:1045] Creating TensorFlow device (/gpu:0) -> (device: 0, name: GeForce GTX 1080, pci bus id: 0000:01:00.0)

 Please input picture file to predict: test_pic/cat.jpeg
 Predicted: [('n02124075', 'Egyptian_cat', 0.93183666)]

```


It will download weight file ``vgg19_weights_tf_dim_ordering_tf_kernels.h5`` and ``imagenet_class_index.json`` to ``~/.keras/models`` the first time.


## Compile 

Using ``make all`` to Compile your cpp file.  
Make sure your python's version is correct.

```
bg@bg-cgi:~/.keras/models$ locate Python.h
/usr/include/python2.7/Python.h
/usr/include/python3.5m/Python.h

```


so I use the following cmd to Compile 

```
g++ -std=c++11 -Wall -O3 prediction.cpp -lpython3.5m -L/usr/include/python3.5m/ -I/usr/include/python3.5m/ -o pred_test

```


## Usage


``make all`` to compile, then ``./pred_test`` to run c++ program.

Then you can see it works:

```
 ===========> START CALL PYTHON SCRIPT <===========
 ===========> 1st CALL <===========
 Please input picture file to predict: huhu
 file not exist!
 ===========> 2nd CALL <===========
 Please input picture file to predict: test_pic/cat.jpeg
 Predicted:  [('n02124075', 'Egyptian_cat', 0.93183666)]
 ===========> 3rd CALL <===========
 Please input picture file to predict: test_pic/tiger.jpeg
 Predicted:  [('n02129604', 'tiger', 0.82598984)]
 ===========> 4th CALL <===========
 Please input picture file to predict: test_pic/puzzle.jpeg
 Predicted:  [('n03598930', 'jigsaw_puzzle', 0.99813461)]
 ===========> CALLING FINISHED <===========
(deeplearning) bg@bg-cgi:~/Desktop/C_python$ 

```